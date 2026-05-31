#pragma once

#include <DirectXMath.h>

#include "Assets/Image/ImageData.h"
#include "Texture.h"

namespace Runtime
{
	class Sprite
	{
		// コピーを禁止する
		Sprite(const Sprite&) = delete;
		// オペレーターによるコピーを禁止する
		void operator = (const Sprite&) = delete;

	public:
		// コンストラクタ
		Sprite();
		// デストラクター
		~Sprite();

		

	private:
		ImageData m_data;

		DirectX::XMFLOAT2 m_size;
		DirectX::XMFLOAT2 m_position;
		DirectX::XMFLOAT2 m_rotation;
	};
}