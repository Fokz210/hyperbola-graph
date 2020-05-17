#include "pch.h"
#include "rectangular_window.h"

rectangular_window::rectangular_window () :
	abstract_window (),
	shape_ ()
{
}

rectangular_window::rectangular_window (const sf::RectangleShape & shape) :
	abstract_window (),
	shape_ (shape)
{
}

rectangular_window::rectangular_window (float x, float y, float width, float height, sf::Color color) :
	abstract_window (),
	shape_ ()
{
	shape_.setPosition (sf::Vector2f (x, y));
	shape_.setSize (sf::Vector2f (width, height));
	shape_.setFillColor (color);
}

sf::RectangleShape & rectangular_window::get_shape () 
{
	return shape_;
}

void rectangular_window::set_shape (const sf::RectangleShape & shape)
{
	shape_ = shape;
}

void rectangular_window::set_position (const sf::Vector2f & position)
{
	shape_.setPosition (position);
}

void rectangular_window::draw (sf::RenderTarget & target)
{
	target.draw (shape_);
}

bool rectangular_window::contains (const sf::Vector2f & point)
{
	return shape_.getGlobalBounds().contains (point);
}

bool rectangular_window::mouse_move (sf::Event::MouseMoveEvent event)
{
	return false;
}

bool rectangular_window::mouse_button_pressed (sf::Event::MouseButtonEvent event)
{
	return false;
}

bool rectangular_window::mouse_button_released (sf::Event::MouseButtonEvent event)
{
	return false;
}

bool rectangular_window::keyboard_key_pressed (sf::Event::KeyEvent event)
{
	return false;
}

bool rectangular_window::keyboard_key_released (sf::Event::KeyEvent event)
{
	return false;
}

bool rectangular_window::keyboard_text_entered (sf::Event::KeyEvent event)
{
	return false;
}

bool rectangular_window::global_mouse_button_pressed (sf::Event::MouseButtonEvent event)
{
	return false;
}

bool rectangular_window::global_mouse_button_released (sf::Event::MouseButtonEvent event)
{
	return false;
}

cursor rectangular_window::get_cursor ()
{
	return cursor (cursor::NORMAL);
}
