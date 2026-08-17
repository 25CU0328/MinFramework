
#include "Quaternion.h"

#include "Vector3.h"

using namespace DirectX;

#include <algorithm>

#pragma region Static Method
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
    DirectX::XMVECTOR vector = DirectX::XMQuaternionRotationRollPitchYaw(
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

// 目標角度まで補間する
Quaternion Quaternion::Slerp(
    const Quaternion& _original,
    const Quaternion& _target,
    const float& _ratio
)
{
    DirectX::XMVECTOR slerpVector = DirectX::XMQuaternionSlerp(
        _original.ToXMVector(_original),
        _target.ToXMVector(_target),
        _ratio
    );

    // 結果をXMVECTORからクォータニオンに転換する
    Quaternion result;
    result = result.FromXMVector(slerpVector);

    return result;
}

// 目標位置に向けるために必要な回転を取得する
Quaternion Quaternion::GetLookAtRotation(
    const Vector3f& _position,
    const Vector3f& _targetPosition,
    const Quaternion& _currentRotation
)
{
    // 注視する時の前方向ベクトル
    Vector3f targetDirection = (_targetPosition - _position).GetNormalized();

    // 目標位置と自身の位置が重なっている場合、単位クォータニオンを返す
    if (targetDirection.GetLength() < 0.00001f)
    {
        return Quaternion::Identity();
    }

    // 自身の回転の方向を目標方向への投影
    Vector3f currentForward = _currentRotation.GetForward();
    float projection = currentForward.Dot(targetDirection);
    projection = std::clamp(projection, -1.0f, 1.0f);

    // 回転軸の方向
    Vector3 rotateAxis = currentForward.Cross(targetDirection).GetNormalized();

    // 回転角度
    float angle = acosf(projection);

    // 回転軸を中心に回転するクォータニオンを作成
    Quaternion result;
    result = result.FromXMVector(DirectX::XMQuaternionRotationAxis(
        DirectX::XMVectorSet(
            rotateAxis.x,
            rotateAxis.y,
            rotateAxis.z,
            0.0f
        ),
        angle
    ));

    return result;
}

// 特定の方向を軸としての回転を取得する
Quaternion Quaternion::GetRotationFromAxis(
    const Vector3f& _axis,
    const float& angle
)
{
    Vector3f normalizedAxis = _axis.GetNormalized();
    // 特定の軸で回転するベクトルを取得する
    DirectX::XMVECTOR vector = DirectX::XMQuaternionRotationAxis(
        DirectX::XMVectorSet(
            normalizedAxis.x,
            normalizedAxis.y,
            normalizedAxis.z,
            0.0f
        ),
        angle
    );

    Quaternion result = Quaternion::Identity();
    return result.FromXMVector(vector);
}

#pragma endregion

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
    XMVECTOR forwardVector = XMVector3Rotate(
        XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),
        ToXMVector(*this)
    );

    // ベクトルをFloat3に保存する
    XMFLOAT3 tempFloat3;
    XMStoreFloat3(&tempFloat3, forwardVector);

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
    XMVECTOR rightVector = XMVector3Rotate(
        XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),
        ToXMVector(*this)
    );

    // ベクトルをFloat3に保存する
    XMFLOAT3 tempFloat3;
    XMStoreFloat3(&tempFloat3, rightVector);

    return Vector3f(
        tempFloat3.x,
        tempFloat3.y,
        tempFloat3.z
    );
}

// 上方向ベクトルを取得する
Vector3f Quaternion::GetUp() const
{
    // 右方向のベクトルを取得する
    XMVECTOR upVector = XMVector3Rotate(
        XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),
        ToXMVector(*this)
    );

    // ベクトルをFloat3に保存する
    XMFLOAT3 tempFloat3;
    XMStoreFloat3(&tempFloat3, upVector);

    return Vector3f(
        tempFloat3.x,
        tempFloat3.y,
        tempFloat3.z
    );
}

// クォータニオンの逆回転を取得
Quaternion Quaternion::GetInverse() const
{
    float length = powf(x, 2) + powf(y, 2) + powf(z, 2) + powf(w, 2);

    Quaternion conjugate = {-x, -y, -z, w};

    return {
        conjugate.x / length,
        conjugate.y / length,
        conjugate.z / length,
        conjugate.w / length,
    };
}

Quaternion Quaternion::operator*(const Quaternion& _quaternion) const
{
    // プロパティのxyzwからベクターを設定する
	XMVECTOR quaternion1 = ToXMVector(*this);

    // 引数のクォータニオンでベクターを設定する
    XMVECTOR quaternion2 = ToXMVector(_quaternion);

    // クォータニオンの掛け算
    XMVECTOR result = XMQuaternionMultiply(quaternion1, quaternion2);

    return FromXMVector(result);
}

// XMVectorからクォータニオンを作る
Quaternion Quaternion::FromXMVector(const DirectX::XMVECTOR& _vector)
{
	return Quaternion{
		DirectX::XMVectorGetX(_vector),
		DirectX::XMVectorGetY(_vector),
		DirectX::XMVectorGetZ(_vector),
		DirectX::XMVectorGetW(_vector)
	};
}

// クォータニオンからXMVectorを作る
DirectX::XMVECTOR Quaternion::ToXMVector(const Quaternion& _quaternion)
{
	return XMVectorSet(
        _quaternion.x, 
        _quaternion.y, 
        _quaternion.z, 
        _quaternion.w
    );
}