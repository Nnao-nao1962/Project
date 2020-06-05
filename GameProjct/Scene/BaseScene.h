#pragma once
#include <memory>

#define GUIDE_POS_Y		730
#define BACK_POS_X		140
#define SELECT_POS_X	512
#define NEXT_POS_X		884

#define STICK_INPUT	300

class BaseScene;

using Base_unq = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();

	virtual Base_unq Update(Base_unq scene) = 0;

};

