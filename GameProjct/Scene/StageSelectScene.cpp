#include <Scene/StageSelectScene.h>



StageSelectScene::StageSelectScene()
{
	stageSelPos = 500;
	_stagePos_x = -720;
	_cursor = 0;
	_sceneMoveFlag = false;
	_stageSel = &StageSelectScene::stageMove;

	_keyOld.try_emplace(KEY_INPUT_LEFT, 1);
	_keyOld.try_emplace(KEY_INPUT_RIGHT, 1);
	_keyOld.try_emplace(KEY_INPUT_UP, 1);
	_keyOld.try_emplace(KEY_INPUT_DOWN, 1);
	_keyOld.try_emplace(KEY_INPUT_RSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_LSHIFT, 1);
	_keyOld.try_emplace(KEY_INPUT_SPACE, 1);

	_stageViewScreen = MakeScreen(STAGE_SIZE_X * 2, STAGE_SIZE_Y * 2, false);
}


StageSelectScene::~StageSelectScene()
{
}

Base_unq StageSelectScene::Update(Base_unq scene)
{
	scene = (this->*_stageSel)(std::move(scene));

	Draw();
	return std::move(scene);
}

Base_unq StageSelectScene::stageMove(Base_unq scene)
{
	_stagePos_x += 100;
	// 次のシーンに行く時のアニメーション処理
	if (!_sceneMoveFlag)
	{
		if (_stagePos_x >= STAGE_OFFSET)
		{
			_stagePos_x = STAGE_OFFSET;
			_stageSel = &StageSelectScene::stageSelect;
		}
	}
	else
	{
		if (_stagePos_x >= SceneMngIns.ScreenSize.x + 400)
		{
			return std::move(_tmpScene);
		}
	}
	return std::move(scene);
}

Base_unq StageSelectScene::stageSelect(Base_unq scene)
{
	// カーソルの上下左右移動
	if ((keyUpdate(KEY_INPUT_LEFT) == 0 && CheckHitKey(KEY_INPUT_LEFT) == 1) || (SceneMngIns.GetStick().x < -STICK_INPUT && SceneMngIns.GetStickOld().x >= -STICK_INPUT))
	{
		_cursor--;
		if (_cursor < 0)
		{
			_cursor = 3;
		}
	}
	if ((keyUpdate(KEY_INPUT_RIGHT) == 0 && CheckHitKey(KEY_INPUT_RIGHT) == 1) || (SceneMngIns.GetStick().x > STICK_INPUT && SceneMngIns.GetStickOld().x <= STICK_INPUT))
	{
		_cursor++;
		if (_cursor > 3)
		{
			_cursor = 0;
		}
	}
	
	// 決定、もどる
	if ((keyUpdate(KEY_INPUT_LSHIFT) == 0 && CheckHitKey(KEY_INPUT_LSHIFT) == 1) || (keyUpdate(KEY_INPUT_RSHIFT) == 0 && CheckHitKey(KEY_INPUT_RSHIFT) == 1) || ((SceneMngIns.GetPad() & PAD_INPUT_3) != 0 && (SceneMngIns.GetPadOld() & PAD_INPUT_3) == 0))
	{
		_sceneMoveFlag = true;
		_stageSel = &StageSelectScene::stageMove;
		_tmpScene = std::make_unique<CharSelectScene>();
	}
	if ((keyUpdate(KEY_INPUT_SPACE) == 0 && CheckHitKey(KEY_INPUT_SPACE) == 1) || ((SceneMngIns.GetPad() & PAD_INPUT_2) != 0 && (SceneMngIns.GetPadOld() & PAD_INPUT_2) == 0))
	{
		_sceneMoveFlag = true;
		_stageSel = &StageSelectScene::stageMove;
		_tmpScene = std::make_unique<GameScene>(_cursor);
	}

	ClsDrawScreen();
	
	return std::move(scene);
}

int StageSelectScene::keyUpdate(int key)
{
	if (_keyOld.find(key) == _keyOld.end())
	{
		return 1;
	}

	int tmpState = _keyOld[key];
	_keyOld[key] = CheckHitKey(key);
	return tmpState;
}

void StageSelectScene::Draw()
{
	ImageMngIns.AddDraw({ ImageMngIns.getImage("TitleBack")[0], 
		SceneMngIns.ScreenCenter.x, SceneMngIns.ScreenCenter.y, 0.0, LAYER::BG, -1000 });
	for (int i = 0; i < STAGE_NUMBER; i++)
	{
		ImageMngIns.AddDraw({ ImageMngIns.getImage("stage")[i],
			250 + (260 * i), 470, 0.0, LAYER::CHAR, 0 });
	}
	//ImageMngIns.AddDraw({ ImageMngIns.getImage("stageSelFrame")[0],
	//	stageSelPos, 470, 0.0, LAYER::CHAR, 0 });
	ImageMngIns.AddDraw({ ImageMngIns.getImage("stageSelFrame")[0],
		SceneMngIns.ScreenCenter.x, 470, 0.0, LAYER::CHAR, 10 });
	switch (_cursor)
	{
	case 0:
		stageSelPos = 500;
		break;
	case 1:
		stageSelPos = 500 + STAGE_SIZE_X;
		break;
	case 2:
		stageSelPos = 500 + STAGE_SIZE_X * 2;
		break;
	default:
		stageSelPos = 500;
		break;
	}
		

	
	
	
}
