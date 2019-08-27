#include "pch.h"
#include <iostream>

#ifndef INTEGRATE_RANGE_H
#define INTEGRATE_RANGE_H

using namespace std;

template <class T>
class IntegrateRange
{
public:
	T a, b;

	IntegrateRange(T a, T b);
	IntegrateRange<T>* generate_range_by_division(); // return two ranges
};

template <class T>
IntegrateRange<T>::IntegrateRange(T a, T b)
{
	this->a = a;
	this->b = b;
}

template<class T>
IntegrateRange<T>* IntegrateRange<T>::generate_range_by_division()
{
	IntegrateRange<T> result[2];

	result[0] = IntegrateRange<T>(this->a, (this->a + this->b) / 2);
	result[1] = IntegrateRange<T>((this->a + this->b) / 2, this->a);

	return result;
}

#endif
