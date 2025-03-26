//
// Created by vastrakai on 7/3/2024.
//

#pragma once
#include <imgui.h>
#include <glm/glm.hpp>

struct Rect {
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
        float array[4]{};
    };

    Rect()
    {
        this->x = 0;
        this->y = 0;
        this->z = 0;
        this->w = 0;
    }

    Rect(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    // Type Conversions

    ImVec4 ToImVec4() const {
        return ImVec4(x, y, z, w);
    }

};

struct glmatrixf : public glm::mat4
{
    glmatrixf() = default;

    glmatrixf(glm::mat4 mat) : glm::mat4(mat) {}


    bool OWorldToScreen(glm::vec3 origin, glm::vec3 pos, glm::vec2& screen, glm::vec2 fov, glm::vec2 displaySize) const
    {
        pos = pos - origin;

        float x = glm::dot((*this)[0], glm::vec4(pos.x, pos.y, pos.z, 1.0f));
        float y = glm::dot((*this)[1], glm::vec4(pos.x, pos.y, pos.z, 1.0f));
        float z = glm::dot((*this)[2], glm::vec4(pos.x, pos.y, pos.z, 1.0f));

        if (z > 0)
            return false;

        float mX = (float)displaySize.x / 2.0F;
        float mY = (float)displaySize.y / 2.0F;

        screen.x = mX + (mX * x / -z * fov.x);
        screen.y = mY - (mY * y / -z * fov.y);

        // If the number is too large, it's probably offscreen
        if (screen.x > displaySize.x * 2 || screen.y > displaySize.y * 2)
            return false;

        return true;
    }

    inline void mul(const glmatrixf& x, const glmatrixf& y) {
        mul(x, y);
    }
    ///pos should be the exact center of the enemy model for scaling to work properly
    glm::vec2 WorldToScreen(glm::vec3 pos, int width, int height) {
        //Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
        Rect clipCoords;
        clipCoords.x = glm::dot((*this)[0], glm::vec4(pos.x, pos.y, pos.z, 1.0f));
        clipCoords.y = glm::dot((*this)[1], glm::vec4(pos.x, pos.y, pos.z, 1.0f));
        clipCoords.z = glm::dot((*this)[2], glm::vec4(pos.x, pos.y, pos.z, 1.0f));
        clipCoords.w = glm::dot((*this)[3], glm::vec4(pos.x, pos.y, pos.z, 1.0f));

        //perspective division, dividing by clip.W = Normalized Device Coordinates
        glm::vec3 NDC;
        NDC.x = clipCoords.x / clipCoords.w;
        NDC.y = clipCoords.y / clipCoords.w;
        NDC.z = clipCoords.z / clipCoords.w;

        //viewport tranform to screenCooords

        glm::vec2 playerscreen;
        playerscreen.x = ((float)width / 2 * NDC.x) + (NDC.x + (float)width / 2);  // NOLINT(bugprone-integer-division)
        playerscreen.y = -((float)height / 2 * NDC.y) + (NDC.y + (float)height / 2);  // NOLINT(bugprone-integer-division)

        return playerscreen;
    }

};

struct AABB {
    union {
        struct {
            glm::vec3 mMin;
            glm::vec3 mMax;
        };
        glm::vec3 mBounds[2];
    };

    AABB(const glm::vec3& position, const glm::vec3& size) {
        /*this->upper.x = position.x;
        this->lower.x = position.x + size.x;
        this->upper.y = position.y;
        this->lower.y = position.y + size.y;
        this->upper.z = position.z;
        this->lower.z = position.z + size.z;*/
        mMin.x = position.x + size.x;
        mMin.y = position.y + size.y;
        mMin.z = position.z + size.z;
        mMax.x = position.x;
        mMax.y = position.y;
        mMax.z = position.z;
    }

    AABB(const glm::vec3& min, const glm::vec3& max, bool) : mMin(min), mMax(max) {}
    AABB() : mMin(0), mMax(0) {}

    glm::vec3 getClosestPoint(const glm::vec3& point) const {
        glm::vec3 result;
        result.x = point.x < mMin.x ? mMin.x : (point.x > mMax.x ? mMax.x : point.x);
        result.y = point.y < mMin.y ? mMin.y : (point.y > mMax.y ? mMax.y : point.y);
        result.z = point.z < mMin.z ? mMin.z : (point.z > mMax.z ? mMax.z : point.z);
        return result;
    }

    // ==
    bool operator==(const AABB& other) const {
        return this->mMin == other.mMin && this->mMax == other.mMax;
    }
};

struct FrameTransform {
    glmatrixf mMatrix    {};
    glm::vec3 mOrigin    {};
    glm::vec3 mPlayerPos {};
    glm::vec2 mFov       {};
};

using BlockPos = glm::ivec3;

namespace glm {
    // < operator for glm::ivec3
    inline bool operator<(const glm::ivec3& lhs, const glm::ivec3& rhs) {
        return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z;
    }
}

template<>
struct std::hash<BlockPos>
{
    size_t operator()(const BlockPos& obj) const noexcept
    {
        return obj.x ^ obj.y ^ obj.z;
    }
};