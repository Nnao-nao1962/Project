#include <Scene/TitleScene.h>
#include <algorithm>
#include <math.h>




TitleScene::TitleScene()
{
	// 初期化
	_keyAllOld = 1;
	_theta = 0;
	_sceneMoveFlag = false;
	_mesMoveFlag = true;
	_mesPos_x = -MES_SIZE_X;
}


TitleScene::~TitleScene()
{
}

Base_unq TitleScene::Update(Base_unq scene)
{
	// 何か押されたらキャラ選択へ
	if (!_mesMoveFlag)
	{
		if ((CheckHitKeyAll() > 0 && _keyAllOld == 0) || (SceneMngIns.GetPad() != 0 && SceneMngIns.GetPadOld() == 0))
		{
			_sceneMoveFlag = true;
			_mesMoveFlag = true;
		}
	}
	else
	{
		scene = mesMove(std::move(scene));
	}
	// 現在のキー状態の保存
	_keyAllOld = CheckHitKeyAll();

	Draw();

	// メッセージを上下に動かす用
	_theta = (_theta + 6) % 360;

	return std::move(scene);
}

Base_unq TitleScene::mesMove(Base_unq scene)
{
	_mesPos_x += 100;
	
	// タイトルに入った時と次に行くときのアニメーション処理
	if (!_sceneMoveFlag)
	{
		if (_mesPos_x >= SceneMngIns.ScreenCenter.x)
		{
			_mesPos_x = SceneMngIns.ScreenCenter.x;
			_mesMoveFlag = false;
		}
	}
	else
	{
		if (_mesPos_x >= SceneMngIns.ScreenSize.x + MES_SIZE_X / 2)
		{
			return std::make_unique<CharSelectScene>();
		}
	}

	return std::move(scene);
}

void TitleScene::Draw(void)
{
	//ImageMngIns.AddDraw({ ImageMngIns.getImage("TitleName")[0], _mesPos_x, SceneMngIns.ScreenCenter.y - 70, 0.0, LAYER::UI, 0 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("TitleBack")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("TitleName")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("space")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y+200, 0.0, LAYER::BG, -1000 });
}
