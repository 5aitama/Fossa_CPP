#version 330

uniform vec2 iResolution;
uniform float iTime;

out vec4 outColor;

void main()
{
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
	vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0, 2, 4));

	outColor = vec4(col, 1.0);
}