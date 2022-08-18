#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

class Button
{
public:
	Button(sf::RenderWindow*);
	~Button();
	void update();
	virtual void onClick();
	void render();
private:
	sf::RectangleShape button_;
	sf::RenderWindow* window_;
	sf::Mouse mouse;
};