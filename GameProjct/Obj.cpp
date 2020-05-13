#include <Dxlib.h>
#include <SceneMng.h>
#include <ImageMng.h>
#include <Obj.h>
#include <Vector2.h>
#include <GameScene.h>

Obj::Obj()
{
	_alive = true;
	_dead = false;
	_animCount = 0;
	_animFrame = 0;
	_rad = 0;
	_zorder = 0;
}

void Obj::Draw(void)
{
	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}
	if (_animFrame < 0 || _animFrame >= _animMap[_state].size())
	{
		return;
	}

	if (_animMap[_state][_animFrame].first >= 0)
	{
		if (_animCount >= _animMap[_state][_animFrame].second)
		{
			_animFrame++;
		}
		if (_animFrame >= _animMap[_state].size())
		{
			_animFrame = 0;
			_animCount = 0;
		}
		else
		{
			_animCount++;
		}
	}

	IpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,-_mapPos.x + _pos.x, _pos.y ,_size.y,_rad,_zorder,LAYER::CHAR });

}

void Obj::Draw(int id)
{
	IpSceneMng.AddDrawQue({ id, _pos.x, _pos.y ,_size.y,_rad,_zorder,LAYER::CHAR });
}

Obj::~Obj()
{
}

bool Obj::state(const STATE state)
{
	if (_animMap.find(state) == _animMap.end())
	{
		return false;
	}
	if (_state != state)
	{
		_animCount = 0;
		_animFrame = 0;
	}
	_state = state;
	return true;
}

const STATE Obj::state(void) const
{
	return _state;
}

const bool Obj::BridgeFlag(void) const
{
	return _bridgeFlag;
}

const Vector2Dbl Obj::Pos(void) const
{
	return _pos;
}

const Vector2 Obj::Size(void) const
{
	return _size;
}


const bool Obj::EndFlag(void) const
{
	return _endFlag;
}


bool Obj::Fall(bool fall)
{
	_fallFlag = fall;

	return true;
}

bool Obj::LeftCheck(bool leftFlag)
{
	_leftFlag = leftFlag;
	return true;
}

bool Obj::RightCheck(bool rightFlag)
{
	_rightFlag = rightFlag;
	return true;
}


Vector2Dbl Obj::movePos(Vector2Dbl move)
{
	_pos.x += move.x;
	_pos.y += move.y;
	return _pos;
}


bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		state(STATE::DETH);
	}

	return true;
}

bool Obj::SetAnim(const STATE state, AnimVector& data)
{
	return (_animMap.try_emplace(state, std::move(data))).second;
}

// ±∆“∞ºÆ›Ç™èIÇÌÇ¡ÇΩÇ©Ç«Ç§Ç©
bool Obj::isAnimEnd(void)
{
	if (_animMap.find(_state) == _animMap.end())
	{
		return true;
	}
	if (_animFrame < 0 || _animFrame >= _animMap[_state].size())
	{
		return true;
	}
	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}


bool Obj::BridgeFlag(bool BridgeFlag)
{
	_bridgeFlag = BridgeFlag;
	return _bridgeFlag;
}


bool Obj::DestroyPrpc(void)
{
	if (_alive)
	{
		return false;
	}
	if (isAnimEnd())
	{
		_dead = true;
	}
	return true;
}




