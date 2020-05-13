#pragma once
#include <functional>
#include <vector>
#include "BaseScene.h"
#include "Obj.h"

// �t�@���N
using funcAct = std::function<bool(ActQueT&, void*)>;				

struct FuncCheckOn;

class GameScene :
	public BaseScene
{
public:
	GameScene();													
	~GameScene();
	unique_Base Update(unique_Base own) override;		

private:
	friend FuncCheckOn;

	void funcInit(void);										
	void RunActQue(std::vector<ActQueT> actList) override;		
	std::vector<sharedObj> _objList;							
	std::map<ACT_QUE, funcAct> funcQue;							

	// �}�b�v������
	void MapInit(void);					


	int _shakeCount;
};
