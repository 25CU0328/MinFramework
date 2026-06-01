
#include "Camera.h"
using namespace Runtime;

#include "AppDef.h"

// コンストラクタ
Camera::Camera()
    : m_position(0, 0, -20)
    , m_rotation(0, 0, 0)
    , m_fov(XM_PIDIV4)
    , m_aspect(static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT))
    , m_nearZ(0.1f)
    , m_farZ(1000.0f)
    , m_projectionType(ProjectionType::Perspective)
{

}
// デストラクター
Camera::~Camera()
{

}

// 初期化処理
void Camera::Init()
{

}

// 位置を設定する
void Camera::SetPosition(const DirectX::XMFLOAT3& _position)
{
    m_position = _position;
}

// 回転角度を設定する
void Camera::SetRotation(const DirectX::XMFLOAT3& _rotation)
{
    m_rotation = _rotation;
}

void Camera::SetView(
    float _fov,
    float _aspect,
    float _nearPlaneDistance,
    float _farPlaneDistance
)
{
    m_fov = _fov;
    m_aspect = _aspect;
    m_nearZ = _nearPlaneDistance;
    m_farZ = _farPlaneDistance;
}

// カメラ位置を取得する
XMFLOAT3 Camera::GetPosition() const
{
    return m_position;
}

// カメラの回転角度を取得する
XMFLOAT3 Camera::GetRotation() const
{
    return m_rotation;
}

// カメラの前方向ベクトルを取得する
XMFLOAT3 Camera::GetFront() const
{
    XMVECTOR forwardVector = XMVectorSet(0, 0, 1, 0);

    XMMATRIX rotateMatrix = XMMatrixRotationRollPitchYaw(
        m_rotation.x,
        m_rotation.y,
        m_rotation.z
    );

    forwardVector = XMVector3TransformNormal(
        forwardVector,
        rotateMatrix
    );
    forwardVector = XMVector3Normalize(forwardVector);

    // XMStoreFLoat3の結果を受け取るための変数
    XMFLOAT3 outFloat;
    XMStoreFloat3(&outFloat, forwardVector);

    return outFloat;
}

// カメラの右方向ベクトルを取得する
XMFLOAT3 Camera::GetRight() const
{
    XMVECTOR forwardVector = XMVectorSet(0, 0, 1, 0);

    XMMATRIX rotateMatrix = XMMatrixRotationRollPitchYaw(
        m_rotation.x,
        m_rotation.y,
        m_rotation.z
    );

    forwardVector = XMVector3TransformNormal(
        forwardVector,
        rotateMatrix
    );
    // 前方向とy軸正方向ベクトルの外積で
    // 右方向ベクトルを取得する
    forwardVector = XMVector3Cross(forwardVector, XMVectorSet(0, 1, 0, 0));
    forwardVector = XMVector3Normalize(forwardVector);

    // XMStoreFLoat3の結果を受け取るための変数
    XMFLOAT3 outFloat;
    XMStoreFloat3(&outFloat, forwardVector);

    return outFloat;
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
    XMVECTOR eyePosition = XMLoadFloat3(&m_position);

    XMVECTOR forward = XMVectorSet(0, 0, 1, 0);

    XMMATRIX rotation = XMMatrixRotationRollPitchYaw(
        m_rotation.x,
        m_rotation.y,
        m_rotation.z
    );

    forward = XMVector3TransformNormal(forward, rotation);

    XMVECTOR target = eyePosition + forward;

    XMVECTOR up = XMVectorSet(0, 1, 0, 0);

    return XMMatrixLookAtLH(
        eyePosition,
        target,
        up
    );
}

XMMATRIX Camera::GetProjectionMatrix() const
{
    switch (m_projectionType)
    {
    case ProjectionType::Perspective:
        return XMMatrixPerspectiveFovLH(
            m_fov,
            m_aspect,
            m_nearZ,
            m_farZ
        );

    case ProjectionType::Orthographic:
        return XMMatrixOrthographicLH(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            m_nearZ,
            m_farZ
        );
    }

    return XMMatrixIdentity();
}

DirectX::XMMATRIX Camera::GetViewProjectionMatrix() const
{
    return GetViewMatrix() * GetProjectionMatrix();
}