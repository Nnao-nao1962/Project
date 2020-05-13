#include <Dxlib.h>
#include "_debug/_DeBugConOut.h"
#include "InputState.h"


InputState::InputState()
{
	// try_emplace:
	//		引数と等価のキーを持つ要素が存在しない場合、コンテナに新しい要素を挿入する。
	//		要素は引数からコンテナ内に直接構築されるため、構築されたオブジェクトはコピーもムーブもされない。
	
	// enum classで範囲FOR文のやり方：INPUT_ID.cppとINPUT_ID.h
	for (auto id : INPUT_ID())
	{
		_state.try_emplace(id, KeyPair{ 0,1 });
	}
}

InputState::~InputState()
{
}

const KeyMap & InputState::state(void) const
{
	return _state;
}

const KeyPair & InputState::state(INPUT_ID id) const
{
	static KeyPair defData = { 0,0 };
	try
	{
		return _state.at(id);
	}
	catch (...)
	{
		AST();
		
		return defData;
	}
}

bool InputState::state(INPUT_ID id,int data)
{
	if (_state.find(id) != _state.end())
	{
		_state[id].first = data;
		return true;
	}
	return false;
}

void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			AST();
			_state.emplace(id, KeyPair{ 0,1 });
		}
	}
}

