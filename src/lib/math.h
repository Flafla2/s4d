
#pragma once

#include <cmath>
#include <algorithm>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"
#include "bbox.h"

#define PI 3.14159265358979323846264338327950288f
#define Radians(v) (v * (PI / 180.0f)) 
#define Degrees(v) (v * (180.0f / PI)) 

inline float clamp(float x, float min, float max) {
	return std::min(std::max(x,min),max);
}
inline Vec2 clamp(Vec2 v, Vec2 min, Vec2 max) {
	return Vec2(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y));
}
inline Vec3 clamp(Vec3 v, Vec3 min, Vec3 max) {
	return Vec3(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z));
}
inline Vec4 clamp(Vec4 v, Vec4 min, Vec4 max) {
	return Vec4(clamp(v.x, min.x, max.x), clamp(v.y, min.y, max.y), clamp(v.z, min.z, max.z), clamp(v.w, min.w, max.w));
}

template<typename T>
T lerp(T start, T end, T t) {
	return start + (end - start) * t;
}

inline float frac(float x) {
	return x - (long long)x;
}

inline float smoothstep(float e0, float e1, float x) {
	float t = clamp((x - e0) / (e1 - e0), 0.0f, 1.0f);
	return t * t * (3.0f - 2.0f * t);
}
