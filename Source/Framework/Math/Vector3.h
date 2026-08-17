#pragma once

#include <string>

#include <DirectXMath.h>

// jsonにシリアライズをするためにインクルード
#include "nlohmann/json.hpp"

template <class T>
class Vector3
{
public:
	T x;
	T y;
	T z;

	// コンストラクタ
public:
	Vector3() noexcept :x((T)0), y((T)0), z((T)0) {}
	Vector3(T _x, T _y, T _z) noexcept :x(_x), y(_y), z(_z) {}

	// 方向ベクトル
public:
	// 右方向
	static Vector3<T> Right() {
		return Vector3<T>(
			static_cast<T>(1),
			static_cast<T>(0),
			static_cast<T>(0)
		);
	}
	// 前方向
	static Vector3<T> Forward() {
		return Vector3<T>(
			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(1)
		);
	}
	// 上方向
	static Vector3<T> Up() {
		return Vector3<T>(
			static_cast<T>(0),
			static_cast<T>(1),
			static_cast<T>(0)
		);
	}

	// DirectXのXMVECTORからキャストする
	static Vector3<T> FromXMVector(const DirectX::XMVECTOR& _vector) {
		return Vector3<T>(
			static_cast<T>(DirectX::XMVectorGetX(_vector)),
			static_cast<T>(DirectX::XMVectorGetY(_vector)),
			static_cast<T>(DirectX::XMVectorGetZ(_vector))
		);
	}

	// DirectXのXMVECTORにキャストする
	static DirectX::XMVECTOR ToXMVector(const Vector3<T>& _vector) {
		return DirectX::XMVectorSet(
			static_cast<float>(_vector.x),
			static_cast<float>(_vector.y),
			static_cast<float>(_vector.z),
			1.0f
		);
	}

public:
	// ベクトルの長さを取得する
	T GetLength() const noexcept;
	// 正規化されたベクトルを取得する
	Vector3<T> GetNormalized() const noexcept;
	// 他のベクトルとの内積を取得する
	T Dot(const Vector3<T>& _vector) const noexcept;
	// 他のベクトルとの外積を取得する
	Vector3<T> Cross(const Vector3<T>& _vector) const noexcept;
	// 回転されたベクトルを取得する
	Vector3<T> GetRotated(float yaw, float pitch, float roll) noexcept;
	// ベクトルを表す文字列を取得する
	std::string GetString() const noexcept;
	// DirectXのXMFLOAT3にキャストする
	DirectX::XMFLOAT3 ToXMFloat3() const noexcept;

	// オペレーターオーバーロード
public:
	Vector3<T> operator+(const Vector3<T>& _vector) const noexcept;
	Vector3<T> operator-(const Vector3<T>& _vector) const noexcept;
	Vector3<T> operator*(const T& _scale) const noexcept;
	Vector3<T> operator/(const T& _scale) const noexcept;
	Vector3<T>& operator=(const Vector3<T>& _vector) noexcept;
	Vector3<T>& operator+=(const Vector3<T>& _vector) noexcept;
	Vector3<T>& operator-=(const Vector3<T>& _vector) noexcept;
	Vector3<T>& operator*=(const T& _scale) noexcept;
	Vector3<T>& operator/=(const T& _scale) noexcept;
	bool operator==(const Vector3<T>& _vector) const noexcept;
	bool operator!=(const Vector3<T>& _vector) const noexcept;

};

//ベクトルの大きさ（長さ）取得
template<typename T>
inline T Vector3<T>::GetLength()const noexcept {
	DirectX::XMVECTOR v = DirectX::XMVectorSet(
		static_cast<float>(x),
		static_cast<float>(y),
		static_cast<float>(z),
		0.0f
	);
	float len = 0.0f;
	DirectX::XMStoreFloat(&len, DirectX::XMVector3Length(v));
	return static_cast<T>(len);
}

//自分を正規化します
template<typename T>
inline Vector3<T> Vector3<T>::GetNormalized()const noexcept {
	const float len = static_cast<float>(GetLength());

	// ※FLT_EPSILONはfloatの最小限
	if (len > FLT_EPSILON) {
		return Vector3<T>(
			static_cast<T>(x / len),
			static_cast<T>(y / len),
			static_cast<T>(z / len)
		);
	}
	else {
		return Vector3<T>(
			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(0)
		);
	}
}
// 内積
template<typename T>
inline T Vector3<T>::Dot(const Vector3<T>& _vector) const noexcept
{
	return (x * _vector.x)
		+ (y * _vector.y)
		+ (z * _vector.z);
}

