#pragma once
#include <Objects/CHECK_DIR.h>
#include <Scene/GameScene.h>


struct CheckHitObj
{
public:
	Vector2Template<double> operator()(Vector2Template<double>, Vector2Template<int>, OBJ_TYPE, std::shared_ptr<object>, CHECK_DIR);
};

