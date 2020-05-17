#pragma once
#include "constants.h"
#include "SFML/Graphics.hpp"
#include "Menu/Menu.h"
#include "info_block.h"
#include "Menu/slider.h"

class info_overlay :
	public rectangular_window
{
public:
	info_overlay (sf::Font font, float window_width, float window_height, std::vector <model *> & models);
	~info_overlay ();

	void init (window_manager & manager);
	void update ();

	virtual void draw (sf::RenderTarget & target) override;

	void update_resolution (float window_width, float window_height);
	
protected:
	float m_window_width;
	float m_window_height;

	char buffer[32];

	std::vector <info_block *> m_info_blocks;
	
	sf::RectangleShape m_left_column, m_right_column;
	sf::RectangleShape m_left_separator, m_right_separator;

	rectangular_window * m_reload_button_ptr, * m_next_button_ptr;

	float gap_x, gap_y;

	sf::Font m_font;

	std::vector <model *> & m_models;

	slider left, right;
};

