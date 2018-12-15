#version 400 core

out vec4 color;

in DATA {
	flat vec4 color;
}fs_in;

void main() {
	color = fs_in.color;
}