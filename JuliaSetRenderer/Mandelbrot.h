#pragma once
#include <complex>
#include <vector>
#include <iostream>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Utils.h"

#define _SILENCE_AMP_DEPRECATION_WARNINGS
#include <amp.h>
#include <amp_math.h>
#include "CustomComplex.h"
#include "Timer.h"

//CREDIT:
//https://www.youtube.com/watch?v=6z7GQewK-Ks -  for base mandelbrot calculation
//https://www.youtube.com/watch?v=vfteiiTfE0c -  for julia sets explination
//https://en.wikipedia.org/wiki/Julia_set -  julia set values
class Mandelbrot
{
public:
	Mandelbrot();
	~Mandelbrot();
	void calculate(double, double);
	sf::Uint32 getPixel(int&, int&);
	void write_tga(const char*);
private:
	uint32_t* image_;
};