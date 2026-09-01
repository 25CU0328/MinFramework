#pragma once

#include "GameComponents.h"


class GameComponentFactory
{
public:
	static GameComponent* CreateComponent(GameComponentType type)
	{
		switch (type)
		{
		case GameComponentType::Transform:
			return new Transform();
			break;

		case GameComponentType::MeshRenderer:
			return new MeshRenderer();
			break;

		case GameComponentType::TextureRenderer:
			return new TextureRenderer();
			break;



		default:
			return nullptr;
		}
	}



};