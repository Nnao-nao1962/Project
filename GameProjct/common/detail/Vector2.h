//#include "stdafx.h"
#include "common/Vector2.h"
#include <cmath>

template<class T>
Vector2Template<T>::Vector2Template()
{
	x = 0;
	y = 0;
}

template<class T>
Vector2Template<T>::Vector2Template(T x, T y)
{
	this->x = x;
	this->y = y;
}

template<class T>
Vector2Template<T>::~Vector2Template()
{
}

// 代入演算子
template<class T>
Vector2Template<T> & Vector2Template<T>::operator =(const Vector2Template<T> & vec)
{
	x = vec.x;
	y = vec.y;

	return *this;
}

// 添え字演算子
template<class T>
int & Vector2Template<T>::operator[](T i)
{
	if (i == 0)
	{
		return x;
	}
	else if(i==1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

// 比較演算子
template<class T>
bool Vector2Template<T>::operator==(const Vector2Template<T> & vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}
template<class T>
bool Vector2Template<T>::operator!=(const Vector2Template<T> & vec) const
{
	return !((this->x == vec.x) && (this->y == vec.y));
}
template<class T>
bool Vector2Template<T>::operator>(const Vector2Template<T> & vec) const
{
	return ((this->x > vec.x) && (this->y > vec.y));
}
template<class T>
bool Vector2Template<T>::operator>=(const Vector2Template<T> & vec) const
{
	return ((this->x >= vec.x) && (this->y >= vec.y));
}
template<class T>
bool Vector2Template<T>::operator<=(const Vector2Template<T> & vec) const
{
	return ((this->x <= vec.x) && (this->y <= vec.y));
}



//単項演算子
template<class T>
Vector2Template<T> & Vector2Template<T>::operator+=(const Vector2Template<T> & vec)
{
	x += vec.x;
	y += vec.y;

	return *this;


}
template<class T>
Vector2Template<T> & Vector2Template<T>::operator-=(const Vector2Template<T> & vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator*=(T k)
{
	x *= k;
	y *= k;

	return *this;
}

template<class T>
Vector2Template<T> & Vector2Template<T>::operator/=(T k)
{
	x /= k;
	y /= k;

	return *this;
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator+() const		//()const   この関数の中で全ての数字const
{

	return *this;						// *this この自身のままで（数字変わらない）
}

template<class T>
Vector2Template<T> Vector2Template<T>::operator-() const
{
	return Vector2Template<T>(-this->x,-this->y);
}

// ベクトルの演算
// Vector2　+　int 
template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, T v)
{
	Vector2Template<T> vec;
	vec.x = u.x + v;
	vec.y = u.y + v;

	return vec;
}

// Vector2　-　int 
template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, T v)
{
	Vector2Template<T> vec;
	vec.x = u.x - v;
	vec.y = u.y - v;

	return vec;
}
// Vector2　*　int
template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, T v)
{
	Vector2Template<T> vec;
	vec.x = u.x * v;
	vec.y = u.y * v;

	return vec;
}


// Vector2　/　int
template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, T v)
{
	Vector2Template<T> vec;
	vec.x = u.x / v;
	vec.y = u.y / v;

	return vec;
}
// Vector2　%　int
template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, T v)
{
	Vector2Template<T> vec;
	vec.x = u.x % v;
	vec.y = u.y % v;

	return vec;
}

// int * Vector2　
template<class T>
Vector2Template<T> operator*(T v, const Vector2Template<T> & u)
{
	Vector2Template<T> vec;
	vec.x = u.x * v;
	vec.y = u.y * v;

	return vec;
}

// Vector2　+　Vector2
template<class T>
Vector2Template<T> operator+(const Vector2Template<T> & u, const Vector2Template<T> v)
{
	Vector2Template<T> vec;
	vec.x = u.x + v.x;
	vec.y = u.y + v.y;

	return vec;
}
// Vector2　-　Vector2
template<class T>
Vector2Template<T> operator-(const Vector2Template<T> & u, const Vector2Template<T> v)
{
	Vector2Template<T> vec;
	vec.x = u.x - v.x;
	vec.y = u.y - v.y;

	return vec;
}
// Vector2　*　Vector2
template<class T>
Vector2Template<T> operator*(const Vector2Template<T> & u, const Vector2Template<T> v)
{
	Vector2Template<T> vec;
	vec.x = u.x * v.x;
	vec.y = u.y * v.y;

	return vec;
}
// Vector2　/　Vector2
template<class T>
Vector2Template<T> operator/(const Vector2Template<T> & u, const Vector2Template<T> v)
{
	Vector2Template<T> vec;
	vec.x = u.x / v.x;
	vec.y = u.y / v.y;

	return vec;
}
// Vector2　%　Vector2
template<class T>
Vector2Template<T> operator%(const Vector2Template<T> & u, const Vector2Template<T> v)
{
	Vector2Template<T> vec;
	vec.x = u.x % v.x;
	vec.y = u.y % v.y;

	return vec;
}


