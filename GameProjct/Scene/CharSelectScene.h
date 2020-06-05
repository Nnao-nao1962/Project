#pragma once
#include <map>
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>
#include <Scene/StageSelectScene.h>

#define RAD(ang)	(ang * 3.141592 / 180.0)	// ���W�A���ϊ�
#define PL_SPACE	200
#define PL_NUMBER		2						// �v���C���[�̐�
#define PL_POS_X	((PL_SPACE * 7 + CubeSize) / 2)

class CharSelectScene :
	public BaseScene
{
public:
	CharSelectScene();
	~CharSelectScene();

	Base_unq Update(Base_unq scene);
private:
	int _charSelPos_x;					// �L�����N�^�[�Z���N�g�̃I�t�Z�b�g
	int _cursor;						// �J�[�\���̈ʒu
	int _theta;							// �p�x(�J�[�\���𓮂�������)
	bool _sceneMoveFlag;				// ��ʂ�ς��邩�ǂ���
	Base_unq _tmpScene;					// �ꎞ�I�Ɏ��̃V�[����ێ�

	std::map<int, int>	_keyOld;		// 1�t���O�̃L�[���
	
	Base_unq charMove(Base_unq);
	Base_unq charSelect(Base_unq);

	Base_unq (CharSelectScene::*_charSel)(Base_unq);

	int keyUpdate(int);
	void Draw(void);
	int framPos;			// ��בI��fram�p���W
};
