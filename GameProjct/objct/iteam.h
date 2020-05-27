#pragma once
#include "Obj.h"
#include "IteamMove.h"

enum class ITEAM_TYPE
{
	コイン,
	ゴール,
	MAX
};

enum class ITEAM_STATE
{
	TYPE,					// 種類
	VECTOR,					// 座標
	SIZE,					// 大きさ
	AIM,					// 移動種類
	MAX
};

// 種類、座標、サイズ、移動種類
using IteamState = std::tuple<ITEAM_TYPE, Vector2Dbl, Vector2, MoveState&>;

class iteam;
class iteam :
	public Obj
{
public:
	iteam();
	iteam(IteamState& state);										// Iteamオーバーロード
	void Update(sharedObj plObj) override;							// 更新
	~iteam();

private:
	IteamMove _moveCtl{ _pos,_rad,_size };							// ムーブコントロール｛座標、角度、サイズ｝
	void Init(void);												// 初期化
	ITEAM_TYPE _type;												// 敵種類
	Vector2Dbl _oldPos;
	int _coinCnt;
};

