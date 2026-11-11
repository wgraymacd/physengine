#pragma once

/*
2D
*/

/// @note 
/*
can make templated instead of just using floats (simplicity makes it fast and easy)
add unit tests coverting edge cases
can add more utilities like reflect, project, cross, rotate, etc.
can add SIMD-friendly optimizations, big win for manipulating large numbers of Vec2 in tight loops for something like particles or collisions (CPU feature that runs the same operation on several data lanes in one instruction using vector registers (SSE/AVX on x86, NEON on ARM); lets you do e.g. 4 or 8 float adds with one instruction instead of 4–8 separate adds)
should generally look into optimizations (part of the point of having the engine)
*/

#include <ostream> // For printing Vec2

/// TODO: is it necessary to use the reference/pointer and stuff here? may be easier to just copy everything, Vec2's are rly small
// Lightweight 2D vector for the physics engine
// Header-only, intentionally simple and float-based
struct Vec2 {
    float x { 0.0f };
    float y { 0.0f };

    // Constructors
    constexpr Vec2() noexcept = default;
    constexpr explicit Vec2(float s) noexcept : x(s), y(s) {}
    constexpr Vec2(float x_, float y_) noexcept : x(x_), y(y_) {}

    // Element access
    float& operator[](int i) noexcept { return (i == 0) ? x : y; }
    constexpr float operator[](int i) const noexcept { return (i == 0) ? x : y; }

    // Compound assignments
    Vec2& operator+=(const Vec2& o) noexcept { x += o.x; y += o.y; return *this; }
    Vec2& operator-=(const Vec2& o) noexcept { x -= o.x; y -= o.y; return *this; }
    Vec2& operator*=(float s) noexcept { x *= s; y *= s; return *this; }
    Vec2& operator/=(float s) noexcept { x /= s; y /= s; return *this; }
};

// Binary vector ops
inline constexpr Vec2 operator+(const Vec2& a, const Vec2& b) noexcept { return Vec2(a.x + b.x, a.y + b.y); }
inline constexpr Vec2 operator-(const Vec2& a, const Vec2& b) noexcept { return Vec2(a.x - b.x, a.y - b.y); }
inline constexpr Vec2 operator-(const Vec2& v) noexcept { return Vec2(-v.x, -v.y); }

// Scalar ops
inline constexpr Vec2 operator*(const Vec2& v, float s) noexcept { return Vec2(v.x * s, v.y * s); }
inline constexpr Vec2 operator*(float s, const Vec2& v) noexcept { return Vec2(v.x * s, v.y * s); }
inline constexpr Vec2 operator/(const Vec2& v, float s) noexcept { return Vec2(v.x / s, v.y / s); }

// Equality
inline constexpr bool operator==(const Vec2& a, const Vec2& b) noexcept { return a.x == b.x && a.y == b.y; }
inline constexpr bool operator!=(const Vec2& a, const Vec2& b) noexcept { return !(a == b); }

// Utilities
inline constexpr float dot(const Vec2& a, const Vec2& b) noexcept { return a.x * b.x + a.y * b.y; }
inline float length(const Vec2& v) noexcept { return std::sqrt(dot(v, v)); }
inline float distance(const Vec2& a, const Vec2& b) noexcept { return length(a - b); }

inline Vec2 normalize(const Vec2& v) noexcept {
    const float len = length(v);
    if (len == 0.0f) return Vec2(0.0f, 0.0f);
    return v / len;
}

// Approximate equality with epsilon but I
inline bool approxEqual(const Vec2& a, const Vec2& b, float eps = 1e-6f) noexcept {
    return std::fabs(a.x - b.x) <= eps && std::fabs(a.y - b.y) <= eps;
}

// Stream output for debugging
inline std::ostream& operator<<(std::ostream& os, const Vec2& v) {
    os << "Vec2(" << v.x << ", " << v.y << ")";
    return os;
}
