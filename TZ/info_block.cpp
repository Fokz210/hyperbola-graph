#include "info_block.h"


info_block::info_block (model & info_source, sf::Font font) :
	rectangular_window (sf::RectangleShape ()),
	m_model (info_source),
	m_font (font),
	buffer (""),
	m_title (),
	m_phi_texture (),
	m_phi_sprite ()
{
	sf::Image img;
	img.loadFromFile ("phi.png");
	m_phi_texture.loadFromImage (img);
	m_phi_sprite.setTexture (m_phi_texture, true);
}

void info_block::init ()
{
	float gap_x = shape_.getPosition ().x;
	float gap_y = shape_.getPosition ().y;

	float character_size = 25;

	m_phi_sprite.setPosition (gap_x + 1, gap_y + character_size * 4 + 15);

	E_el_text.setFont (m_font);
	E_el_text.setCharacterSize (20);
	E_el_text.setFillColor (sf::Color (25, 118, 194));

	E_el_text.setStyle (sf::Text::Bold);
	
	P_el_text = E_el_text;
	S_el_text = E_el_text;
	A_el_text = E_el_text; 
    B_el_text = E_el_text;
    C_el_text = E_el_text;

	P_c_text = E_el_text;
	P_c_text.setFillColor (sf::Color (235, 122, 40));
	R_c_text = P_c_text;
	S_c_text = P_c_text;
	Phi_text = P_c_text;
	
	E_hyp_text = E_el_text;
	E_hyp_text.setFillColor (sf::Color::Black);
	A_hyp_text = E_hyp_text;
	P_hyp_text = E_hyp_text;
	S_hyp_text = E_hyp_text;
	B_hyp_text = E_hyp_text;
	C_hyp_text = E_hyp_text;

	m_title.setCharacterSize (20);
	m_title.setFillColor (sf::Color::Black);
	m_title.setFont (m_font);
	m_title.setStyle (sf::Text::Bold);

	m_title.setPosition (gap_x, gap_y);

	S_c_text.setPosition (gap_x, gap_y + character_size + 10);
	P_c_text.setPosition (gap_x, gap_y + character_size * 2 + 10);
	R_c_text.setPosition (gap_x, gap_y + character_size * 3 + 10);
	Phi_text.setPosition (gap_x, gap_y + character_size * 4 + 10);

	E_el_text.setPosition (gap_x, gap_y + character_size * 5 + 15);
	P_el_text.setPosition (gap_x, gap_y + character_size * 6 + 15);
	S_el_text.setPosition (gap_x, gap_y + character_size * 7 + 15);
	A_el_text.setPosition (gap_x, gap_y + character_size * 8 + 15);
	B_el_text.setPosition (gap_x, gap_y + character_size * 9 + 15);
	C_el_text.setPosition (gap_x, gap_y + character_size * 10 + 15);

	E_hyp_text.setPosition (gap_x, gap_y + character_size * 11 + 20);
	P_hyp_text.setPosition (gap_x, gap_y + character_size * 12 + 20);
	S_hyp_text.setPosition (gap_x, gap_y + character_size * 13 + 20);
	A_hyp_text.setPosition (gap_x, gap_y + character_size * 14 + 20);
	B_hyp_text.setPosition (gap_x, gap_y + character_size * 15 + 20);
	C_hyp_text.setPosition (gap_x, gap_y + character_size * 16 + 20);
}

void info_block::update ()
{
	sprintf_s <32> (buffer, "E (el) = %.2f", m_model.E_el);
	E_el_text.setString (buffer);

	sprintf_s <32> (buffer, "P (el) = %.2f", m_model.A_el * m_model.B_el * 3.1415);
	P_el_text.setString (buffer);

	sprintf_s <32> (buffer, "E (hyp) = %.2f", m_model.E_hyp);
	E_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "P (hyp) = ");
	P_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "S (hyp) = ");
	S_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "R (circ) = %.2f", m_model.r_circ);
	R_c_text.setString (buffer);

	sprintf_s <32> (buffer, "P (circ) = %.2f", 2 * 3.1415 * m_model.r_circ);
	P_c_text.setString (buffer);

	sprintf_s <32> (buffer, "A (el) = %.2f", m_model.A_el);
	A_el_text.setString (buffer);

	sprintf_s <32> (buffer, "B (el) = %.2f", m_model.B_el);
	B_el_text.setString (buffer);

	sprintf_s <32> (buffer, "A (hyp) = %.2f", m_model.A_hyp);
	A_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "B (hyp) = %.2f", m_model.B_hyp);
	B_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "C (el) = %.2f", m_model.C);
	C_el_text.setString (buffer);

	sprintf_s <32> (buffer, "C (hyp) = %.2f", m_model.C);
	C_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "S (circ) = %.2f", 3.1415 * m_model.r_circ * m_model.r_circ);
	S_c_text.setString (buffer);

	sprintf_s <32> (buffer, "S (el) = %.2f", m_model.S_el);
	S_el_text.setString (buffer);

	sprintf_s <32> (buffer, "   = %.2f", m_model.Phi);
	Phi_text.setString (buffer);
}

void info_block::draw (sf::RenderTarget & window)
{
	window.draw (E_el_text);
	window.draw (P_el_text);
	window.draw (S_el_text);
	window.draw (A_hyp_text);
	window.draw (B_hyp_text);
	window.draw (E_hyp_text);
	window.draw (R_c_text);
	window.draw (P_c_text);
	window.draw (S_c_text);
	window.draw (A_el_text);
	window.draw (B_el_text);
	window.draw (C_el_text);
	window.draw (C_hyp_text);
	window.draw (P_hyp_text);
	window.draw (S_hyp_text);
	window.draw (Phi_text);
	window.draw (m_title);
	window.draw (m_phi_sprite);
}

void info_block::set_title (const sf::String & title)
{
	m_title.setString (title);
}

void info_block::set_position (const sf::Vector2f & position)
{
	shape_.setPosition (position);
	
	init ();
}
