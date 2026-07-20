
#include "Quaternion.h"

#include "Vector3.h" 

using namespace DirectX;

// オイラー角からクォータニオンを取得する
Quaternion Quaternion::FromEuler(const Vector3f& _eulerAngle)
{
    return FromEuler(
        _eulerAngle.x,
        _eulerAngle.y,
        _eulerAngle.z
    );
}
// オイラー角からクォータニオンを取得する
Quaternion Quaternion::FromEuler(
	const float& pitch,
	const float& yaw,
	const float& roll
)
{
    // オイラー角からベクトルを取得する
    XMVECTOR vector = XMQuaternionRotationRollPitchYaw(
            pitch,
            yaw,
            roll
    );

    // ベクトルからクォータニオンを取得する
    Quaternion result = {
        XMVectorGetX(vector),
        XMVectorGetY(vector),
        XMVectorGetZ(vector),
        XMVectorGetW(vector)
    };

    return result;
}

// 基本
Quaternion Quaternion::Identity()
{
    Quaternion result = { 0.0f, 0.0f, 0.0f, 1.0f };

    return result;
}

// オイラー角にキャストする
Vector3f Quaternion::ToEuler() const
{
    Vector3f result;

    const float squaredX = x * x;
    const float squaredY = y * y;
    const float squaredZ = z * z;

    // Pitch (X軸回転)
    float sinPitch = 2.0f * (w * x - y * z);

    if (fabsf(sinPitch) >= 1.0f)
    {
        result.x = copysignf(
            DirectX::XM_PIDIV2,
            sinPitch
        );
    }
    else
    {
        result.x = asinf(sinPitch);
    }

    // Yaw (Y軸回転)
    result.y = atan2f(
        2.0f * (w * y + x * z),
        1.0f - 2.0f * (squaredX + squaredY)
    );

    // Roll (Z軸回転)
    result.z = atan2f(
        2.0f * (w * z + x * y),
        1.0f - 2.0f * (squaredX + squaredZ)
    );

    return result;
}

// クォータニオンから行列を取得する
DirectX::XMMATRIX Quaternion::GetMatrix() const
{
    XMVECTOR vector = XMVectorSet(x, y, z, w);

    return XMMatrixRotationQuaternion(vector);
}

Vector3f Quaternion::GetForward() const
{
    // 前方向のベクトルを取得する
    XMVECTOR forward = XMVector3Rotate(
        XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),
        _toXMVector()
    );

    // ベクトルをFloat3に保存する
    XMFLOAT3 tempFloat3;
    XMStoreFloat3(&tempFloat3, forward);

    return Vector3f(
        tempFloat3.x,
        tempFloat3.y,
        tempFloat3.z
    );
}

// 右方向ベクトルを取得する
Vector3f Quaternion::GetRight() const
{
    // 右方向のベクトルを取得する
    XMVECTOR right = XMVector3Rotate(
        XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f), 
        _toXMVector()
    );

    // ベクトルをFloat3に保存する
    XMFLOAT3 tempFloat3;
    XMStoreFloat3(&tempFloat3, right);

    return Vector3f(
        tempFloat3.x,
        tempFloat3.y,
        tempFloat3.z
    );
}

Quaternion Quaternion::operator*(const Quaternion& _quaternion) const
{
    XMFLOAT4 tempFloat = { x, y, z, w };
    XMVECTOR quaternion1 = XMLoadFloat4(&tempFloat);

    tempFloat = {
        _quaternion.x, 
        _quaternion.y, 
        _quaternion.z, 
        _quaternion.w
    };
    XMVECTOR quaternion2 = XMLoadFloat4(&tempFloat);

    XMVECTOR result = XMQuaternionMultiply(quaternion1, quaternion2);

    Quaternion q;

    XMStoreFloat4(&tempFloat,result);

    return {tempFloat.x, tempFloat.y, tempFloat.z, tempFloat.w};
}

// XMVECTORにキャストする
DirectX::XMVECTOR Quaternion::_toXMVector() const
{
    return XMVectorSet(x, y, z, w);
}