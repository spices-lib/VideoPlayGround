#ifndef SHADER_COMMON
#define SHADER_COMMON

#ifdef __cplusplus
#include <glm/glm.hpp>

namespace Shader
{
	using vec2 = glm::vec2;
	using vec3 = glm::vec3;
	using vec4 = glm::vec4;
	using mat4 = glm::mat4;
	using uint = unsigned int;

#else

#extension GL_EXT_scalar_block_layout : enable
#extension GL_EXT_debug_printf : require  /* debugPrintfEXT("Hello: %d", num); */

#endif

const vec2 invAtan = vec2(0.1591, 0.3183);
const float PI     = 3.141592654f;
const float BIAS   = 0.01f;
const float EPS    = 1e-6f;

struct Vertex
{
	vec3 position; 
	vec3 normal;
	vec3 color;
	vec2 texCoord;
};

#define Pixel Vertex

struct MaterialAttributes
{
	vec3  albedo;
	float roughness;
	float metallic;
	vec3  emissive;
	vec3  normal;
};

struct View
{
	mat4  projection;
	mat4  nprojection;
	mat4  view;
	mat4  inView;
	vec4  sceneTextureSize;
	vec4  windowSize;
	float fov;
};

struct Input
{
	vec4  mousePos;
	float engineTime;
	float frameTime;
};

#ifdef __cplusplus
}
#endif

#endif