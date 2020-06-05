#pragma once
#include <vector>
#include <chrono>
#include <algorithm>
#include <Scene/BaseScene.h>
#include <Graphic/ImageMng.h>
#include <StageMng.h>
#include <Objects/object.h>
#include <Objects/player.h>
#include <func/CanGripCube.h>
#include <func/CheckHitObj.h>

using namespace std::chrono;

// プレイヤーのアニメーションの種類
enum class PL_ANIM
{
	FALL,
	UP,
	LR
};

class GameScene :
	public BaseScene
{
public:
	GameScene();
	GameScene(int stage);
	~GameScene();

	Base_unq Update(Base_unq scene);
	void setStage(int count);			// ステージの設定
private:
	friend class StageMng;
	friend struct CanGripCube;
	friend struct CheckHitObj;

	bool clearCheck(void);				// クリアしたのかをチェック

	// プレイヤーのアニメーション
	bool moveFall(void);				// 落ちる
	bool moveUp(void);					// 上がる
	bool moveLR(void);					// 回転
	
	int _count;											// アニメーション用フレームカウンタ
	std::vector<std::pair<OBJ_STATS, int>> _LRAnim;		// 回転アニメーション
	int _animCount;										// 現在のアニメーション

	bool (GameScene::*_plMove)(void);					// アニメーションの関数ポインタ

	bool objUpdate(void);				// プレイ中の処理	
	bool animUpdate(void);				// アニメーション中の処理
	
	bool (GameScene::*_update)(void);	// 上2つの関数ポインタ

	void Draw(void);

	unsigned int _stageCount;			// 現在のステージ数
	bool _keyOldR;						// Rキーの1フレ前の状態

	// ゲーム開始時間と終了時間
	steady_clock::time_point _startTime;
	steady_clock::time_point _clearTime;

	static std::vector<std::shared_ptr<object>> _objList;	// オブジェクトのsharedptrを格納
};

