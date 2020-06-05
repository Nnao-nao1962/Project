#pragma once
#include <map>
#include <Scene/BaseScene.h>
#include <Scene/SceneMng.h>

#define STAGE_SPACE		60			// ステージ間の間隔
#define STAGE_SIZE_X	200			// ステージのX方向の大きさ
#define STAGE_SIZE_Y	96			// ステージのY方向の大きさ
#define STAGE_OFFSET	(SceneMngIns.ScreenCenter.x - (STAGE_SIZE_X + STAGE_SPACE) * 3 / 2)		// 下のステージ達のオフセット
#define STAGE_NUMBER 3


class StageSelectScene :
	public BaseScene
{
public:
	StageSelectScene();
	~StageSelectScene();

	Base_unq Update(Base_unq scene);	// 更新
private:
	int _stagePos_x;					// ステージの座標
	int _cursor;						// カーソル
	bool _sceneMoveFlag;				// 場面を変えるかどうか
	Base_unq _tmpScene;					// 一時的に次のシーンを保持
	int _stageViewScreen;				// ステージを拡大したものを描画するスクリーン

	std::map<int, int> _keyOld;			// 1フレ前のキー状態

	Base_unq stageMove(Base_unq scene);		// ステージが動いている間の処理
	Base_unq stageSelect(Base_unq scene);		// ステージを選ぶ時の処理

	Base_unq (StageSelectScene::*_stageSel)(Base_unq);	// 上2つの関数ポインタ

	int keyUpdate(int key);				// キー状態の管理
	void Draw();						// 描画

	int stageSelPos;	// ステージ選択用frame
};

