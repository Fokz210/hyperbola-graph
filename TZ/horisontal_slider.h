#pragma once
#include "Menu/rectangular_window.h"

class horisontal_slider :
	public rectangular_window
{
public:
	horisontal_slider (const sf::RectangleShape & shape, float & x, float y, float xmin, float xmax);

	virtual bool global_mouse_button_released (sf::Event::MouseButtonEvent event) override;
	virtual bool mouse_button_pressed (sf::Event::MouseButtonEvent event) override;
	virtual bool mouse_button_released (sf::Event::MouseButtonEvent event) override;

	virtual bool mouse_move (sf::Event::MouseMoveEvent event) override;

	virtual cursor get_cursor () override;

	void lock ();
	void unlock ();

	float & x_;
	bool pressed_;
	float xmin_, xmax_;
	sf::Vector2f offset_;

	bool locked_;
};

