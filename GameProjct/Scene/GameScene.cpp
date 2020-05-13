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
	funcInit();
	IpSceneMng._timeLimitCnt = 300;
	IpSceneMng._liveFlag = true;
	IpSceneMng._endFlag = false;
	IpSceneMng._stageCnt = 3;	// 3�i�K�̗\��
	
	
	// ���فA�ްѵ��ް��ʂ̓o�^

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
	// �`��
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
		IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0], 4096 / 2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });
		break;
	case 2:
		IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0], 4096 / 2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });
		break;
	case 3:
		IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0], 4096 / 2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });
		break;
	default:
		AST();
		break;
	}
	
	_objList.erase(std::remove_if(
		_objList.begin(),									// �`�F�b�N�͈͂̊J�n
		_objList.end(),										// �`�F�b�N�͈͂̏I��
		[](sharedObj& obj) {return (*obj).isDead(); }),		// �����_��()
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

// �N���X1
void GameScene::MapInit(void)
{
	// �`���ǂݍ���
	IpImageMng.GetID("�u���b�N", "image/block.png", { 30,30 }, { 9,2 });		
	
	_mapPos = { 0,0 };
	
	// csv�t�@�C����ǂݍ���
	int type = NULL;
	int y = 0;
	int x = 0;
	FILE* fp = NULL;
	fopen_s(&fp, "csv/1.csv", "rb");
	while (fscanf_s(fp, "%d", &type) != EOF)
	{
		IpSceneMng.mapNow[y][x] = type;
		x++;
	}

	StageState stageState;
	
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			switch (IpSceneMng.mapNow[y][x])
			{
			case 4:
				stageState = { BLOCK_TYPE::�u���b�N�P,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
				_objList.emplace_back(new Stage(stageState));
				break;
			case 5:
				stageState = { BLOCK_TYPE::�u���b�N�Q,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,20} };
				_objList.emplace_back(new Stage(stageState));
				break;
			default:
				break;
			}
		}
	}
}



void GameScene::funcInit(void)
{
	funcQue[ACT_QUE::CHECK_LEFT] = FuncCheckLeft();
	funcQue[ACT_QUE::CHECK_UP] = FuncCheckOn();
}


