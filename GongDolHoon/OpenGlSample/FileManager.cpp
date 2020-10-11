#include <iostream>
#include <fstream>
#include <sstream>

#include "FileManager.h"
#include "include/GLFW/glfw3.h" 

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

FileManager* FileManager::instance = nullptr;

GLuint FileManager::load_shaders(const char* vertex_file_path, const char* fragment_file_path) {
	
	printf("GONG_DOL_HOON_CUSTOM_ENGINE [SHADER_LOADING]: %s, %s\n", vertex_file_path, fragment_file_path);

	// 쉐이더들 생성
	GLuint _vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint _fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	// 버텍스 쉐이더 코드를 파일에서 읽기
	std::string _vertex_shader_code;
	std::ifstream _vertex_shader_stream(vertex_file_path, std::ios::in);
	if (_vertex_shader_stream.is_open()) {
		std::stringstream sstr;
		sstr << _vertex_shader_stream.rdbuf();
		_vertex_shader_code = sstr.str();
		_vertex_shader_stream.close();
	}
	else {
		printf("파일 %s 를 읽을 수 없음. 정확한 디렉토리를 사용 중입니까 ? FAQ 를 우선 읽어보는 걸 잊지 마세요!\n", vertex_file_path);
		getchar();
		return 0;
	}

	// 프래그먼트 쉐이더 코드를 파일에서 읽기
	std::string _fragment_shader_code;
	std::ifstream _fragment_shader_stream(fragment_file_path, std::ios::in);
	if (_fragment_shader_stream.is_open()) {
		std::stringstream sstr;
		sstr << _fragment_shader_stream.rdbuf();
		_fragment_shader_code = sstr.str();
		_fragment_shader_stream.close();
	}

	GLint _result = GL_FALSE;
	int _info_log_length;

	char const* _vertex_source_pointer = _vertex_shader_code.c_str();
	glShaderSource(_vertex_shader_id, 1, &_vertex_source_pointer, NULL);
	glCompileShader(_vertex_shader_id);

	// 버텍스 쉐이더를 검사
	glGetShaderiv(_vertex_shader_id, GL_COMPILE_STATUS, &_result);
	glGetShaderiv(_vertex_shader_id, GL_INFO_LOG_LENGTH, &_info_log_length);
	if (_info_log_length > 0) {
		std::vector<char> VertexShaderErrorMessage(_info_log_length + 1);
		glGetShaderInfoLog(_vertex_shader_id, _info_log_length, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	char const* _fragment_source_pointer = _fragment_shader_code.c_str();
	glShaderSource(_fragment_shader_id, 1, &_fragment_source_pointer, NULL);
	glCompileShader(_fragment_shader_id);

	// 프래그먼트 쉐이더를 검사
	glGetShaderiv(_fragment_shader_id, GL_COMPILE_STATUS, &_result);
	glGetShaderiv(_fragment_shader_id, GL_INFO_LOG_LENGTH, &_info_log_length);
	if (_info_log_length > 0) {
		std::vector<char> FragmentShaderErrorMessage(_info_log_length + 1);
		glGetShaderInfoLog(_fragment_shader_id, _info_log_length, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	GLuint _program_id = glCreateProgram();
	glAttachShader(_program_id, _vertex_shader_id);
	glAttachShader(_program_id, _fragment_shader_id);
	glLinkProgram(_program_id);

	// 프로그램 검사
	glGetProgramiv(_program_id, GL_LINK_STATUS, &_result);
	glGetProgramiv(_program_id, GL_INFO_LOG_LENGTH, &_info_log_length);
	if (_info_log_length > 0) {
		std::vector<char> _program_error_message(_info_log_length + 1);
		glGetProgramInfoLog(_program_id, _info_log_length, NULL, &_program_error_message[0]);
		printf("%s\n", &_program_error_message[0]);
	}

	glDetachShader(_program_id, _vertex_shader_id);
	glDetachShader(_program_id, _fragment_shader_id);

	glDeleteShader(_vertex_shader_id);
	glDeleteShader(_fragment_shader_id);

	return _program_id;
}

GLuint FileManager::load_dds(const char* dds_path) {

	printf("GONG_DOL_HOON_CUSTOM_ENGINE [DDS_LOADING]: %s\n", dds_path);

	unsigned char _header[124];

	FILE* _fp;

	/* try to open the file */
	fopen_s(&_fp, dds_path, "rb");
	if (_fp == NULL) {
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", dds_path); 
		getchar();
		return 0;
	}

	/* verify the type of file */
	char _file_code[4];
	fread(_file_code, 1, 4, _fp);
	if (strncmp(_file_code, "DDS ", 4) != 0) {
		fclose(_fp);
		return 0;
	}

	/* get the surface desc */
	fread(&_header, 124, 1, _fp);

	unsigned int _height = *(unsigned int*)&(_header[8]);
	unsigned int _width = *(unsigned int*)&(_header[12]);
	unsigned int _linear_size = *(unsigned int*)&(_header[16]);
	unsigned int _mip_map_count = *(unsigned int*)&(_header[24]);
	unsigned int _four_CC = *(unsigned int*)&(_header[80]);


	unsigned char* _buffer;
	unsigned int _buf_size;
	/* how big is it going to be including all mipmaps? */
	_buf_size = _mip_map_count > 1 ? _linear_size * 2 : _linear_size;
	_buffer = (unsigned char*)malloc(_buf_size * sizeof(unsigned char));
	fread(_buffer, 1, _buf_size, _fp);
	/* close the file pointer */
	fclose(_fp);

	unsigned int _components = (_four_CC == FOURCC_DXT1) ? 3 : 4;
	unsigned int _format;
	switch (_four_CC)
	{
	case FOURCC_DXT1:
		_format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		_format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		_format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(_buffer);
		return 0;
	}

	// Create one OpenGL texture
	GLuint _texture_ID;
	glGenTextures(1, &_texture_ID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, _texture_ID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int _block_size = (_format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int _offset = 0;

	/* load the mipmaps */
	for (unsigned int _level = 0; _level < _mip_map_count && (_width || _height); ++_level)
	{
		unsigned int _size = ((_width + 3) / 4) * ((_height + 3) / 4) * _block_size;
		glCompressedTexImage2D(GL_TEXTURE_2D, _level, _format, _width, _height,
			0, _size, _buffer + _offset);

		_offset += _size;
		_width /= 2;
		_height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if (_width < 1)
		{
			_width = 1;
		}
		if (_height < 1) 
		{
			_height = 1;
		}

	}

	free(_buffer);

	return _texture_ID;
}

GLuint FileManager::load_bmp(const char* bmp_path)
{
	printf("GONG_DOL_HOON_CUSTOM_ENGINE [BMP_LOADING]: %s\n", bmp_path);

	// Data read from the header of the BMP file
	unsigned char _header[54];
	unsigned int _data_pos;
	unsigned int _image_size;
	unsigned int _width, _height;
	// Actual RGB data
	unsigned char* _data;

	// Open the file
	FILE* _file = fopen(bmp_path, "rb");
	if (!_file) {
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", bmp_path);
		getchar();
		return 0;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if (fread(_header, 1, 54, _file) != 54) {
		printf("Not a correct BMP file\n");
		fclose(_file);
		return 0;
	}
	// A BMP files always begins with "BM"
	if (_header[0] != 'B' || _header[1] != 'M') {
		printf("Not a correct BMP file\n");
		fclose(_file);
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(_header[0x1E]) != 0) { printf("Not a correct BMP file\n");    fclose(_file); return 0; }
	if (*(int*)&(_header[0x1C]) != 24) { printf("Not a correct BMP file\n");    fclose(_file); return 0; }

	// Read the information about the image
	_data_pos = *(int*)&(_header[0x0A]);
	_image_size = *(int*)&(_header[0x22]);
	_width = *(int*)&(_header[0x12]);
	_height = *(int*)&(_header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (_image_size == 0)
	{
		_image_size = _width * _height * 3; // 3 : one byte for each Red, Green and Blue component
	}
	if (_data_pos == 0)    
	{
		_data_pos = 54; // The BMP header is done that way
	}
	// Create a buffer
	_data = new unsigned char[_image_size];

	// Read the actual data from the file into the buffer
	fread(_data, 1, _image_size, _file);

	// Everything is in memory now, the file can be closed.
	fclose(_file);

	// Create one OpenGL texture
	GLuint _texture_ID;
	glGenTextures(1, &_texture_ID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, _texture_ID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_BGR, GL_UNSIGNED_BYTE, _data);

	// OpenGL has now copied the data. Free our own version
	delete[] _data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return _texture_ID;
}

bool FileManager::load_obj(const char* obj_path, std::vector<glm::vec3>& out_sphere_vertices, std::vector<glm::vec2>& out_sphere_uvs, std::vector<glm::vec3>& out_sphere_normals)
{
	printf("GONG_DOL_HOON_CUSTOM_ENGINE [OBJ_LOADING]: %s\n", obj_path);

	std::vector<unsigned int> _vertex_indices, _uv_indices, _normal_indices;
	std::vector<glm::vec3> _temp_sphere_vertices;
	std::vector<glm::vec2> _temp_sphere_uvs;
	std::vector<glm::vec3> _temp_sphere_normals;


	FILE* _file = fopen(obj_path, "r");
	if (_file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char _line_header[128];
		// read the first word of the line
		int _res = fscanf(_file, "%s", _line_header);
		if (_res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(_line_header, "v") == 0) {
			glm::vec3 _vertex;
			fscanf(_file, "%f %f %f\n", &_vertex.x, &_vertex.y, &_vertex.z);
			_temp_sphere_vertices.push_back(_vertex);
		}
		else if (strcmp(_line_header, "vt") == 0) {
			glm::vec2 _uv;
			fscanf(_file, "%f %f\n", &_uv.x, &_uv.y);
			_uv.y = -_uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			_temp_sphere_uvs.push_back(_uv);
		}
		else if (strcmp(_line_header, "vn") == 0) {
			glm::vec3 _normal;
			fscanf(_file, "%f %f %f\n", &_normal.x, &_normal.y, &_normal.z);
			_temp_sphere_normals.push_back(_normal);
		}
		else if (strcmp(_line_header, "f") == 0) {
			std::string _vertex1, _vertex2, _vertex3;
			unsigned int _vertex_index[3], _uv_index[3], _normal_index[3];
			int _matches = fscanf(_file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &_vertex_index[0], &_uv_index[0], &_normal_index[0], &_vertex_index[1], &_uv_index[1], &_normal_index[1], &_vertex_index[2], &_uv_index[2], &_normal_index[2]);
			if (_matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				fclose(_file);
				return false;
			}
			_vertex_indices.push_back(_vertex_index[0]);
			_vertex_indices.push_back(_vertex_index[1]);
			_vertex_indices.push_back(_vertex_index[2]);
			_uv_indices.push_back(_uv_index[0]);
			_uv_indices.push_back(_uv_index[1]);
			_uv_indices.push_back(_uv_index[2]);
			_normal_indices.push_back(_normal_index[0]);
			_normal_indices.push_back(_normal_index[1]);
			_normal_indices.push_back(_normal_index[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char _stupid_buffer[1000];
			fgets(_stupid_buffer, 1000, _file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i < _vertex_indices.size(); i++) {

		// Get the indices of its attributes
		unsigned int _vertex_index = _vertex_indices[i];
		unsigned int _uv_index = _uv_indices[i];
		unsigned int _normal_index = _normal_indices[i];

		// Get the attributes thanks to the index
		glm::vec3 _vertex = _temp_sphere_vertices[_vertex_index - 1];
		glm::vec2 _uv = _temp_sphere_uvs[_uv_index - 1];
		glm::vec3 _normal = _temp_sphere_normals[_normal_index - 1];

		// Put the attributes in buffers
		out_sphere_vertices.push_back(_vertex);
		out_sphere_uvs.push_back(_uv);
		out_sphere_normals.push_back(_normal);

	}
	fclose(_file);

	return true;
}
