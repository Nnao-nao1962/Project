#include <Dxlib.h>
#include "SelectScene.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "SceneMng.h"
#include <algorithm>

SelectScene::SelectScene()
{
	IpImageMng.GetID("space", "image/space.png", { 300,50 }, { 1,1 });
	
}


SelectScene::~SelectScene()
{
}

unique_Base SelectScene::Update(unique_Base own)
{
	auto PlObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj obj) {return (*obj)._unitID == UNIT_ID::PLAYER; });

	if (!FadeUpdate())
	{
		for (auto data : _objList)
		{
			(*data).Update(*PlObj);
		}
	}

	for (auto data : _objList)
	{

		(*data).Draw();
	}

	// �`��̍폜
	_objList.erase(std::remove_if(
		_objList.begin(),									
		_objList.end(),										
		[](sharedObj& obj) {return (*obj).isDead(); }),		
		_objList.end());

	// �`��𑝉�
	switch (IpSceneMng._stageCnt)
	{
	case 1:
		IpSceneMng.AddDrawQue({ IMAGE_ID("space")[0],IpSceneMng.ScreenSize.x / 2,IpSceneMng.ScreenSize.y / 2,0,0,0,LAYER::BG });
		break;
	case 2:
		IpSceneMng.AddDrawQue({ IMAGE_ID("space")[0],IpSceneMng.ScreenSize.x / 2,IpSceneMng.ScreenSize.y / 2,0,0,0,LAYER::BG });
		break;
	case 3:
		IpSceneMng.AddDrawQue({ IMAGE_ID("space")[0],IpSceneMng.ScreenSize.x / 2,IpSceneMng.ScreenSize.y / 2,0,0,0,LAYER::BG });
		break;
	default:
		break;
	}

	if (!IpSceneMng._blendCnt)
	{
		if (((*_Input).state(INPUT_ID::BTN_3).first && !(*_Input).state(INPUT_ID::BTN_3).second) || (_key.A[TRG::TRG_NOW] & !_key.A[TRG::TRG_OLD]))
		{
			return std::make_unique<GameScene>();
		
		}
	}

	return std::move(own);
}

