
#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include <cfloat>

#include "vec2.h"
#include "vec3.h"
#include "mat4.h"

struct BBox {

	BBox() : 
        min(FLT_MAX),
        max(-FLT_MAX) {
	}
	BBox(Vec3 min, Vec3 max) :
        min(min),
        max(max) {
	}
	BBox(const BBox& src) {
		min = src.min;
		max = src.max;
	}

	BBox operator=(BBox v) {
		min = v.min;
		max = v.max;
		return *this;
	}

    void reset() {
        min = Vec3(FLT_MAX);
        max = Vec3(-FLT_MAX);
    }

    void enclose(Vec3 point) {
        min = hmin(min, point);
		max = hmax(max, point);
    }

    std::vector<Vec3> corners() const {
        std::vector<Vec3> ret(8);
        ret[0] = Vec3(min.x, min.y, min.z);
        ret[1] = Vec3(max.x, min.y, min.z);
        ret[2] = Vec3(min.x, max.y, min.z);
        ret[3] = Vec3(min.x, min.y, max.z);
        ret[4] = Vec3(max.x, max.y, min.z);
        ret[5] = Vec3(min.x, max.y, max.z);
        ret[6] = Vec3(max.x, min.y, max.z);
        ret[7] = Vec3(max.x, max.y, max.z);
        return ret;
    }

    void screen_rect(Mat4 transform, Vec2& min_out, Vec2& max_out) const {

        min_out = Vec2(FLT_MAX);
        max_out = Vec2(-FLT_MAX);
        auto c = corners();
        bool partially_behind = false, all_behind = true;
        for(auto& v : c) {
            Vec3 p = transform * v;
            if(p.z < 0) {
                partially_behind = true;
            } else {
                all_behind = false;
            }
            min_out = hmin(min_out, Vec2(p.x, p.y));
            max_out = hmax(max_out, Vec2(p.x, p.y));
        }

        if(partially_behind && !all_behind) {
            min_out = Vec2(-1.0f, -1.0f);
            max_out = Vec2(1.0f, 1.0f);
        } else if(all_behind) {
            min_out = Vec2(0.0f, 0.0f);
            max_out = Vec2(0.0f, 0.0f);
        }
    }

    Vec3 min, max;
};
