#include "Slider.h"

Slider::Slider(sf::RenderWindow* window)
{
	window_ = window;
	handle_.setFillColor(sf::Color::Green);
	handle_.setRadius(10);
	handle_.setOrigin(10, 10);
}

Slider::~Slider()
{
}

float Slider::getReal()
{
	return real;
}

float Slider::getImag()
{
	return imag;
}

void Slider::update()
{
	float mouse_x = mouse.getPosition().x - window_->getPosition().x;
	float mouse_y = mouse.getPosition().y - window_->getPosition().y;

	if (mouse_x > handle_.getPosition().x - 50 && mouse_x < handle_.getPosition().x + 50 &&
		mouse_y > handle_.getPosition().y - 50 && mouse_y < handle_.getPosition().y + 50)
	{
		handle_.setFillColor(sf::Color::Red);

		if (mouse.isButtonPressed(mouse.Left))
		{
			handle_.setPosition(mouse_x, mouse_y);
		}
	}
	else
	{
		handle_.setFillColor(sf::Color::Green);
	}

	if (handle_.getPosition().x < window_->getSize().x / 2)
	{
		handle_.setPosition(window_->getSize().x / 2, handle_.getPosition().y);
	}

	if (handle_.getPosition().x > window_->getSize().x)
	{
		handle_.setPosition(window_->getSize().x, handle_.getPosition().y);
	}

	if (handle_.getPosition().y > window_->getSize().y)
	{
		handle_.setPosition(handle_.getPosition().x, window_->getSize().y);
	}

	if (handle_.getPosition().y < 0)
	{
		handle_.setPosition(handle_.getPosition().x, 0);
	}

	real = (double)Utils::map(handle_.getPosition().x, window_->getSize().x / 2.f, window_->getSize().x, -2.f, 2.f);
	imag = (double)Utils::map(handle_.getPosition().y, 0.f, window_->getSize().y, -2.f, 2.f);
}

void Slider::render()
{
	window_->draw(handle_);
}