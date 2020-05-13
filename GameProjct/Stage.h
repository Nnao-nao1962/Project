#pragma once
#include "Obj.h"

enum class BLOCK_TYPE
{
	�u���b�N�P,
	�u���b�N�Q,
	�u���b�N�R,
	�u���b�N�S,
	�u���b�NSP,
	MAX
};

enum class FLOOR_STATE
{
	TYPE,					// ���
	VECTOR,					// ���W
	SIZE,					// �傫��
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
