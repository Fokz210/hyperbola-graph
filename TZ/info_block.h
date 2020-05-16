#pragma once
#include "Menu/rectangular_window.h"
#include "model.h"
class info_block :
	public rectangular_window
{
public:
	info_block (model & info_source, sf::Font font);

	void init ();
	void update ();
	virtual void draw (sf::RenderTarget & window) override;

	void set_title (const sf::String & title);
	
	void set_position (const sf::Vector2f & position);

protected:
	model & m_model;

	char buffer[32];

	sf::Text m_title;

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
};

