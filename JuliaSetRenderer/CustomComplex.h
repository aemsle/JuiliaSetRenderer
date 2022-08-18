#pragma once

#define _SILENCE_AMP_DEPRECATION_WARNINGS
#include <amp.h>
#include <amp_math.h>

class CustomComplex
{
public:
	float real_;
	float imag_;
	static CustomComplex c_add(CustomComplex c1, CustomComplex c2) restrict(cpu, amp);
	static float c_abs(CustomComplex c) restrict(cpu, amp);
	static CustomComplex c_mul(CustomComplex c1, CustomComplex c2) restrict(cpu, amp);
private:
};
