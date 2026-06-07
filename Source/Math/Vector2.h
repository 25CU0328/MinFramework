#pragma once

#include <cmath>
#include "string"
#include "Math.h"

template <class T>
class Vector2
{
public:
	T x;
	T y;

	// コンストラクタ
public:
	Vector2() noexcept :x((T)0), y((T)0) {}
	Vector2(T _x, T _y) noexcept :x(_x), y(_y) {}

public:
	// ベクトルの距離を取得する
	T GetLength() const noexcept;
	// 正規化されたベクトルを取得する
	Vector2<T> GetNormalized() const noexcept;
	// 回転された(時計回り)ベクトルを取得する
	Vector2<T> GetRotated(float _degree) const noexcept;
	// 他のベクトルとの内積を取得する
	T Dot(const Vector2<T>& _vector) const noexcept;
	// ベクトルを表す文字列を取得する
	std::string GetString() const noexcept;

	// オペレーターオーバーロード
public:
	Vector2<T> operator+(const Vector2<T>& _vector) noexcept;
	Vector2<T> operator-(const Vector2<T>& _vector) noexcept;
	Vector2<T> operator*(const T& _scale) noexcept;
	Vector2<T> operator/(const T& _scale) noexcept;
	Vector2<T>& operator=(const Vector2<T>& _vector) noexcept;
	Vector2<T>& operator+=(const Vector2<T>& _vector) noexcept;
	Vector2<T>& operator-=(const Vector2<T>& _vector) noexcept;
	Vector2<T>& operator*=(const T& _scale) noexcept;
	Vector2<T>& operator/=(const T& _scale) noexcept;
	bool operator==(const Vector2<T>& _vector) noexcept;
	bool operator!=(const Vector2<T>& _vector) noexcept;


	
};

// ベクトルの距離を取得する
template<typename T>
inline T Vector2<T>::GetLength() const noexcept
{
	DirectX::XMVECTOR xmVector = DirectX::XMVectorSet(
		static_cast<float>(x),
		static_cast<float>(y),
		0.0f,
		0.0f
	);
	float len = 0.0f;
	DirectX::XMStoreFloat(&len, DirectX::XMVector3Length(xmVector));
	return static_cast<T>(len);
}

// 正規化されたベクトルを取得する
template<typename T>
inline Vector2<T> Vector2<T>::GetNormalized() const noexcept
{
	const float len = static_cast<float>(GetLength());

	// ※FLT_EPSILONはfloatの最小限
	if (len > FLT_EPSILON) {
		x = static_cast<T>(x / len);
		y = static_cast<T>(y / len);
	}
	else {
		x = y = static_cast<T>(0);
	}
}

// 回転された(時計回り)ベクトルを取得する
template<typename T>
inline Vector2<T> Vector2<T>::GetRotated(float _degree) const noexcept
{
	float radian = DegToRad(_degree);
	float sin = std::sin(radian);
	float cos = std::cos(radian);
	
	return Vector2<T>(
		x * static_cast<T>(cos) - y * static_cast<T>(sin),
		y * static_cast<T>(sin) + x * static_cast<T>(cos)
	);
}

// 他のベクトルとの内積を取得する
template<typename T>
inline T Vector2<T>::Dot(const Vector2<T>& _vector) const noexcept
{
	return (x * _vector.x) + (y * _vector.y);
}

// ベクトルを表す文字列を取得する
template<typename T>
inline std::string Vector2<T>::GetString()  const noexcept
{
	std::string str = "";

	str += "(" + std::to_string(x)
		+ ", " + std::to_string(y)
		+ ")";

	return str;
}

#pragma region Operator Override
template<typename T>
inline Vector2<T> Vector2<T>::operator+(const Vector2<T>& _vector) noexcept
{
	return Vector2<T>(
		x + _vector.x,
		y + _vector.y
	);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator-(const Vector2<T>& _vector) noexcept
{
	return Vector2<T>(
		x - _vector.x,
		y - _vector.y
	);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator*(const T& _scale) noexcept
{
	return Vector2<T>(
		x * _scale,
		y * _scale
	);
}

template<typename T>
inline Vector2<T> Vector2<T>::operator/(const T& _scale) noexcept
{
	return Vector2<T>(
		x / _scale,
		y / _scale
	);
}

// =オペレーターオペレーター
template<typename T>
inline Vector2<T>& Vector2<T>::operator=(const Vector2<T>& _vector) noexcept {
	x = _vector.x;
	y = _vector.y;
	return *this;
}

// +=オペレーターオペレーター
template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& _vector) noexcept {
	x += _vector.x;
	y += _vector.y;
	return *this;
}

// -=オペレーターオペレーター
template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& _vector) noexcept {
	x -= _vector.x;
	y -= _vector.y;
	return *this;
}

// *=オペレーターオペレーター
template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(const T& _scale) noexcept {
	x *= _scale;
	y *= _scale;
	return *this;
}

// /=オペレーターオペレーター
template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(const T& _scale) noexcept {
	assert(_scale != 0);
	x /= _scale;
	y /= _scale;
	return *this;
}

// ==オペレーターオペレーター
template<typename T>
inline bool Vector2<T>::operator==(const Vector2<T>& _vector) noexcept {
	return fabs(x - _vector.x) <= (T)1e-6
		&& fabs(y - _vector.y) <= (T)1e-6;
}

// !=オペレーターオペレーター
template<typename T>
inline bool Vector2<T>::operator!=(const Vector2<T>& _vector) noexcept {
	return fabs(x - _vector.x) > (T)1e-6
		&& fabs(y - _vector.y) > (T)1e-6;
}

#pragma endregion

template<typename T>
Vector2<T> Lerp(
	const Vector2<T>& _originalVector,
	const Vector2<T>& _targetVector,
	T _ratio
) noexcept
{
	return Vector2<T>(
		_originalVector.x + (_targetVector.x - _originalVector.x) * _ratio,
		_originalVector.y + (_targetVector.y - _originalVector.y) * _ratio
	);
}

//汎用ベクトル2次元ベクトル型定義
using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2d = Vector2<double>;