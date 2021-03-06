#version 330

in vec2 gf_TexCoord;
flat in vec4 gf_Color;
uniform sampler2D u_Tex0;

out vec4 out_Color;

void main(void) {
	out_Color = texture(u_Tex0, gf_TexCoord) * gf_Color;
}
