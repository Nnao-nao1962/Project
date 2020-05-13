#include <Dxlib.h>
#include "FuncCheck.h"
#include "GameScene.h"
#include "SceneMng.h"
#include <ImageMng.h>
#include "_DeBugConOut.h"

bool FuncCheckLeft::operator()(ActQueT & actQue, void * scene)
{

	return false;
}


bool FuncCheckOn::operator()(ActQueT & actQue, void * scene)
{
	return false;
}
