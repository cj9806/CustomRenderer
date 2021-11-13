#version 430 core
in vec4 vertColor;

// shader uniforms
layout (location = 3) uniform sampler2D albedo;
layout (location = 4) uniform vec3 ambientLight;
layout (location = 5) uniform vec3 lightDir;

//input attributes
in vec2 vUV;
in vec3 vNormal;

//output
out vec4 outColor;
void main() 
{ 
	float d = max(0,dot(vNormal, -lightDir));
	vec3 diffuse = vec3(d);
	vec4 base = texture(albedo, vUV);

	outColor.rgb = base.rgb * (ambientLight + diffuse);
	outColor.a = base.a;
}