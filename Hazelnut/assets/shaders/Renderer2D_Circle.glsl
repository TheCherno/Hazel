//////////////
// Hazel 2D //
//////////////
//
// Renderer 2D Circle Shader
//

#type vertex
#version 450 core

layout(location = 0) in vec3 a_WorldPosition;
layout(location = 1) in float a_Thickness;
layout(location = 2) in vec2 a_LocalPosition;
layout(location = 3) in vec4 a_Color;
layout(location = 4) in int a_EntityID;

layout (std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec2 LocalPosition;
	float Thickness;
	vec4 Color;
};

layout (location = 0) out VertexOutput Output;
layout (location = 3) out flat int v_EntityID;

void main()
{
	Output.LocalPosition = a_LocalPosition;
	Output.Thickness = a_Thickness;
	Output.Color = a_Color;
	v_EntityID = a_EntityID;
	gl_Position = u_ViewProjection * vec4(a_WorldPosition, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec2 LocalPosition;
	float Thickness;
	vec4 Color;
};

layout (location = 0) in VertexOutput Input;
layout (location = 3) in flat int v_EntityID;

void main()
{
	float fade = 0.01;
	float dist = sqrt(dot(Input.LocalPosition, Input.LocalPosition));
	float t = Input.Thickness;
	if (dist > 1.0 || dist < 1.0 - t - fade)
		discard;

	float alpha = 1.0 - smoothstep(1.0f - fade, 1.0f, dist);
	alpha *= smoothstep(1.0 - t - fade, 1.0 - t, dist);
	o_Color = Input.Color;
	o_Color.a = Input.Color.a * alpha;

	o_EntityID = v_EntityID;
}
