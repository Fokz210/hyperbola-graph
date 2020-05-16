#pragma once
#include "constants.h"
#include "SFML/Graphics.hpp"
#include "Menu/Menu.h"

class info_overlay :
	public rectangular_window
{
public:
	info_overlay (sf::Font font, float window_width, float window_height);

	void init ();
	void update (float E_el, float P_el, float S_el, float E_hyp, float r_circ, float A_el, float B_el, float A_hyp, float B_hyp, float C);

	virtual void draw (sf::RenderTarget & target) override;

	void update_resolution (float window_width, float window_height);
	
protected:


	float m_window_width;
	float m_window_height;

	char buffer[32];

	sf::Text E_el_text;
	sf::Text E_hyp_text;
	sf::Text P_hyp_text;
	sf::Text S_hyp_text;
	sf::Text A_hyp_text;
	sf::Text B_hyp_text;
	sf::Text P_el_text; 
	sf::Text S_el_text; 
	sf::Text P_c_text;
	sf::Text R_c_text;
	sf::Text S_c_text;
	sf::Text A_el_text;
	sf::Text B_el_text;
	sf::Text C_el_text;
	sf::Text C_hyp_text;
	
	sf::Font m_font;

	sf::RectangleShape m_left_column, m_right_column;
	sf::RectangleShape m_left_separator, m_right_separator;

	float gap_x, gap_y;
};

