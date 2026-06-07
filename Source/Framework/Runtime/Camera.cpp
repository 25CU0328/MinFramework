
#include "Camera.h"
using namespace Runtime;

#include "AppDef.h"

// コンストラクタ
Camera::Camera()
    : m_position(0, 0, 0)
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
void Camera::Init(ProjectionType _type)
{
    if (_type == ProjectionType::Perspective)
    {
        m_fov = XM_PIDIV4;
        m_aspect = (static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT));
        m_nearZ = 0.1f;
        m_farZ = 1000.0f;

        
    }
    else
    {
        m_viewWidth = static_cast<float>(WINDOW_WIDTH);
        m_viewHeight = static_cast<float>(WINDOW_HEIGHT);
        m_nearZ = 0.1f;
        m_farZ = 100.0;

        m_position = Vector3f(0.0f, 0.0f, -1.0f);
    }

    m_projectionType = _type;
}

// 位置を設定する
void Camera::SetPosition(const Vector3f& _position)
{
    m_position = _position;
}

// 回転角度を設定する
void Camera::SetRotation(const Vector3f& _rotation)
{
    m_rotation = _rotation;
}

// カメラ位置を取得する
Vector3f Camera::GetPosition() const
{
    return m_position;
}

// カメラの回転角度を取得する
Vector3f Camera::GetRotation() const
{
    return m_rotation;
}

// カメラの前方向ベクトルを取得する
Vector3f Camera::GetFront() const
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

    return Vector3f(outFloat.x, outFloat.y, outFloat.z);
}

// カメラの右方向ベクトルを取得する
Vector3f Camera::GetRight() const
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

    return Vector3f(outFloat.x, outFloat.y, outFloat.z);
}

// カメラの投影方式を透視投影に設定する
void Camera::SetPerspective(
    const float _fov,
    const float _aspect,
    const float _nearZ,
    const float _farZ
)
{
    m_fov = _fov;
    m_aspect = _aspect;
    m_nearZ = _nearZ;
    m_farZ = _farZ;

    m_projectionType = ProjectionType::Perspective;
}

// カメラの投影方式を正投影に設定する
void Camera::SetOthographics(
    const float _width,
    const float _height,
    const float _nearZ,
    const float _farZ
)
{
    m_viewWidth = _width;
    m_viewHeight = _height;
    m_nearZ = _nearZ;
    m_farZ = _farZ;

    m_projectionType = ProjectionType::Perspective;
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
    XMFLOAT3 position = XMFLOAT3(
        m_position.x,
        m_position.y,
        m_position.z
    );
    XMVECTOR eyePosition = XMLoadFloat3(&position);

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
            m_viewWidth,
            m_viewHeight,
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