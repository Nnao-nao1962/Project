#pragma once
#include <Objects/object.h>
#include <Graphic/ImageMng.h>
#include <StageMng.h>
#include <func/CanGripCube.h>
#include <Objects/CHECK_DIR.h>
#include <func/CheckHitObj.h>

#define PL_SPEED	4		// ƒvƒŒƒCƒ„[‚Ì‚Í‚â‚³


class player :
	public object
{
public:
	player();
	player(Vector2Template<double> pos, double rad, Vector2Template<int> size, int color);
	~player();
	void Update(void)override;

private:
	
	void control(void);
	bool CheckHitCube(CHECK_DIR);	// ˆÚ“®
};

