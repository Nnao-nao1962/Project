#include <Dxlib.h>
#include "_DeBugConOut.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "algorithm"
#include "Vector2.h"
#include "SceneMng.h"
#include "Obj.h"
#include "FuncCheck.h"
#include "TitleScene.h"
#include "Stage.h"
#include "SelectScene.h"

GameScene::GameScene()
{	
	TRACE("¹Þ°Ñ¼°ÝÌ¶¬");
	///funcInit();
	IpSceneMng._timeLimitCnt = 300;
	IpSceneMng._liveFlag = true;
	IpSceneMng._endFlag = false;
	IpSceneMng._stageCnt =1;	// 3iKÌ\è
	
	
	// À²ÄÙA¹Þ°Ñµ°ÊÞ°æÊÌo^

	switch (IpSceneMng._stageCnt)
	{
	case 1:
		MapInit();
		break;
	case 2:
		MapInit();
		break;
	case 3:
		MapInit();
		break;
	default:
		AST();
		break;
	}

	_shakeCount = 0;
}


GameScene::~GameScene()
{

}

unique_Base GameScene::Update(unique_Base own)
{
	// `æ
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

	switch (IpSceneMng._stageCnt)
	{
	case 1:
		//IpSceneMng.AddDrawQue({ IMAGE_ID("wi")[0], 4096 / 2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });
		TRACE("¹Þ°Ñ¼°Ý1wiÌ¶¬");
		IpSceneMng.AddDrawQue({ IMAGE_ID("wi")[0], 400,300,0,0,0,LAYER::BG });
		break;
	case 2:
		IpSceneMng.AddDrawQue({ IMAGE_ID("wi")[0], 400 ,300 / 2,0,0,0,LAYER::BG });
		break;
	case 3:
		IpSceneMng.AddDrawQue({ IMAGE_ID("wi")[0],400,300,0,0,0,LAYER::BG });
		break;
	default:
		AST();
		break;
	}
	
	_objList.erase(std::remove_if(
		_objList.begin(),									// `FbNÍÍÌJn
		_objList.end(),										// `FbNÍÍÌI¹
		[](sharedObj& obj) {return (*obj).isDead(); }),		// _®()
		_objList.end());



	/*if (IpSceneMng._endFlag)
	{
		return std::make_unique<GameScene>();	
	}*/
	return std::move(own);
}

void GameScene::RunActQue(std::vector<ActQueT> actList)
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

// NX1
void GameScene::MapInit(void)
{
	// `æðÇÝÞ
	IpImageMng.GetID("ubN", "image/block.png", { 30,30 }, { 9,2 });	
	IpImageMng.GetID("wi", "image/bakeImage.jpg", { 800,600 }, { 1, 1 });

	
	_mapPos = { 0,0 };

	
	// csvt@CðÇÝÞ
	int type = NULL;
	int y = 0;
	int x = 0;
	FILE* fp = NULL;
	fopen_s(&fp, "csv/2.csv", "rb");
	while (fscanf_s(fp, "%d", &type) != EOF)
	{
		//TRACE("Ï¯ÌßÃÞ°ÀÌÇÝÝ");
		IpSceneMng.map[MAP_Y][MAP_X] = type;
	}
	
		
	StageState stageState;
	
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			switch (IpSceneMng.map[MAP_Y][MAP_X])
			{
			case 4:
				//TRACE("ÌÞÛ¯¸ÌÇÝÝ");
				stageState = { BLOCK_TYPE::ubNP,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(stageState));
				break;
			case 5:
				stageState = { BLOCK_TYPE::ubNQ,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(stageState));
				break;
			default:
				break;
			}
			if (IpSceneMng.map[y][x] == 4)
			{
				stageState = { BLOCK_TYPE::ubNQ,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(stageState));
			}
		}
	}
}



void GameScene::funcInit(void)
{
	funcQue[ACT_QUE::CHECK_LEFT] = FuncCheckLeft();
	funcQue[ACT_QUE::CHECK_UP] = FuncCheckOn();
}


