#pragma once
#include "Menu/rectangular_window.h"

class horisontal_slider :
	public rectangular_window
{
public:
	horisontal_slider (const sf::RectangleShape & shape, float & x, float y);

	virtual bool global_mouse_button_released (sf::Event::MouseButtonEvent event) override;
	virtual bool mouse_button_pressed (sf::Event::MouseButtonEvent event) override;
	virtual bool mouse_button_released (sf::Event::MouseButtonEvent event) override;

	virtual bool mouse_move (sf::Event::MouseMoveEvent event) override;

	virtual cursor get_cursor () override;

protected:
	float & x_;
	bool pressed_;
	sf::Vector2f offset_;
};

