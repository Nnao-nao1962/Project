#include "TitleScene.h"
#include "SelectScene.h"
#include "algorithm"
#include "GameScene.h"
#include <Dxlib.h>
#include "ImageMng.h"
#include "SceneMng.h"
#include <Stage.h>
#include <FuncCheck.h>
#include <map>


TitleScene::TitleScene()
{
	IpSceneMng._stageCnt = 1;
	IpSceneMng._scoreCnt = 0;
	IpSceneMng._liveCnt = 3;

	MapInit();
	//funcInit();

}

TitleScene::~TitleScene()
{
}

// �X�V
unique_Base TitleScene::Update(unique_Base own)
{
	if (IpSceneMng._flameCnt % 100 / 50)
	{
		IpSceneMng.AddDrawQue({ IMAGE_ID("spaceP")[0],
				IpSceneMng.GameScreenSize.x,IpSceneMng.GameScreenSize.y + 200,0,0,150,LAYER::BG });
	}
	

	// ID�AX�AY�A����Y�A��]�AZ���ް�Aڲ԰ID
	IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0],400,300,0,0,0,LAYER::BG});
	IpSceneMng.AddDrawQue({ IMAGE_ID("�^�C�g��")[0],
		IpSceneMng.GameScreenSize.x,IpSceneMng.GameScreenSize.y - 90,0,0,100,LAYER::BG });
	
	if (!IpSceneMng._blendCnt)
	{
		if(CheckHitKey(KEY_INPUT_SPACE))
		{
			return std::make_unique<SelectScene>();
			//return std::make_unique<GameScene>();
		}
	}

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

	_objList.erase(std::remove_if
	(
		_objList.begin(),	
		_objList.end(),								
		[](sharedObj& obj) {return (*obj).isDead(); }),
		_objList.end());

	return std::move(own);
}

// �}�b�v������
void TitleScene::MapInit(void)
{
	IpImageMng.GetID("�w�i", "image/back.png", { 800,600 }, { 1,1 });
	IpImageMng.GetID("�^�C�g��", "image/title.png", { 450,300 }, { 1,1 });
	IpImageMng.GetID("spaceP", "image/spaceP.png", { 400,50 }, { 1,1 });
	IpImageMng.GetID("��", "image/white.png", { 800,600 }, { 1,1 });
	IpImageMng.GetID("�u���b�N", "image/block.png", { 30,30 }, { 9,2 });
	
	_mapPos = { 0,0 };

	//_objList.emplace_back(new Player({ 120,495+15 }, { 30,30 }));

	StageState Floordata;
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			switch (IpSceneMng.map[MAP_Y][MAP_X])
			{
			case 4: 
				Floordata = { BLOCK_TYPE::�u���b�N�P,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(Floordata));
				break;
			case 5:
				Floordata = { BLOCK_TYPE::�u���b�N�Q,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(Floordata));
				break;
			case 10:
				Floordata = { BLOCK_TYPE::�u���b�N�R,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(Floordata));
				break;
			default:
				break;
			}
		}
	}
}


void TitleScene::RunActQue(std::vector<ActQueT> actList)
{
	for (auto actQue : actList)
	{
		try
		{
			funcQue.at(actQue.first)(actQue, this);
		}
		catch (...)
		{
			//AST();
		}

	}
}

void TitleScene::funcInit(void)
{
	funcQue[ACT_QUE::CHECK_LEFT] = FuncCheckLeft();
}
