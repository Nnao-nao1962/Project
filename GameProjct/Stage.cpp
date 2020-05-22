#include <Dxlib.h>
#include "Stage.h"
#include "ImageMng.h"
#include "_DeBugConOut.h"
#include "SceneMng.h"
#include "_DeBugConOut.h"
#include <math.h>


Stage::Stage()
{
	Init();
}

Stage::Stage(StageState & state)
{
	_type = std::get<static_cast<int>(FLOOR_STATE::TYPE)>(state);
	_pos = std::move(std::get<static_cast<int>(FLOOR_STATE::VECTOR)>(state));
	_size = std::move(std::get<static_cast<int>(FLOOR_STATE::SIZE)>(state));
	Init();
}

// 更新
void Stage::Update(sharedObj plObj)
{
}

Stage::~Stage()
{
}

// 初期化
void Stage::Init(void)
{
	_unitID = UNIT_ID::FLOOR;
	AnimVector data;

	switch (_type)
	{
	case BLOCK_TYPE::ブロック１:
		data.emplace_back(IMAGE_ID("ブロック")[static_cast<int>(0)], 30);
		SetAnim(STATE::STAY, data);
		break;
	case BLOCK_TYPE::ブロック２:
		data.emplace_back(IMAGE_ID("ブロック")[static_cast<int>(1)], 30);
		SetAnim(STATE::STAY, data);
		break;
	case BLOCK_TYPE::ブロック３:
		data.emplace_back(IMAGE_ID("ブロック")[static_cast<int>(2)], 30);
		SetAnim(STATE::STAY, data);
		break;
	case BLOCK_TYPE::ブロック４:
		data.emplace_back(IMAGE_ID("ブロック")[static_cast<int>(4)], 30);
		SetAnim(STATE::STAY, data);
		break;		
	case BLOCK_TYPE::ブロックSP:
		data.emplace_back(IMAGE_ID("ブロック")[static_cast<int>(5)], 30);
		SetAnim(STATE::STAY, data);
		break;
	default:
		break;
	}

	state(STATE::STAY);

}

