#pragma once
#include "BaseScene.h"


class SelectScene :
	public BaseScene
{
public:
	SelectScene();
	~SelectScene();
	unique_Base Update(unique_Base own) override;			

private:
	std::vector<sharedObj> _objList;				
};

