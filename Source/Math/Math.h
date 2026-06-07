#pragma once

#include <DirectXMath.h>
#include "Vector.h"

#define PI 3.14159265358979323846
#define PI_F 3.14159265358979323846f

inline float DegToRad(float deg) noexcept { return DirectX::XMConvertToRadians(deg); }
inline float RadToDeg(float rad) noexcept { return DirectX::XMConvertToDegrees(rad); }

static inline float NormalizeDeg(float deg) noexcept {
    // 0～360 未満へ正規化
    deg = std::fmod(deg, 360.0f);
    if (deg < 0.0f) deg += 360.0f;
    // -0.0 対策（見た目のため）
    if (deg == -0.0f) deg = 0.0f;
    return deg;
}

template<typename T>
inline T Lerp(const T& _original, const T& _destination, float _ratio)
{
    return T(_original + (_destination - _original) * _ratio);
}