template<typename T>
inline Vector3<T> Vector3<T>::GetRotated(
	float yaw, float pitch, float roll
) noexcept {
	using namespace DirectX;
	const XMVECTOR v = XMVectorSet((float)x, (float)y, (float)z, 0.0f);
	const XMMATRIX R = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);
	XMVECTOR rotatedVector = XMVector3Transform(v, R);

	return Vector3(
		(T)XMVectorGetX(rotatedVector),
		(T)XMVectorGetY(rotatedVector),
		(T)XMVectorGetZ(rotatedVector)
	);
}
// ベクトルを表す文字列を取得する
template<typename T>
inline std::string Vector3<T>::GetString()  const noexcept
{
	std::string str = "";

	str += "(" + std::to_string(x)
		+ ", " + std::to_string(y)
		+ ", " + std::to_string(z)
		+ ")";

	return str;
}

// DirectXのXMFLOAT3にキャストする
template<typename T>
inline DirectX::XMFLOAT3 Vector3<T>::ToXMFloat3() const noexcept
{
	return DirectX::XMFLOAT3(
		static_cast<float>(x),
		static_cast<float>(y),
		static_cast<float>(z)
	);
}

// 外積
template<typename T>
inline Vector3<T> Vector3<T>::Cross(const Vector3<T>& _vector) const noexcept
{
	return Vector3<T>(
		(y * _vector.z) - (z * _vector.y),
		(z * _vector.x) - (x * _vector.z),
		(x * _vector.y) - (y * _vector.x)
	);
}


#pragma region Operator Override
template<typename T>
inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& _vector) const noexcept
{
	return Vector3<T>(
		x + _vector.x,
		y + _vector.y,
		z + _vector.z
	);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& _vector) const noexcept
{
	return Vector3<T>(
		x - _vector.x,
		y - _vector.y,
		z - _vector.z
	);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator*(const T& _scale) const noexcept
{
	return Vector3<T>(
		x * _scale,
		y * _scale,
		z * _scale
	);
}

template<typename T>
inline Vector3<T> Vector3<T>::operator/(const T& _scale) const noexcept
{
	return Vector3<T>(
		x / _scale,
		y / _scale,
		z / _scale
	);
}

// =オペレーターオペレーター
template<typename T>
inline Vector3<T>& Vector3<T>::operator=(const Vector3<T>& _vector) noexcept {
	x = _vector.x;
	y = _vector.y;
	z = _vector.z;

	return *this;
}

// +=オペレーターオペレーター
template<typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& _vector) noexcept {
	x += _vector.x;
	y += _vector.y;
	z += _vector.z;

	return *this;
}

// -=オペレーターオペレーター
template<typename T>
inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& _vector) noexcept {
	x -= _vector.x;
	y -= _vector.y;
	z -= _vector.z;

	return *this;
}

// *=オペレーターオペレーター
template<typename T>
inline Vector3<T>& Vector3<T>::operator*=(const T& _scale) noexcept {
	x *= _scale;
	y *= _scale;
	z *= _scale;

	return *this;
}

// /=オペレーターオペレーター
template<typename T>
inline Vector3<T>& Vector3<T>::operator/=(const T& _scale) noexcept {
	assert(_scale != 0);
	x /= _scale;
	y /= _scale;
	z /= _scale;

	return *this;
}

// ==オペレーターオペレーター
template<typename T>
inline bool Vector3<T>::operator==(const Vector3<T>& _vector) const noexcept {
	return fabs(x - _vector.x) <= (T)1e-6
		&& fabs(y - _vector.y) <= (T)1e-6
		&& fabs(z - _vector.z) <= (T)1e-6;
}

// !=オペレーターオペレーター
template<typename T>
inline bool Vector3<T>::operator!=(const Vector3<T>& _vector) const noexcept {
	return fabs(x - _vector.x) > (T)1e-6
		&& fabs(y - _vector.y) > (T)1e-6
		&& fabs(z - _vector.z) > (T)1e-6;
}

#pragma endregion

//汎用ベクトル3次元ベクトル型定義
using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector3d = Vector3<double>;

// シリアライズするためのマクロ
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector3f, x, y, z)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector3i, x, y, z)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector3d, x, y, z)