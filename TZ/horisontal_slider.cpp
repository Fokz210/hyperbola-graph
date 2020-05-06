#include "horisontal_slider.h"

horisontal_slider::horisontal_slider (const sf::RectangleShape & shape, float & x, float y, float xmin, float xmax) :
	rectangular_window (shape),
	x_ (x),
	pressed_ (false),
	offset_ (),
	xmin_ (xmin),
	xmax_ (xmax)
{
	shape_.setOrigin (sf::Vector2f (shape_.getSize ().x / 2, shape_.getSize().y / 2));
	shape_.setPosition (x, y);
}

bool horisontal_slider::global_mouse_button_released (sf::Event::MouseButtonEvent event)
{
	pressed_ = false;
	return false;
}

bool horisontal_slider::mouse_button_pressed (sf::Event::MouseButtonEvent event)
{
	pressed_ = true;
	offset_ = sf::Vector2f (event.x - shape_.getPosition ().x, event.y - shape_.getPosition ().y);

	return true;
}

bool horisontal_slider::mouse_button_released (sf::Event::MouseButtonEvent event)
{
	pressed_ = false;
	return false;
}

bool horisontal_slider::mouse_move (sf::Event::MouseMoveEvent event)
{
	if (pressed_)
	{
		if (!sf::Mouse::isButtonPressed (sf::Mouse::Left))
			pressed_ = false;

		if (event.x > xmax_ || event.x  < xmin_)
			return false;

		shape_.setPosition (event.x - offset_.x, shape_.getPosition().y);
		x_ = event.x - offset_.x;
	}

	return false;
}

cursor horisontal_slider::get_cursor ()
{
	return cursor::HAND;
}

