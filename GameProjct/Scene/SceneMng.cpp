#include <Dxlib.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "Obj.h""
#include "ImageMng.h"
#include "SelectScene.h"
#include <algorithm>
#include <KeyState.h>

#include "_DeBugConOut.h"
#include "_DebugDispOut.h"

Key _key;
SceneMng *SceneMng::sInstance=nullptr;

SceneMng::SceneMng() :ScreenSize{ 800,600 }, GameScreenSize{ ScreenSize / 2 }, _flameCnt{ 0 }
{
}

void SceneMng::Draw(void)
{
	_dbgAddDraw();
	
	std::sort(_drawList.begin(), _drawList.end(), [](DrawQueT dQueA, DrawQueT dQueB) {
		return	std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZODER)>(dQueA))
			<
			std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZODER)>(dQueB));
	});

	for (auto layer : LAYER())
	{
		SetDrawScreen(_screenID[layer]);
		ClsDrawScreen();
	}

	
	for (auto dQue : _drawList)
	{
		double x, y, rad;
		int id,size_y;
		LAYER layer_id;

		std::tie(id, x, y, size_y, rad, std::ignore, layer_id) = dQue;

		if (_screenID[layer_id] != GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer_id]);
		}

		switch (layer_id)
		{
		case LAYER::EX:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, IpSceneMng._blendCnt);
			DrawRotaGraph(static_cast<int>(x), static_cast<int>(y) - size_y / 2, 1.0, rad, id, true);
			SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
			break;
		default:
			DrawRotaGraph(static_cast<int>(x), static_cast<int>(y) - size_y / 2, 1.0, rad, id, true);
			break;
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	for (auto layer_id : LAYER())
	{
		DrawRotaGraph(GameScreenSize.x, GameScreenSize.y, 1.0, 0, _screenID[layer_id], true);	
	}

	ScreenFlip();
}

// ｷｰ情報
void SceneMng::GetKeyState(void)
{
	_key.A[TRG::TRG_OLD] = _key.A[TRG::TRG_NOW];
	_key.A[TRG::TRG_NOW] = (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_1);
}

SceneMng::~SceneMng()
{

}

void SceneMng::Run(void)
{
	SysInit();

_activeScene = std::make_unique<TitleScene>();
	//_activeScene = std::make_unique<SelectScene>();
	
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_drawList.clear();
		_dbgStartDraw();
 		_activeScene = (*_activeScene).Update(std::move(_activeScene));

		// 所有権を渡す
		(*_activeScene).RunActQue(std::move(_actList));
		(*_input).Update();

		GetKeyState();
		Draw();

		_frames++;
		_flameCnt++;
	}
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		return false;
	}
	
	_drawList.emplace_back(dQue);
	return true;
}

bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;
}

const int SceneMng::frames(void) const
{
	return _frames;
}

bool SceneMng::SysInit(void)
{
	// システム処理
	SetWindowText("2D迷路");	
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);					
	ChangeWindowMode(true);											
	if (DxLib_Init() == -1)											
	{
		return false;
	}
	
	// ｷｰ情報
	_input = std::make_shared<KeyState>();								
	
	_dbgSetup(215);														
	
	MapSize = { 30,30 };												
	
	// ﾚｲﾔｰ設定
	_screenID.try_emplace(LAYER::BG, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::CHAR, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::UI, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::EX, MakeScreen(ScreenSize.x, ScreenSize.y, true));

	_frames = 0;

	return false;
}
