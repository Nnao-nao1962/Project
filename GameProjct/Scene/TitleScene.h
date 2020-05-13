#pragma once
#include "BaseScene.h"
#include <functional>
#include <vector>
#include "Obj.h"

// ƒtƒ@ƒ“ƒN
using funcAct = std::function<bool(ActQueT&, void*)>;			

struct FuncCheckLeft;

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own) override;		

	friend FuncCheckLeft;
	
	void funcInit(void);										

	void RunActQue(std::vector<ActQueT> actList) override;		
	std::vector<sharedObj> _objList;							
	std::map<ACT_QUE, funcAct> funcQue;							

	void MapInit(void);										
};

