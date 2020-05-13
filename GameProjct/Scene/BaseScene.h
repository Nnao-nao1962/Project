#pragma once
#include <memory>
#include "Obj.h"
#include <tuple>		

// ∏◊ΩÇÃÃﬂ€ƒ¿≤ÃﬂêÈåæ
class BaseScene;

enum class ACT_QUE
{
	NON,						
	CHECK_UP,			// è„
	CHECK_SELF,			// é©êg
	CHECK_DOWN,			// â∫
	CHECK_RIFGT,		// âE
	CHECK_LEFT			// ç∂
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


