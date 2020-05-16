#pragma once
#include <SFML/Graphics.hpp>

class canvas
{
public:
	canvas (float left, float top, float width, float height);
	~canvas();

	operator sf::Drawable & ()
	{	
		return m_sprite;
	}
	
	operator sf::RenderTexture & ()
	{
		return *m_texture_ptr;
	}

	void draw (const sf::Drawable & drawable);
	void display ();
	void clear (sf::Color clear_color);

	void set_pos (const sf::Vector2f & pos);
	void resize (const sf::Vector2f & size);

	const sf::Vector2f & get_pos ();
	const sf::Vector2u & get_size ();

protected:
	sf::RenderTexture * m_texture_ptr;
	sf::Sprite m_sprite;
};

