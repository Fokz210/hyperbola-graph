#include "vertical_slider.h"

vertical_slider::vertical_slider (const sf::RectangleShape & shape, float x, float & y, float ymin, float ymax) :
	rectangular_window (shape),
	y_ (y),
	pressed_ (false),
	offset_ (),
	ymin_ (ymin),
	ymax_ (ymax)
{
	shape_.setOrigin (sf::Vector2f (shape_.getSize ().x / 2, shape_.getSize ().y / 2));
	shape_.setPosition (x, y);
}

bool vertical_slider::global_mouse_button_released (sf::Event::MouseButtonEvent event)
{
	pressed_ = false;
	return false;
}

bool vertical_slider::mouse_button_pressed (sf::Event::MouseButtonEvent event)
{
	pressed_ = true;
	offset_ = sf::Vector2f (event.x - shape_.getPosition ().x, event.y - shape_.getPosition ().y);

	return true;
}

bool vertical_slider::mouse_button_released (sf::Event::MouseButtonEvent event)
{
	pressed_ = false;
	return false;
}

bool vertical_slider::mouse_move (sf::Event::MouseMoveEvent event)
{
	if (pressed_)
	{
		if (!sf::Mouse::isButtonPressed (sf::Mouse::Left))
			pressed_ = false;

	/*	if (y_ > ymax_ || y_ < ymin_)
		{
			printf_s ("[WARN] Out of the limits. y_ = %f, ymax_ = %f, ymin = %f.\n", y_, ymax_, ymin_);
			return false;
		}
			*/

		shape_.setPosition (shape_.getPosition ().x , event.y - offset_.y);
		y_ = event.y - offset_.y;
	}

	return false;
}

cursor vertical_slider::get_cursor ()
{
	return cursor::HAND;
}

