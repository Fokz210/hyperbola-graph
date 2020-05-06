#include "vertical_slider.h"

vertical_slider::vertical_slider (const sf::RectangleShape & shape, float x, float & y) :
	rectangular_window (shape),
	y_ (y),
	pressed_ (false),
	offset_ ()
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
		shape_.setPosition (shape_.getPosition ().x , event.y - offset_.y);
		y_ = event.y - offset_.y;
	}

	return false;
}

cursor vertical_slider::get_cursor ()
{
	return cursor::HAND;
}

