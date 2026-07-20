#pragma once

#include <DirectXMath.h>

template <class T> class Vector3;
using Vector3f = Vector3<float>;

// クォータニオンを表すクラス
class Quaternion
{
public:
    // オイラー角からクォータニオンを取得する
    static Quaternion FromEuler(const Vector3f& _eulerAngle);
    // オイラー角からクォータニオンを取得する
    static Quaternion FromEuler(
        const float& pitch, 
        const float& yaw, 
        const float& roll
    );

    // 単位
    static Quaternion Identity();

    // オイラー角にキャストする
    Vector3f ToEuler() const;

    // クォータニオンから行列を取得する
    DirectX::XMMATRIX GetMatrix() const;

    // 前方向ベクトルを取得する
    Vector3f GetForward() const;
    // 右方向ベクトルを取得する
    Vector3f GetRight() const;

    Quaternion operator*(const Quaternion& rhs) const;
public:
    float x;
    float y;
    float z;
    float w;

private:
    // XMVECTORにキャストする
    DirectX::XMVECTOR _toXMVector() const;
};