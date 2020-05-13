#pragma once
#include <memory>
#include "Obj.h"
#include <tuple>		

// ｸﾗｽのﾌﾟﾛﾄﾀｲﾌﾟ宣言
class BaseScene;

enum class ACT_QUE
{
	NON,						
	CHECK_UP,			// 上
	CHECK_SELF,			// 自身
	CHECK_DOWN,			// 下
	CHECK_RIFGT,		// 右
	CHECK_LEFT			// 左
};

enum class ACT_STATE
{
	ACT_QUE,														
	Obj,															
	MAX
};

using unique_Base = std::unique_ptr<BaseScene>;						
using ActQueT = std::pair<ACT_QUE, Obj&>;							

class BaseScene
{
public:
	BaseScene();														
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;				
	
	virtual void RunActQue(std::vector<ActQueT> actList);			
	Vector2 _screenPos;												
protected:
	void FadeInit(std::string fadeType);						
	bool FadeUpdate(void);										
private:
	int _fadeScrID;												
	std::string _fadeType;										
};


