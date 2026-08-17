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

    // 目標角度まで補間する
    static Quaternion Slerp(
        const Quaternion& _original,
        const Quaternion& _target,
        const float& _ratio
    );

    // 目標位置に向けるために必要な回転を取得する
    static Quaternion GetLookAtRotation(
        const Vector3f& _position,          // 自身の位置
        const Vector3f& _targetPosition,    // 目標の位置
        const Quaternion& _currentRotation  // 自身の回転
    );

    // 特定の方向を軸としての回転を取得する
    static Quaternion GetRotationFromAxis(
        const Vector3f& _axis,
        const float& angle
    );

	// XMVectorからクォータニオンを作る
	static Quaternion FromXMVector(const DirectX::XMVECTOR& _vector);

	// クォータニオンからXMVectorを作る
	static DirectX::XMVECTOR ToXMVector(const Quaternion& _quaternion);

public:
    // オイラー角にキャストする
    Vector3f ToEuler() const;

    // クォータニオンから行列を取得する
    DirectX::XMMATRIX GetMatrix() const;

    // 前方向ベクトルを取得する
    Vector3f GetForward() const;
    // 右方向ベクトルを取得する
    Vector3f GetRight() const;
    // 上方向ベクトルを取得する
    Vector3f GetUp() const;

    // クォータニオンの逆回転を取得
    Quaternion GetInverse() const;

    // クォータニオンの乗算
    Quaternion operator*(const Quaternion& rhs) const;
public:
    float x;
    float y;
    float z;
    float w;

};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Quaternion, x, y, z, w)