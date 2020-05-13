#pragma once
#include "InputState.h"
#include <vector>

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void) override;
private:
	void RefKeyData(void);
	void SetKeyConfig(void);
	void (KeyState::*func)(void);		

	char _buf[256];							// 全部のｷｰ情報
	std::vector<int> _keyCon;				// INPUTキー情報
	std::vector<int> _keyConDef;			// INPUTキー情報の保存
	
	INPUT_ID _confID;						// コントロールのINPUT_ID情報
	int modeKeyOld;							// コンフィグモッドキーのオルト
};

