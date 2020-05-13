#pragma once
#include "Obj.h"

enum class BLOCK_TYPE
{
	ブロック１,
	ブロック２,
	ブロック３,
	ブロック４,
	ブロックSP,
	MAX
};

enum class FLOOR_STATE
{
	TYPE,					// 種類
	VECTOR,					// 座標
	SIZE,					// 大きさ
	MAX
};

using StageState = std::tuple<BLOCK_TYPE, Vector2Dbl, Vector2>;

class Stage;
class Stage :
	public Obj
{
public:
	Stage();
	Stage(StageState& state);

	void Update(sharedObj plObj) override;							
	~Stage();

private:
	void Init(void);											
	BLOCK_TYPE _type;											
};
