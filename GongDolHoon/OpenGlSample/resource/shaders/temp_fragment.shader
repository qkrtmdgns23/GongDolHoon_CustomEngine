#version 330 core

// Interpolated values from the vertex shaders
in vec3 vs_position;
in vec2 vs_texcoord;
in vec3 vs_normal;

// Ouput data
out vec3 fs_color;

// Values that stay constant for the whole mesh.
uniform sampler2D MyTextureSampler;

void main() {
	fs_color = texture(MyTextureSampler, vs_texcoord).rgb;
}
