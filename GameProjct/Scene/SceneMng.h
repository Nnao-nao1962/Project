#pragma once
#include <common\Vector2.h>
#include <vector>
#include <memory>
#include "BaseScene.h"
#include <tuple>						
#include "LAYER.h"
#include <map>
#include <InputState.h>

enum class DRAW_QUE
{
	IMAGE,									
	X,										
	Y,										
	SIZE_Y,									
	RAD,								
	ZODER,								
	LAYER,								
};

enum TRG
{
	TRG_NOW,			// ����				
	TRG_OLD,			// 1�ڰёO

	TRG_MAX
};

// ����̨�ނŎg�p�E�ݒ肷�鷰
struct Key									
{
	bool left[TRG_MAX];
	bool right[TRG_MAX];
	bool up[TRG_MAX];		
	bool down[TRG_MAX];	
	bool Y[TRG_MAX];	// bt1
	bool B[TRG_MAX];	// bt2
	bool A[TRG_MAX];	// bt3
	bool X[TRG_MAX];	// bt4
};

class Obj;

//ID�AX�AY�A����Y�A��]�AZ���ް�Aڲ԰ID
using DrawQueT = std::tuple<int, double, double,int, double,int, LAYER>;		

// �f�t�@�C��
#define IpSceneMng SceneMng::GetInstance()
#define _mapPos SceneMng::GetInstance().MapPos
#define _mapSize SceneMng::GetInstance().MapSize
#define _Input SceneMng::GetInstance()._input


#define MAP_X 20
#define MAP_Y 20


class SceneMng
{
public:
	// ���I�V���O���g��
	static SceneMng &GetInstance(void)				
	{
		Create();
		return *sInstance;
	}
	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}
	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	void Run(void);

	int map[MAP_Y][MAP_X];

	bool AddDrawQue(DrawQueT dQue);				
	bool AddActQue(ActQueT aQue);				
	
	const Vector2 ScreenSize;					
	const Vector2 GameScreenSize;				
	
	Vector2Dbl MapPos;							
	Vector2Dbl MapSize;							

	int _blendCnt;								
	int _stageCnt;							
	int _liveCnt;				// 			
	int _timeLimitCnt;							
	int _scoreCnt;							
	
	std::shared_ptr<InputState> _input;				
	bool _liveFlag;							// true:�����Ă���Afalse:����ł���
	bool _endFlag;									
	const int frames(void)const;					

private:
	static SceneMng* sInstance;						
	unique_Base _activeScene;						

	void Draw(void);								
	int _frames;									
	int _layerGID;									
	
	std::map<LAYER, int> _screenID;					
	std::vector<DrawQueT> _drawList;				
	std::vector<ActQueT> _actList;					

	~SceneMng();
	SceneMng();													
	void GetKeyState(void);							
	bool SysInit(void);								
};

extern Key _key;


