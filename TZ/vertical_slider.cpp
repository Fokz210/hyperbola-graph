#include "vertical_slider.h"

vertical_slider::vertical_slider (const sf::RectangleShape & shape, float x, float & y, float ymin, float ymax) :
	rectangular_window (shape),
	y_ (y),
	pressed_ (false),
	offset_ (),
	ymin_ (ymin),
	ymax_ (ymax),
	locked_ (false)
{
	shape_.setOrigin (sf::Vector2f (shape_.getSize ().x / 2, shape_.getSize ().y / 2));
	shape_.setPosition (x, y);
}

bool vertical_slider::global_mouse_button_released (sf::Event::MouseButtonEvent event)
{
	if (locked_)
		return false;

	pressed_ = false;
	return false;
}

bool vertical_slider::mouse_button_pressed (sf::Event::MouseButtonEvent event)
{
	if (locked_)
		return false;

	pressed_ = true;
	offset_ = sf::Vector2f (event.x - shape_.getPosition ().x, event.y - shape_.getPosition ().y);

	return true;
}

bool vertical_slider::mouse_button_released (sf::Event::MouseButtonEvent event)
{
	if (locked_)
		return false;

	pressed_ = false;
	return false;
}

bool vertical_slider::mouse_move (sf::Event::MouseMoveEvent event)
{
	if (pressed_ && !locked_)
	{
		if (!sf::Mouse::isButtonPressed (sf::Mouse::Left))
			pressed_ = false;

		if (event.y >= ymax_ || event.y <= ymin_)
		{
			return false;
		}

		shape_.setPosition (shape_.getPosition ().x , event.y - offset_.y);
		y_ = event.y - offset_.y;

#ifdef MY_DEBUG
		printf ("[info] Changed y to %f\n", y_);
#endif // MY_DEBUG
	}

	return false;
}

void vertical_slider::lock ()
{
	locked_ = true;
}

void vertical_slider::unlock ()
{
	locked_ = false;
}

cursor vertical_slider::get_cursor ()
{
	if (locked_)
		return cursor::NORMAL;
	return cursor::HAND;
}

