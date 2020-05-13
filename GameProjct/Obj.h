#pragma once
#include <string>
#include <vector>
#include <Vector2.h>
#include <map>
#include <memory>


// à⁄ìÆ
enum class MOVE_TYPE
{
	LR,						
	DOWN,					
	UP,						
	DOWNUP					
};
// ’∆Øƒ
enum class UNIT_ID
{
	NON,						// Ç»Çµ
	PLAYER,						
	ENEMY,						
	COIN,						
	END,						
	BRICK,						
	FLOOR						
};
// èÛë‘ä«óù
enum class STATE
{
	STAY,					
	RIGHT,					
	LEFT,									
	MOVE,					
	DETH,					
	MAX
};
enum class ACT
{
	STAY,			
	RIGHT,					
	LEFT,						
	MAX
};

class Obj;
class Stage;

using AnimVector = std::vector<std::pair<int, unsigned int>>;

using sharedObj = std::shared_ptr<Obj>;								
class Obj
{
public:
	Obj();
	virtual void Update(sharedObj plObj) = 0;						
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const STATE state);									

	UNIT_ID _unitID;												

	virtual bool SetAlive(bool alive);								
	virtual bool Fall(bool fall);									
	virtual bool LeftCheck(bool leftFlag);							
	virtual bool RightCheck(bool rightFlag);						

	virtual Vector2Dbl movePos(Vector2Dbl move);			
	virtual bool BridgeFlag(bool BridgeFlag);				

	bool SetAnim(const STATE state, AnimVector& data);			
	bool isAlive(void) { return _alive; }						
	bool isDead(void) { return _dead; }							
	bool isAnimEnd(void);										

	// πﬁØƒä÷êî
	const Vector2Dbl Pos(void)const;						
	const Vector2 Size(void) const;							
	const bool EndFlag(void) const;							
	const STATE state(void) const;							
	const bool BridgeFlag(void) const;						

private:
	friend Stage;

	Vector2Dbl _pos;							
	bool _leftFlag;								
	bool _rightFlag;							
	bool _endFlag;													
	bool _fallFlag;																										
	bool _bridgeFlag;												
	bool _treadFlag;													

	std::map <STATE, AnimVector> _animMap;								
	STATE _state;														
	unsigned int _animFrame;											
	unsigned int _animCount;											

protected:
	bool DestroyPrpc(void);								
	bool _alive;										
	bool _dead;											
	double _rad;										
	int _zorder;										
	Vector2 _size;										
};
