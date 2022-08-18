#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

class Slider
{
public:
	Slider(sf::RenderWindow*);
	~Slider();
	float getReal();
	float getImag();
	void update();
	void render();
private:
	sf::CircleShape handle_;
	sf::RenderWindow* window_;
	sf::Mouse mouse;
	double real;
	double imag;
};

