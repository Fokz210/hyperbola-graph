#pragma once
#include "constants.h"
#include "SFML/Graphics.hpp"

class info_overlay
{
public:
	info_overlay (sf::Font font, float window_width, float window_height);

	void init ();
	void update (float E_el, float S_el, float E_hyp, float r_circ, float S_sirc, float A_el, float B_el, float A_hyp, float B_hyp, float C);
	void draw (sf::RenderTarget & window);

	void update_resolution (float window_width, float window_height);
	
protected:
	float m_window_width;
	float m_window_height;

	char buffer[32];

	sf::Text E_el_text;
	sf::Text E_hyp_text;
	sf::Text A_hyp_text;
	sf::Text B_hyp_text;
	sf::Text S_el_text; 
	sf::Text S_c_text;
	sf::Text R_c_text;
	sf::Text A_el_text;
	sf::Text B_el_text;
	sf::Text C_el_text;
	sf::Text C_hyp_text;
	
	sf::Font m_font;

	float gap_x, gap_y;
};

