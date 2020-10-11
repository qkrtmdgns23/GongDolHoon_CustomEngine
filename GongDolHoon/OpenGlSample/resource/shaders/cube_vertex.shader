#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_texcoord;
layout(location = 2) in vec3 vertex_normal;

// Output data ; will be interpolated for each fragment.
out vec3 vs_position;
out vec2 vs_texcoord;
out vec3 vs_normal;

// Values that stay constant for the whole mesh.
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
	vs_position = vec4(Model * vec4(vertex_position, 1.f)).xyz;
	vs_texcoord = vertex_texcoord;
	vs_normal = mat3(Model) * vertex_normal;

	gl_Position = Projection * View * Model * vec4(vertex_position, 1.f);
}
