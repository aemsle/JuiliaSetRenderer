#include "Scene_app.h"
#include <SFML/Graphics/Text.hpp>

Scene_app::Scene_app(sf::RenderWindow* in)
{
	window_ = in;

	width_ = 1500;
	height_ = 1500;

	mandelbrot_ = new Mandelbrot();
	slider = new Slider(window_);
	button_ = new Button(window_);
}

Scene_app::~Scene_app()
{
}

void Scene_app::init()
{
	if (!font_.loadFromFile("font/consola.ttf"))
	{
		std::cout << "invalid font";
	}

	fps_text_.setFont(font_); // font is a sf::Font
	real_text_.setFont(font_); // font is a sf::Font
	imag_text_.setFont(font_); // font is a sf::Font

	// set the string to display
	fps_text_.setString("Hello world");
	real_text_.setString("Hello world");
	imag_text_.setString("Hello world");

	// set the character size
	fps_text_.setCharacterSize(24); // in pixels, not points!
	real_text_.setCharacterSize(24); // in pixels, not points!
	imag_text_.setCharacterSize(24); // in pixels, not points!

	// set the color
	fps_text_.setFillColor(sf::Color::White);
	real_text_.setFillColor(sf::Color::White);
	imag_text_.setFillColor(sf::Color::White);

	// set the text style
	fps_text_.setStyle(sf::Text::Bold);
	real_text_.setStyle(sf::Text::Bold);
	imag_text_.setStyle(sf::Text::Bold);

	fps_text_.setPosition(20, 20);
	real_text_.setPosition(20, window_->getSize().y - 68);
	imag_text_.setPosition(20, window_->getSize().y - 44);

	window_->clear(sf::Color(255, 0, 255));
	window_->clear(sf::Color(255, 0, 255));
	window_->clear(sf::Color(255, 0, 255));

	mandelbrot_->calculate(0, 0);

	image_final_.create(width_, height_);
	rect.setSize({ (float)width_,(float)height_ });
	rect.setPosition({ 0, 0 });

	texture.loadFromImage(image_final_);
	rect.setTexture(&texture);

	image_base_.create(width_, height_);
	base_rect.setSize({ (float)width_,(float)height_ });
	base_rect.setPosition({ (float)(window_->getSize().x / 2), 0 });

	base_.loadFromFile("base/base.tga");
	base_rect.setTexture(&base_);

	mandelbrot_->write_tga("output/output.tga");
}

void Scene_app::update(float dt)
{
	fps_text_.setString("FPS: " + std::to_string(1 / dt));
	real_text_.setString("Real:      " + std::to_string(slider->getReal()));
	imag_text_.setString("Imaginary: " + std::to_string(slider->getImag()) + "i");

	int tempx = 1500, tempy = 1500;

	width_ = window_->getSize().x;
	height_ = window_->getSize().y;

	slider->update();
	button_->update();
	mandelbrot_->calculate(slider->getReal(), slider->getImag());

	for (int y = 0; y < tempy; y++)
	{
		for (int x = 0; x < tempx; x++)
		{
			image_final_.setPixel(x, y, { ((mandelbrot_->getPixel(x, y)) >> 16) & 0xFF, ((mandelbrot_->getPixel(x, y)) >> 8) & 0xFF, (mandelbrot_->getPixel(x, y)) & 0xFF });
		}
	}
	base_rect.setPosition(window_->getSize().x / 2, 0);
	texture.loadFromImage(image_final_);
	rect.setTexture(&texture);
}

void Scene_app::render()
{
	window_->clear(sf::Color(255, 0, 255));
	rect.setSize({ (float)width_ / 2, (float)height_ });
	base_rect.setSize({ (float)width_ / 2, (float)height_ });
	window_->draw(rect);
	window_->draw(base_rect);
	window_->draw(fps_text_);
	window_->draw(real_text_);
	window_->draw(imag_text_);
	slider->render();
	button_->render();
	window_->display();
}