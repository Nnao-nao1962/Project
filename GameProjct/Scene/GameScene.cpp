#include <Scene/GameScene.h>

std::vector<std::shared_ptr<object>> GameScene::_objList;

GameScene::GameScene()
{
}

GameScene::GameScene(int stage)
{
	// 初期化
	_keyOldR = false;
	StageMngIns.UpdateStagecount(stage);
	_update = &GameScene::animUpdate;
	_plMove = &GameScene::moveFall;
	_count	= 0;
	_animCount = 0;

	// アニメーション
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::LEFT, 10));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::RIGHT, 10));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::LEFT, 10));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::RIGHT, 9));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::LEFT, 8));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::RIGHT, 7));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::LEFT, 6));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::RIGHT, 5));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::LEFT, 2));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::RIGHT, 2));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::LEFT, 2));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::RIGHT, 2));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::LEFT, 2));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::RIGHT, 2));
	_LRAnim.emplace_back(std::make_pair(OBJ_STATS::MAX, -1));	 // 終了
}


GameScene::~GameScene()
{
}

Base_unq GameScene::Update(Base_unq scene)
{
	// 最後まで終わったらステージ選択へ
	if ((this->*_update)())
	{
		scene = std::make_unique<StageSelectScene>();
		_objList.clear();
	}

	return std::move(scene);
}

void GameScene::setStage(int count)
{
	_stageCount = count;
}

bool GameScene::clearCheck(void)
{
	auto pl_data = std::find_if(_objList.begin(), _objList.end(), [](std::shared_ptr<object> data) { return data->getType() == OBJ_TYPE::PLAYER; });
	if (pl_data == _objList.end())
	{
		AST();
		return false;
	}

	if (StageMngIns.getStageData({ static_cast<int>((*pl_data)->getPos().x + (*pl_data)->getSize().x / 2), static_cast<int>((*pl_data)->getPos().y + (*pl_data)->getSize().y / 2) }) >= 0 &&
		StageMngIns.getStageData({ static_cast<int>((*pl_data)->getPos().x + (*pl_data)->getSize().x / 2), static_cast<int>((*pl_data)->getPos().y + (*pl_data)->getSize().y / 2) }) <= 3)
	{
		return true;
	}
	return false;
}

bool GameScene::moveFall(void)
{
	auto pl_data = std::find_if(_objList.begin(), _objList.end(), [](std::shared_ptr<object> data) { return data->getType() == OBJ_TYPE::PLAYER; });

	(*pl_data)->setPos({ (*pl_data)->getPos().x, (*pl_data)->getPos().y + 20.0 });
	_count++;

	if (_count >= 40)
	{
		_update = &GameScene::objUpdate;
		ImageMngIns.setEffect(EFFECT::SMOKE, { static_cast<int>((*pl_data)->getPos().x) + CubeSize / 2,static_cast<int>((*pl_data)->getPos().y) + CubeSize / 2 });
		_startTime = steady_clock::now();
	}
	return false;
}

bool GameScene::moveUp(void)
{
	auto pl_data = std::find_if(_objList.begin(), _objList.end(), [](std::shared_ptr<object> data) { return data->getType() == OBJ_TYPE::PLAYER; });

	(*pl_data)->setPos({ (*pl_data)->getPos().x, (*pl_data)->getPos().y - 20.0 });
	(*pl_data)->setState(static_cast<OBJ_STATS>(_count % 2));
	_count++;

	if (_count >= 80)
	{

		return true;
	}
	return false;
}

bool GameScene::moveLR(void)
{
	auto pl_data = std::find_if(_objList.begin(), _objList.end(), [](std::shared_ptr<object> data) { return data->getType() == OBJ_TYPE::PLAYER; });

	(*pl_data)->setState(_LRAnim[_animCount].first);
	_count++;
	if (_count >= _LRAnim[_animCount].second)
	{
		_count = 0;
		_animCount++;
		if (_LRAnim[_animCount].first == OBJ_STATS::MAX)
		{
			_plMove = &GameScene::moveUp;
		}
	}

	return false;
}

bool GameScene::objUpdate(void)
{
	for (auto data : _objList)
	{
		data->Update();
	}

	if (CheckHitKey(KEY_INPUT_R) && (!_keyOldR) || ((SceneMngIns.GetPad() & PAD_INPUT_10) != 0 && (SceneMngIns.GetPadOld() & PAD_INPUT_10) == 0))
	{
		StageMngIns.resetObj();
	}
	_keyOldR = CheckHitKey(KEY_INPUT_R);

	if (clearCheck())
	{
		_update = &GameScene::animUpdate;
		_plMove = &GameScene::moveLR;
		_count = 0;
		_clearTime = steady_clock::now();
		int time = static_cast<int>(duration_cast<milliseconds>(_clearTime - _startTime).count());
	}

	Draw();

	return false;
}

bool GameScene::animUpdate(void)
{
	bool tmpBool = (this->*_plMove)();
	Draw();

	return tmpBool;
}

void GameScene::Draw(void)
{
	for (auto data : _objList)
	{
		data->objDraw();
	}
	StageMngIns.Update();
}
