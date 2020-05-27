#pragma once
#include "Obj.h"
#include "IteamMove.h"

enum class ITEAM_TYPE
{
	�R�C��,
	�S�[��,
	MAX
};

enum class ITEAM_STATE
{
	TYPE,					// ���
	VECTOR,					// ���W
	SIZE,					// �傫��
	AIM,					// �ړ����
	MAX
};

// ��ށA���W�A�T�C�Y�A�ړ����
using IteamState = std::tuple<ITEAM_TYPE, Vector2Dbl, Vector2, MoveState&>;

class iteam;
class iteam :
	public Obj
{
public:
	iteam();
	iteam(IteamState& state);										// Iteam�I�[�o�[���[�h
	void Update(sharedObj plObj) override;							// �X�V
	~iteam();

private:
	IteamMove _moveCtl{ _pos,_rad,_size };							// ���[�u�R���g���[���o���W�A�p�x�A�T�C�Y�p
	void Init(void);												// ������
	ITEAM_TYPE _type;												// �G���
	Vector2Dbl _oldPos;
	int _coinCnt;
};

