#include "canvas.h"
#include <stdexcept>

canvas::canvas (float left, float top, float width, float height) :
	m_texture_ptr (new sf::RenderTexture ()),
	m_sprite ()
{
	m_texture_ptr->create (width, height);
	m_sprite.setTexture (m_texture_ptr->getTexture (), true);
	m_sprite.setPosition (left, top);
}

canvas::~canvas ()
{
	if (!m_texture_ptr)
	{
		throw std::runtime_error ("Failed to destruct canvas!");
		return;
	}

	delete m_texture_ptr;
}

void canvas::draw (const sf::Drawable & drawable)
{
	m_texture_ptr->draw (drawable);
}

void canvas::display ()
{
	m_texture_ptr->display ();
}

void canvas::clear (sf::Color clear_color)
{
	m_texture_ptr->clear (clear_color);
}

void canvas::set_pos (const sf::Vector2f & pos)
{
	m_sprite.setPosition (pos);
}

void canvas::resize (const sf::Vector2f & size)
{
	delete m_texture_ptr;

	m_texture_ptr = new sf::RenderTexture;
	m_texture_ptr->create (size.x, size.y);

	m_sprite.setTexture (m_texture_ptr->getTexture (), true);
}

const sf::Vector2f & canvas::get_pos ()
{
	return m_sprite.getPosition ();
}

const sf::Vector2u & canvas::get_size ()
{
	return m_texture_ptr->getSize ();
}

