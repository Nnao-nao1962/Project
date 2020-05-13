#include <Dxlib.h>
#include "_debug/_DeBugConOut.h"
#include "InputState.h"


InputState::InputState()
{
	// try_emplace:
	//		�����Ɠ����̃L�[�����v�f�����݂��Ȃ��ꍇ�A�R���e�i�ɐV�����v�f��}������B
	//		�v�f�͈�������R���e�i���ɒ��ڍ\�z����邽�߁A�\�z���ꂽ�I�u�W�F�N�g�̓R�s�[�����[�u������Ȃ��B
	
	// enum class�Ŕ͈�FOR���̂����FINPUT_ID.cpp��INPUT_ID.h
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

