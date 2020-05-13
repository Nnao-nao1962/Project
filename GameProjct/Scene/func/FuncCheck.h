#pragma once
#include "Scene/BaseScene.h"

struct FuncCheckLeft
{
	bool operator()(ActQueT & actQue, void * scene);
};

struct FuncCheckOn
{
	bool operator()(ActQueT & actQue, void * scene);
};



