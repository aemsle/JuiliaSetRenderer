#include "Utils.h"

double Utils::UtilRound(double d)
{
	return (double)floor(d + 0.5);
}

double Utils::map(double value, double input_one, double input_two, double output_one, double output_two)
{
	/*
	double slope = (double)1.f * ((double)output_two - (double)output_one) / ((double)input_two - (double)input_one);
	double output = (double)output_one + (double)Utils::UtilRound((double)slope * (value - input_one));
	return output;
	*/
	return (output_one + (output_two - output_one) * ((value - input_one) / (input_two - input_one)));
}
