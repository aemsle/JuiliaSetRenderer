#pragma once
#include <SFML/Graphics.hpp>
#include "Mandelbrot.h"
#include "Utils.h"
#include "Slider.h"
#include "Button.h"

class Scene_app
{
public:
	Scene_app(sf::RenderWindow*);
	~Scene_app();
	void init();

	void update(float);
	void render();
private:
	sf::RenderWindow* window_;
	Mandelbrot* mandelbrot_;

	int width_;
	int height_;

	std::vector<std::vector<sf::Color> > image_color_;
	sf::RenderWindow* window;
	sf::Texture texture;
	sf::Image image_final_;
	sf::RectangleShape rect;

	sf::Texture base_;
	sf::Image image_base_;
	sf::RectangleShape base_rect;
	
	sf::Font font_;
	sf::Text fps_text_;
	sf::Text real_text_;
	sf::Text imag_text_;

	Slider* slider;
	Button* button_;
};

