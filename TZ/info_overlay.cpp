#include "info_overlay.h"

#define COLUMN_SIZE 220.f

info_overlay::info_overlay (sf::Font font, float window_width, float window_height, model & info_source1) :
	rectangular_window (sf::RectangleShape ()),
	m_window_height (window_height),
	m_window_width (window_width),
	buffer (""),
	block1 (info_source1, font),
	gap_x (30.f),
	gap_y (30.f),
	m_left_column (),
	m_right_column (),
	m_left_separator (),
	m_right_separator ()
{
}

void info_overlay::init ()
{
	m_right_column.setSize (sf::Vector2f (COLUMN_SIZE, m_window_height));
	m_right_column.setPosition (sf::Vector2f (m_window_width - COLUMN_SIZE, 0.f));
	m_right_column.setFillColor (sf::Color (245, 245, 245));

	m_left_column = m_right_column;
	m_left_column.setPosition (0.f, 0.f);

	m_left_separator.setSize (sf::Vector2f (1.f, m_window_height));
	m_left_separator.setFillColor (sf::Color (125, 125, 125));
	m_left_separator.setPosition (sf::Vector2f (COLUMN_SIZE - 1.f, 0));

	m_right_separator = m_left_separator;
	m_left_separator.setPosition (m_window_width - COLUMN_SIZE, 0);

	block1.set_position (sf::Vector2f (gap_x, gap_y));
	block1.set_title ("Iteration #1");
}

void info_overlay::update ()
{
	block1.update ();
}

void info_overlay::draw (sf::RenderTarget& window)
{
	window.draw (m_left_column);
	window.draw (m_right_column);
	window.draw (m_left_separator);
	window.draw (m_right_separator);

	block1.draw (window);
}

void info_overlay::update_resolution (float window_width, float window_height)
{
	m_window_height = window_height;
	m_window_width = window_width;

	m_right_column.setSize (sf::Vector2f (COLUMN_SIZE, m_window_height));
	m_right_column.setPosition (sf::Vector2f (m_window_width - COLUMN_SIZE, 0.f));

	m_left_column = m_right_column;
	m_left_column.setPosition (0.f, 0.f);

	m_left_separator.setSize (sf::Vector2f (1.f, m_window_height));
	m_left_separator.setPosition (sf::Vector2f (COLUMN_SIZE - 1.f, 0));

	m_right_separator = m_left_separator;
	m_left_separator.setPosition (m_window_width - COLUMN_SIZE, 0);
}