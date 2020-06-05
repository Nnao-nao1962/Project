#pragma once
#include <map>
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>
#include <Scene/StageSelectScene.h>

#define RAD(ang)	(ang * 3.141592 / 180.0)	// ラジアン変換
#define PL_SPACE	200
#define PL_NUMBER		2						// プレイヤーの数
#define PL_POS_X	((PL_SPACE * 7 + CubeSize) / 2)

class CharSelectScene :
	public BaseScene
{
public:
	CharSelectScene();
	~CharSelectScene();

	Base_unq Update(Base_unq scene);
private:
	int _charSelPos_x;					// キャラクターセレクトのオフセット
	int _cursor;						// カーソルの位置
	int _theta;							// 角度(カーソルを動かすため)
	bool _sceneMoveFlag;				// 場面を変えるかどうか
	Base_unq _tmpScene;					// 一時的に次のシーンを保持

	std::map<int, int>	_keyOld;		// 1フレ前のキー状態
	
	Base_unq charMove(Base_unq);
	Base_unq charSelect(Base_unq);

	Base_unq (CharSelectScene::*_charSel)(Base_unq);

	int keyUpdate(int);
	void Draw(void);
	int framPos;			// ｷｬﾗ選択fram用座標
};

