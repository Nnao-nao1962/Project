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

// 更新
unique_Base TitleScene::Update(unique_Base own)
{
	if (IpSceneMng._flameCnt % 50 / 40)
	{
		IpSceneMng.AddDrawQue({ IMAGE_ID("space")[0],IpSceneMng.ScreenSize.x / 2,IpSceneMng.ScreenSize.y / 5*4,0,0,200,LAYER::BUTTON});
	}
	

	// ID、X、Y、ｻｲｽﾞY、回転、Zｵｰﾀﾞｰ、ﾚｲﾔｰID
	IpSceneMng.AddDrawQue({ IMAGE_ID("背景")[0],400,300,0,0,0,LAYER::BG});
	//IpSceneMng.AddDrawQue({ IMAGE_ID("タイトル")[0],IpSceneMng.ScreenSize.x/2,IpSceneMng.ScreenSize.y / 2-100,0,0,0,LAYER::BG });
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

// マップ初期化
void TitleScene::MapInit(void)
{

	IpImageMng.GetID("space", "image/space.png", { 300,50 }, { 1,1 });
	IpImageMng.GetID("背景", "image/backImage.jpg", { 800,600 }, { 1,1 });
	IpImageMng.GetID("ブロック", "image/block.png", { 30,30 }, { 9,2 });
	
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
				Floordata = { BLOCK_TYPE::ブロック１,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(Floordata));
				break;
			case 5:
				Floordata = { BLOCK_TYPE::ブロック２,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
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
