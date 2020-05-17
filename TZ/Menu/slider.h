#pragma once
#include "rectangular_window.h"

class slider :
	public rectangular_window
{
public:
	slider (int x, int y, int width, int height, sf::Color first_color, sf::Color second_color, float start_value);

	virtual bool mouse_button_pressed (sf::Event::MouseButtonEvent event) override;
	virtual bool mouse_button_released (sf::Event::MouseButtonEvent event) override;
	virtual bool global_mouse_button_released (sf::Event::MouseButtonEvent event) override;

	virtual bool mouse_move (sf::Event::MouseMoveEvent event) override;

	virtual void draw (sf::RenderTarget & target) override;

	virtual void set_position (const sf::Vector2f & position) override
	{
		shape_.setPosition (position);
		m_path_shape.setPosition (position.x, position.y + shape_.getSize().y / 2 - 5.f);
		m_slider_shape.setPosition (shape_.getPosition ().x + shape_.getSize ().x * m_value, shape_.getPosition ().y + shape_.getSize ().y / 2);
	}

	float get_value () const;

	void hide ();
	void show ();

	void reset ();

protected:
	float m_value;

	sf::RectangleShape m_path_shape;
	sf::RectangleShape m_slider_shape;

	sf::Vector2f m_mouse_offset;
	bool m_mouse_pressed;

	bool m_hidden;
};


inline slider::slider (int x, int y, int width, int height, sf::Color first_color, sf::Color second_color, float start_value) :
	rectangular_window (x, y, width, height, sf::Color::Transparent),
	m_value (start_value),
	m_path_shape (),
	m_slider_shape (),
	m_mouse_offset (),
	m_mouse_pressed (false),
	m_hidden (false)
{
	m_path_shape.setSize (sf::Vector2f (width, 10.f));
	m_path_shape.setPosition (x, y + height / 2 - 5.f);
	m_path_shape.setFillColor (first_color);
	
	m_slider_shape.setSize (sf::Vector2f (10.f, height));
	m_slider_shape.setOrigin (sf::Vector2f (5.f, height / 2));
	m_slider_shape.setPosition (sf::Vector2f (x + width * start_value, y + height / 2));
	m_slider_shape.setFillColor (second_color);
}

inline bool slider::mouse_button_pressed (sf::Event::MouseButtonEvent event)
{
	if (m_hidden)
		return false;

	if (m_slider_shape.getGlobalBounds ().contains (event.x, event.y))
	{
		m_mouse_pressed = true;
		m_mouse_offset = sf::Vector2f (event.x - m_slider_shape.getPosition ().x, event.y - m_slider_shape.getPosition ().y);

		return true;
	}

	return false;
}

inline bool slider::mouse_button_released (sf::Event::MouseButtonEvent event)
{
	if (m_hidden)
		return false;

	m_mouse_pressed = false;
	return false;
}

inline bool slider::global_mouse_button_released (sf::Event::MouseButtonEvent event)
{
	if (m_hidden)
		return false;

	m_mouse_pressed = false;
	return false;
}

inline bool slider::mouse_move (sf::Event::MouseMoveEvent event)
{
	if (m_hidden)
		return false;

	if (m_mouse_pressed)
	{
		if (!sf::Mouse::isButtonPressed (sf::Mouse::Left))
		{
			m_mouse_pressed = false;
			return false;
		}

		m_slider_shape.setPosition (event.x + m_mouse_offset.x, m_slider_shape.getPosition ().y);

		if (m_slider_shape.getPosition().x > shape_.getPosition().x + shape_.getSize().x)
			m_slider_shape.setPosition (shape_.getPosition ().x + shape_.getSize ().x, m_slider_shape.getPosition ().y);

		if (m_slider_shape.getPosition ().x < shape_.getPosition ().x)
			m_slider_shape.setPosition (shape_.getPosition ().x, m_slider_shape.getPosition ().y);

		m_value = (m_slider_shape.getPosition ().x - shape_.getPosition ().x) / shape_.getSize ().x;

		return true;
	}

	return false;
}

inline void slider::draw (sf::RenderTarget & target)
{
	if (m_hidden)
		return;

	target.draw (m_path_shape);
	target.draw (m_slider_shape);
}

inline float slider::get_value () const
{
	return m_value;
}

inline void slider::hide ()
{
	m_hidden = true;
}

inline void slider::show ()
{
	m_hidden = false;
}

inline void slider::reset ()
{
	m_value = 0.f;

	m_slider_shape.setPosition (shape_.getPosition ().x + shape_.getSize ().x / 2, m_slider_shape.getPosition ().y);
}
