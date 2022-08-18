#include "CustomComplex.h"

CustomComplex CustomComplex::c_add(CustomComplex c1, CustomComplex c2) restrict(cpu, amp)
{
	CustomComplex tmp;
	float a = c1.real_;
	float b = c1.imag_;
	float c = c2.real_;
	float d = c2.imag_;
	tmp.real_ = a + c;
	tmp.imag_ = b + d;
	return tmp;
}

float CustomComplex::c_abs(CustomComplex c) restrict(cpu, amp)
{
	return concurrency::fast_math::sqrt(c.real_ * c.real_ + c.imag_ * c.imag_);
}

CustomComplex CustomComplex::c_mul(CustomComplex c1, CustomComplex c2) restrict(cpu, amp)
{
	CustomComplex tmp;
	float a = c1.real_;
	float b = c1.imag_;
	float c = c2.real_;
	float d = c2.imag_;
	tmp.real_ = a * c - b * d;
	tmp.imag_ = b * c + a * d;
	return tmp;
}
