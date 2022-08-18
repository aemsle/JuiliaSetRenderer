#include "Button.h"

Button::Button(sf::RenderWindow* window)
{
	window_ = window;
	button_.setFillColor(sf::Color::Green);
	button_.setSize({ 20,20 });
}

Button::~Button()
{
}

void Button::update()
{
	float mouse_x = mouse.getPosition().x - window_->getPosition().x;
	float mouse_y = mouse.getPosition().y - window_->getPosition().y;

	if (mouse_x > button_.getPosition().x && mouse_x < button_.getPosition().x + 20 &&
		mouse_y > button_.getPosition().y && mouse_y < button_.getPosition().y + 20)
	{
		button_.setFillColor(sf::Color::Red);

		if (mouse.isButtonPressed(mouse.Left))
		{
			onClick();
		}
	}
	else
	{
		button_.setFillColor(sf::Color::Green);
	}

	button_.setPosition({ (float)window_->getSize().x - 40 }, 20);
}

void Button::onClick()
{
	window_->close();
}

void Button::render()
{
	window_->draw(button_);
}