#include "pch.h"
#include "sprite_window.h"

sprite_window::sprite_window () :
	abstract_window (),
	sprite_ ()
{

}

sprite_window::sprite_window (sf::Sprite sprite) :
	abstract_window (),
	sprite_ (sprite)
{
}

sf::Sprite & sprite_window::get_sprite ()
{
	return sprite_;
}

void sprite_window::draw (sf::RenderTarget & target)
{
	target.draw (sprite_);
}

bool sprite_window::contains (const sf::Vector2f & point)
{
	return sprite_.getGlobalBounds().contains (point);
}

bool sprite_window::mouse_move (sf::Event::MouseMoveEvent event)
{
	return false;
}

bool sprite_window::mouse_button_pressed (sf::Event::MouseButtonEvent event)
{
	return false;
}

bool sprite_window::mouse_button_released (sf::Event::MouseButtonEvent event)
{
	return false;
}

bool sprite_window::keyboard_key_pressed (sf::Event::KeyEvent event)
{
	return false;
}

bool sprite_window::keyboard_key_released (sf::Event::KeyEvent event)
{
	return false;
}

bool sprite_window::keyboard_text_entered (sf::Event::KeyEvent event)
{
	return false;
}

cursor sprite_window::get_cursor ()
{
	return cursor (cursor::NORMAL);
}
