#include "KeyState.h"
#include <Dxlib.h>
#include "_debug\_DeBugConOut.h"
#include "InputState.h"

KeyState::KeyState()
{
	
	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));

	_keyConDef.emplace_back(KEY_INPUT_LEFT);
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_Z);
	_keyConDef.emplace_back(KEY_INPUT_X);
	_keyConDef.emplace_back(KEY_INPUT_A);
	_keyConDef.emplace_back(KEY_INPUT_S);

	FILE* file;
	fopen_s(&file, "data/key.dat", "rb");
	if (file==nullptr)
	{
		_keyCon = _keyConDef;
	}
	else
	{
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));
		fread(_keyCon.data(), sizeof(&_keyCon[0])*_keyCon.size(), 1, file);
		
		fclose(file);
	}
	
	modeKeyOld = 1;
	func = &KeyState::RefKeyData;
}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();
	modeKeyOld = _buf[KEY_INPUT_F1];
	GetHitKeyStateAll(_buf);
	
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
	for(auto id: INPUT_ID())
	{
		state(id, _buf[_keyCon[static_cast<size_t>(id)]]);
	}
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		_confID = INPUT_ID::LEFT;
		func = &KeyState::SetKeyConfig;
		TRACE("キーコンフィグ開始\n");
		TRACE("%d/%d番目のキー設定\n", static_cast<int>(_confID)+1,end(INPUT_ID()));
	}
}

void KeyState::SetKeyConfig(void)
{
	
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		func = &KeyState::RefKeyData;
		TRACE("ｷｰｺﾝﾌｨｸﾞ終了\n");
	}
	for (auto key : INPUT_ID())
	{
		state(key, 0);
	}

	
	auto checkKey=[&](int id) {
		for (auto ckID = INPUT_ID::LEFT; ckID < _confID; ++ckID)
		{
			if (_keyCon[static_cast<int>(ckID)] == id)
			{
				return false;
			}
		}
		return true;
	};

	
	for (int id = 0; id < sizeof(_buf); id++)
	{	
		if (!checkKey(id))
		{
			continue;
		}

		if (_buf[id] && (!_buf[KEY_INPUT_F1]))
		{
			_keyCon[static_cast<int>(_confID)] = id;
			++_confID;
			TRACE("%dを設定\n", id);
			if (_confID == end(_confID))
			{
				
				FILE* file;
				fopen_s(&file, "data/key.dat", "wb");
				if (file != nullptr)
				{
					fwrite(_keyCon.data(), sizeof(_keyCon[0])*_keyCon.size(), 1, file);
					fclose(file);
				}
				TRACE("ｷｰｺﾝﾌｨｸﾞ終了\n");
				func = &KeyState::RefKeyData;
				break;
			}
			TRACE("%d/%d番目のｷｰ設定\n", static_cast<int>(_confID) + 1, end(INPUT_ID()));
		}
	}
}


