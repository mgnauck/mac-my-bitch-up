#ifndef H_CONSTANTS__
#define H_CONSTANTS__

#include <cmath>
#include <cstdlib>

extern float const PI;
extern float const PI_HALF;
extern float const PI_2;
extern float const EPSILON;
extern float const DEG2RAD;
extern float const RAD2DEG;

template<typename T>			// should not be here
T rnd(T _min, T _max) {
	return _min + (_max - _min) * (rand() / (T)RAND_MAX);
}

template<typename T>
void swap(T* a, T* b) {
	T t = *a;
	*a = *b;
	*b = t;
}

#endif