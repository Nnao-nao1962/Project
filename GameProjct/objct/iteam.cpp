#include "iteam.h"
#include "ImageMng.h"
#include "_DeBugConOut.h"
#include "Obj.h"
#include "SceneMng.h"
#include <Dxlib.h>
iteam::iteam()
{
	Init();
}

// Iteam�I�[�o�[���[�h
iteam::iteam(IteamState & state)
{
	_type = std::get<static_cast<int>(ITEAM_STATE::TYPE)>(state);
	_pos = std::move(std::get<static_cast<int>(ITEAM_STATE::VECTOR)>(state));
	_size = std::move(std::get<static_cast<int>(ITEAM_STATE::SIZE)>(state));
	_moveCtl.SetMoveState(std::get<static_cast<int>(ITEAM_STATE::AIM)>(state), true);

	Init();

}

// �X�V
void iteam::Update(sharedObj plObj)
{

	_moveCtl.Update(plObj);
	switch (_unitID)
	{
	case UNIT_ID::COIN:
		IpSceneMng.AddActQue({ ACT_QUE::CHECK_SELF , *this });
		if (_coinFlag)
		{
			_pos.y -= 5;
			if (_pos.y<=_oldPos.y-40)
			{
				SetAlive(false);
				IpSceneMng._scoreCnt += 100;
				_coinFlag = false;
			}
		}
		else
		{
			_oldPos = _pos;
		}
		break;
	case UNIT_ID::END:
		IpSceneMng.AddActQue({ ACT_QUE::CHECK_SELF , *this });
		break;
	default:
		break;
	}


}

iteam::~iteam()
{
}

// ������
void iteam::Init(void)
{
	_coinCnt = 0;
	AnimVector data;

	switch (_type)
	{
	case ITEAM_TYPE::�R�C��:
		_unitID = UNIT_ID::COIN;

		data.emplace_back(IMAGE_ID("�R�C��")[0], 10);
		
	default:
		break;
	}

	state(STATE::STAY);
}
