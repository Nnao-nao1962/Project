#pragma once

// テンプレート
template<class T>class Vector2Template
{
public:
	Vector2Template();
	Vector2Template(T x, T y);
	~Vector2Template();
	T x;
	T y;

	// 代入演算子
	Vector2Template<T>& operator = (const Vector2Template&vec);

	// 添え字演算子
	int& operator [] (T i);

	// 比較演算子
	bool operator == (const Vector2Template&vec)const;
	bool operator != (const Vector2Template&vec)const;
	bool operator > (const Vector2Template&vec)const;
	bool operator >= (const Vector2Template&vec)const;
	bool operator <= (const Vector2Template&vec)const;

	// 単項演算子
	Vector2Template& operator +=(const Vector2Template<T>&vec);
	Vector2Template& operator -=(const Vector2Template<T>&vec);
	Vector2Template& operator *=(T k);
	Vector2Template& operator /=(T k);

	Vector2Template operator+()const;
	Vector2Template operator-()const;
};

// ベクトルの演算
// Vector2　+　int 
template<class T>
Vector2Template<T> operator+(const Vector2Template<T>&u, T v);
// Vector2　-　int 
template<class T>
Vector2Template<T> operator-(const Vector2Template<T>&u, T v);
// Vector2　*　int
template<class T>
Vector2Template<T> operator*(const Vector2Template<T>&u, T v);
// Vector2　/　int
template<class T>
Vector2Template<T> operator/(const Vector2Template<T>&u, T v);
// Vector2　%　int
template<class T>
Vector2Template<T> operator%(const Vector2Template<T>&u, T v);

// int * Vector2　
template<class T>
Vector2Template<T> operator*(T v, const Vector2Template<T>&u);

// Vector2　+　Vector2
template<class T>
Vector2Template<T> operator+(const Vector2Template<T>&u, const Vector2Template<T> v);
// Vector2　-　Vector2
template<class T>
Vector2Template<T> operator-(const Vector2Template<T>&u, const Vector2Template<T> v);
// Vector2　*　Vector2
template<class T>
Vector2Template<T> operator*(const Vector2Template<T>&u, const Vector2Template<T> v);
// Vector2　/　Vector2
template<class T>
Vector2Template<T> operator/(const Vector2Template<T>&u, const Vector2Template<T> v);
// Vector2　%　Vector2
template<class T>
Vector2Template<T> operator%(const Vector2Template<T>&u, const Vector2Template<T> v);

using Vector2 = Vector2Template<int>;
using Vector2Dbl = Vector2Template<double>;
using Vector2Flt = Vector2Template<float>;

#include "detail/Vector2.h"