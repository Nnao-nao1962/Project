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
	TRACE("ｹﾞｰﾑｼｰﾝの生成");
	///funcInit();
	IpSceneMng._timeLimitCnt = 300;
	IpSceneMng._liveFlag = true;
	IpSceneMng._endFlag = false;
	IpSceneMng._stageCnt =1;	// 3段階の予定
	
	
	// ﾀｲﾄﾙ、ｹﾞｰﾑｵｰﾊﾞｰ画面の登録

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
	// 描画
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
		//TRACE("ｹﾞｰﾑｼｰﾝ1背景の生成");
		IpSceneMng.AddDrawQue({ IMAGE_ID("背景")[0],
			IpSceneMng.GameScreenSize.x,IpSceneMng.GameScreenSize.y,0,0,0,LAYER::BG });
		break;
	case 2:
		/*IpSceneMng.AddDrawQue({ IMAGE_ID("背景")[0],
			IpSceneMng.GameScreenSize.x,IpSceneMng.GameScreenSize.y,0,0,0,LAYER::BG });*/
		break;
	case 3:
		/*IpSceneMng.AddDrawQue({ IMAGE_ID("背景")[0],
			IpSceneMng.GameScreenSize.x,IpSceneMng.GameScreenSize.y,0,0,0,LAYER::BG });*/
		break;
	default:
		AST();
		break;
	}
	
	_objList.erase(std::remove_if(
		_objList.begin(),									// チェック範囲の開始
		_objList.end(),										// チェック範囲の終了
		[](sharedObj& obj) {return (*obj).isDead(); }),		// ラムダ式()
		_objList.end());



	if (IpSceneMng._endFlag)
	{
		return std::make_unique<GameScene>();	
	}
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

void GameScene::MapInit(void)
{
	// 描画を読み込む
	IpImageMng.GetID("ブロック", "image/block.png", { 30,30 }, { 9,2 });	
	//IpImageMng.GetID("背景", "image/bakeImage.jpg", { 800,600 }, { 1, 1 });
	//IpImageMng.GetID("白", "image/white.png", { 800,600 }, { 1, 1 });

	
	_mapPos = { 0,0 };

	
	// csvﾌｧｲﾙを読み込む
	int type = NULL;
	int y = 0;
	int x = 0;
	FILE* fp = NULL;
	fopen_s(&fp, "csv/1.csv", "rb");
	while (fscanf_s(fp, "%d", &type) != EOF)
	{
		TRACE("ﾏｯﾌﾟﾃﾞｰﾀの読み込み");
		IpSceneMng.map[MAP_Y][MAP_X] = type;
	}
	
		
	StageState stageState;
	
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			switch (IpSceneMng.map[MAP_Y][MAP_X])
			{
			case 1:
				TRACE("ﾌﾞﾛｯｸの読み込み");
				stageState = { BLOCK_TYPE::ブロック１,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(stageState));
				break;
			case 2:
				//TRACE("ﾌﾞﾛｯｸの読み込み");
				stageState = { BLOCK_TYPE::ブロック２,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(stageState));
				break;
			case 3:
				//TRACE("ﾌﾞﾛｯｸの読み込み");
				stageState = { BLOCK_TYPE::ブロック３,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(stageState));
				break;
			case 4:
				//TRACE("ﾌﾞﾛｯｸの読み込み");
				stageState = { BLOCK_TYPE::ブロック４,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(stageState));
				break;
			case 6:
				//TRACE("ﾌﾞﾛｯｸの読み込み");
				stageState = { BLOCK_TYPE::ブロックSP,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(stageState));
				break;
			default:
				break;
			}
			if (IpSceneMng.map[y][x] == 4)
			{
				stageState = { BLOCK_TYPE::ブロック３,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
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


