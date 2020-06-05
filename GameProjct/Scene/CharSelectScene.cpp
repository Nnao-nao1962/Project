#include <iostream>
#include <Scene/SceneMng.h>
#include <Scene/CharSelectScene.h>



CharSelectScene::CharSelectScene()
{
	framPos = 400;
	_cursor = 0;
	_theta = 0;
	_sceneMoveFlag = false;
	_charSel = &CharSelectScene::charMove;

	_keyOld.try_emplace(KEY_INPUT_LEFT, 1);
	_keyOld.try_emplace(KEY_INPUT_RIGHT, 1);
	_keyOld.try_emplace(KEY_INPUT_RSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_LSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_SPACE, 1);
}


CharSelectScene::~CharSelectScene()
{
}

Base_unq CharSelectScene::Update(Base_unq scene)
{
	scene = (this->*_charSel)(std::move(scene));

	Draw();

	return std::move(scene);
}

// 画面遷移
Base_unq CharSelectScene::charMove(Base_unq scene)
{
	_charSelPos_x += 100;
	if (!_sceneMoveFlag)
	{
		if (_charSelPos_x > SceneMngIns.ScreenCenter.x - PL_POS_X)
		{
			_charSelPos_x = SceneMngIns.ScreenCenter.x - PL_POS_X;
			_charSel = &CharSelectScene::charSelect;
		}
	}
	else
	{
		if (_charSelPos_x > SceneMngIns.ScreenSize.x + 400)
		{
			return std::move(_tmpScene);
		}
	}

	return std::move(scene);
}


Base_unq CharSelectScene::charSelect(Base_unq scene)
{
	if ((keyUpdate(KEY_INPUT_LEFT) == 0 && CheckHitKey(KEY_INPUT_LEFT) == 1) || (SceneMngIns.GetStick().x < -STICK_INPUT && SceneMngIns.GetStickOld().x >= -STICK_INPUT))
	{
		_cursor--;
		if (_cursor < 0)
		{
			_cursor = PL_NUMBER;
		}
	}
	if ((keyUpdate(KEY_INPUT_RIGHT) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 1) || (SceneMngIns.GetStick().x > STICK_INPUT && SceneMngIns.GetStickOld().x <= STICK_INPUT))
	{
		_cursor++;
		if (_cursor > PL_NUMBER)
		{
			_cursor = 0;
		}
	}
	if (keyUpdate(KEY_INPUT_SPACE) == 0 && CheckHitKey(KEY_INPUT_SPACE) == 1 || ((SceneMngIns.GetPad() & PAD_INPUT_2) != 0 && (SceneMngIns.GetPadOld() & PAD_INPUT_2) == 0))
	{
		_sceneMoveFlag = true;
		_charSel = &CharSelectScene::charMove;
		StageMngIns.setPlayerColor(_cursor);
		_tmpScene = std::make_unique<StageSelectScene>();
	}

	// カーソルを上下に動かす用
	_theta = (_theta + 6) % 180;

	// カーソルの描画
	//ImageMngIns.AddDraw({ ImageMngIns.getImage("cursor")[0], PL_SPACE * _cursor + _charSelPos_x, 400 + CubeSize + static_cast<int>(std::sin(RAD(_theta)) * 30), 0.0, LAYER::UI, 0 });
	// ガイドの描画
	ImageMngIns.AddDraw({ ImageMngIns.getImage("space")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y+200, 0.0, LAYER::UI, 1000 });

	return std::move(scene);
}

int CharSelectScene::keyUpdate(int key)
{
	if (_keyOld.find(key) == _keyOld.end())
	{
		return 1;
	}

	int tmpState = _keyOld[key];
	_keyOld[key] = CheckHitKey(key);
	return tmpState;
}

void CharSelectScene::Draw(void)
{
	ImageMngIns.AddDraw({ ImageMngIns.getImage("TitleBack")[0], SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	//ImageMngIns.AddDraw({ ImageMngIns.getImage("SelectMes")[0], _charSelPos_x + PL_POS_X, 200, 0.0, LAYER::BG, 0 });
	
	for (int i = 0; i < PL_NUMBER; i++)
	{
		ImageMngIns.AddDraw({ ImageMngIns.getImage("player")[i * 2], 400 +PL_SPACE * i, 400, 0.0, LAYER::CHAR, 0 });
	}

	for (int i = 0; i < PL_NUMBER; i++)
	{
		ImageMngIns.AddDraw({ ImageMngIns.getImage("playerSel")[i * 2], 400 + PL_SPACE * i, 400, 0.0, LAYER::CHAR, 10 });
	}
	ImageMngIns.AddDraw({ ImageMngIns.getImage("charSelFram")[0], framPos, 400, 0.0, LAYER::CHAR, 0 });
	switch (_cursor)
	{
	case 0:
		framPos = 400;
		break;
	case 1:
		framPos = 400+PL_SPACE;
		break;
	default:
		framPos = 400;
		break;
	}

	
}
