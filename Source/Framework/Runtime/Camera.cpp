
#include "Camera.h"

#include "AppDef.h"
using namespace DirectX;

// コンストラクタ
Camera::Camera()
    : m_position(0, 0, 0)
    , m_rotation(Quaternion::Identity())
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
void Camera::SetRotation(const Quaternion& _rotation)
{
    m_rotation = _rotation;
}

// カメラの回転を設定する (オイラー角)
void Camera::SetRotationEuler(const Vector3f& _rotation)
{
    m_rotation = Quaternion::FromEuler(_rotation);
}

// カメラ位置を取得する
Vector3f Camera::GetPosition() const
{
    return m_position;
}

// カメラの回転角度を取得する
Quaternion Camera::GetRotation() const
{
    return m_rotation;
}

// カメラ回転に対応するオイラー角を取得する
Vector3f Camera::GetRotationEuler() const
{
    return m_rotation.ToEuler();
}

// カメラの前方向ベクトルを取得する
Vector3f Camera::GetForward() const
{
    return m_rotation.GetForward();
}

// カメラの右方向ベクトルを取得する
Vector3f Camera::GetRight() const
{
    return m_rotation.GetRight();
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

// 行列を取得する
DirectX::XMMATRIX Camera::GetViewMatrix() const
{
    // カメラ位置を表すベクトルを取得
    XMFLOAT3 position = m_position.ToXMFloat3();
    XMVECTOR cameraPosition = XMLoadFloat3(&position);
   
    // 回転行列を取得
    XMMATRIX rotationMatrix = m_rotation.GetMatrix();
    
    // 移動行列
    XMMATRIX translationMatrix = XMMatrixTranslation(
        m_position.x,
        m_position.y,
        m_position.z
    );

    // 変換行列の逆行列を取得する
    XMVECTOR inverseMatrix;
    return XMMatrixInverse(&inverseMatrix, rotationMatrix * translationMatrix);
}

XMMATRIX Camera::GetProjectionMatrix() const
{
    switch (m_projectionType)
    {
        // 透視投影の場合
    case ProjectionType::Perspective:
        return XMMatrixPerspectiveFovLH(
            m_fov,
            m_aspect,
            m_nearZ,
            m_farZ
        );

        // 正投影の場合
    case ProjectionType::Orthographic:
        return XMMatrixOrthographicLH(
            m_viewWidth,
            m_viewHeight,
            m_nearZ,
            m_farZ
        );
    }

    // 同じ設定がない場合、単位行列を返す
    return XMMatrixIdentity();
}

DirectX::XMMATRIX Camera::GetViewProjectionMatrix() const
{
    return GetViewMatrix() * GetProjectionMatrix();
}