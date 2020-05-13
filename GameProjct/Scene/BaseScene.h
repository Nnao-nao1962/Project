#pragma once
#include <memory>
#include "Obj.h"
#include <tuple>		

// �׽���������ߐ錾
class BaseScene;

enum class ACT_QUE
{
	NON,						
	CHECK_UP,			// ��
	CHECK_SELF,			// ���g
	CHECK_DOWN,			// ��
	CHECK_RIFGT,		// �E
	CHECK_LEFT			// ��
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


