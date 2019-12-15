
#pragma once

#include <cmath>
#include <algorithm>

#include "log.h"

struct Vec3 {

	Vec3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vec3(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	Vec3(const Vec3& src) {
		x = src.x;
		y = src.y;
		z = src.z;
	}

	Vec3 operator=(Vec3 v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	float& operator[](int idx) {
		assert(idx >= 0 && idx <= 2);
		return data[idx];
	}
	float operator[](int idx) const {
		assert(idx >= 0 && idx <= 2);
		return data[idx];
	}

	Vec3 operator+=(Vec3 v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}
	Vec3 operator-=(Vec3 v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}
	Vec3 operator*=(Vec3 v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}
	Vec3 operator/=(Vec3 v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vec3 operator+=(float s) {
		x += s;
		y += s;
		z += s;
		return *this;
	}
	Vec3 operator-=(float s) {
		x -= s;
		y -= s;
		z -= s;
		return *this;
	}
	Vec3 operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	Vec3 operator/=(float s) {
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}

	Vec3 operator+(Vec3 v) const {
		return Vec3(x + v.x, y + v.y, z + v.z);
	}
	Vec3 operator-(Vec3 v) const {
		return Vec3(x - v.x, y - v.y, z - v.z);
	}
	Vec3 operator*(Vec3 v) const {
		return Vec3(x * v.x, y * v.y, z * v.z);
	}
	Vec3 operator/(Vec3 v) const {
		return Vec3(x / v.x, y / v.y, z / v.z);
	}

	Vec3 operator+(float s) const {
		return Vec3(x + s, y + s, z + s);
	}
	Vec3 operator-(float s) const {
		return Vec3(x - s, y - s, z - s);
	}
	Vec3 operator*(float s) const {
		return Vec3(x * s, y * s, z * s);
	}
	Vec3 operator/(float s) const {
		return Vec3(x / s, y / s, z / s);
	}

	bool operator==(Vec3 v) const {
		return x == v.x && y == v.y && z == v.z;
	}
	bool operator!=(Vec3 v) const {
		return x != v.x || y != v.y || z != v.z;
	}

	Vec3 abs() const {
		return Vec3(std::fabsf(x), std::fabsf(y), std::fabsf(z));
	}
	Vec3 operator-() const {
		return Vec3(-x, -y, -z);
	}

	/// Modify vec to have unit length
	Vec3 normalize() {
		float n = norm();
		x /= n;
		y /= n;
		z /= n;
		return *this;
	}
	/// Return unit length vec in the same direction
	Vec3 unit() const {
		float n = norm();
		return Vec3(x / n, y / n, z / n);
	}

	float norm_squared() const {
		return x * x + y * y + z * z;
	}
	float norm() const {
		return std::sqrtf(norm_squared());
	}

	union {
		struct {
			float x;
			float y;
			float z;
		};
		float data[3] = {};
	};
};

inline Vec3 operator+(float s, Vec3 v) {
	return Vec3(v.x + s, v.y + s, v.z + s);
}
inline Vec3 operator-(float s, Vec3 v) {
	return Vec3(v.x - s, v.y - s, v.z - s);
}
inline Vec3 operator*(float s, Vec3 v) {
	return Vec3(v.x * s, v.y * s, v.z * s);
}
inline Vec3 operator/(float s, Vec3 v) {
	return Vec3(v.x / s, v.y / s, v.z / s);
}

inline Vec3 min(Vec3 l, Vec3 r) {
	return Vec3(std::min(l.x, r.x), std::min(l.y, r.y), std::min(l.z, r.z));
}
inline Vec3 max(Vec3 l, Vec3 r) {
	return Vec3(std::max(l.x, r.x), std::max(l.y, r.y), std::max(l.z, r.z));
}

inline float dot(Vec3 l, Vec3 r) {
	return l.x * r.x + l.y * r.y + l.z * r.z;
}
inline Vec3 cross(Vec3 l, Vec3 r) {
	return Vec3(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x);
}
