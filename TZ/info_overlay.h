#pragma once
#include "constants.h"
#include "SFML/Graphics.hpp"
#include "Menu/Menu.h"
#include "info_block.h"

class info_overlay :
	public rectangular_window
{
public:
	info_overlay (sf::Font font, float window_width, float window_height, model & info_source1);

	void init ();
	void update ();

	virtual void draw (sf::RenderTarget & target) override;

	void update_resolution (float window_width, float window_height);
	
protected:


	float m_window_width;
	float m_window_height;

	char buffer[32];

	info_block block1;
	
	sf::RectangleShape m_left_column, m_right_column;
	sf::RectangleShape m_left_separator, m_right_separator;

	float gap_x, gap_y;
};

