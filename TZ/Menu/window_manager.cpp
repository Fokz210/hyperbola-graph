#include "pch.h"
#include "window_manager.h"

window_manager::window_manager () :
	windows_ (),
	active_ (nullptr)
{
}

window_manager::window_manager (std::vector<abstract_window *> windows) :
	windows_ (windows),
	active_ (nullptr)
{
}

std::vector<abstract_window *>::iterator window_manager::add_window (abstract_window * window)
{
	windows_.push_back (window);
	return --windows_.end();
}

void window_manager::remove_window (std::vector<abstract_window *>::iterator iterator)
{
	windows_.erase (iterator);
}

void window_manager::draw_windows (sf::RenderTarget & target)
{
	for (auto && el : windows_)
		el->draw (target);
}

bool window_manager::handle_event (const sf::Event & event)
{
	switch (event.type)
	{
	default:
		return false;

	case sf::Event::MouseButtonPressed:
		for (auto && el : windows_)
		{
			
			if (el->contains (sf::Vector2f (event.mouseButton.x, event.mouseButton.y)))
				if (el->mouse_button_pressed (event.mouseButton))
					return true;
		}
		return false;

	case sf::Event::MouseButtonReleased:
		for (auto && el : windows_)
			if (el->contains (sf::Vector2f (event.mouseButton.x, event.mouseButton.y)))
			{
				if (el->global_mouse_button_released (event.mouseButton))
					return true;

				if (el->mouse_button_released (event.mouseButton))
				{
					
					return true;
				}
			}
		if (!active_)
			return false;

		active_->deactivate ();
		active_ = nullptr;
		return false;

	case sf::Event::MouseMoved:
		for (auto && el : windows_)
		//	if (el->contains (sf::Vector2f (event.mouseMove.x, event.mouseMove.y)))
				if (el->mouse_move (event.mouseMove))
					return true;
		return false;

	case sf::Event::KeyPressed:
		for (auto && el : windows_)
			if (el->keyboard_key_pressed (event.key))
					return true;
		return false;

	case sf::Event::KeyReleased:
		for (auto && el : windows_)
			if (el->keyboard_key_released (event.key))
				return true;
		return false;

	case sf::Event::TextEntered:
		for (auto && el : windows_)
			if (el->keyboard_text_entered (event.key))
				return true;
		return false;
	}
}

void window_manager::update_cursor (const sf::Event::MouseMoveEvent & event, const sf::WindowHandle & handle)
{
	cursor normal (cursor::NORMAL);
	normal.Set (handle);

	for (auto && el : windows_)
		if (el->contains (sf::Vector2f (event.x, event.y)))
			el->get_cursor ().Set (handle);
}
