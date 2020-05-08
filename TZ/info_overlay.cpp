#include "info_overlay.h"

info_overlay::info_overlay (sf::Font font, float window_width, float window_height) :
	m_window_height (window_height),
	m_window_width (window_width),
	buffer (""),
	E_el_text (),
	E_hyp_text (),
	P_hyp_text (),
	S_hyp_text (),
	A_hyp_text (),
	B_hyp_text (),
	P_el_text (),
	P_c_text (),
	S_c_text (),
	S_el_text (),
	R_c_text (),
	A_el_text (),
	B_el_text (),
	C_el_text (),
	C_hyp_text (),
	m_font (font),
	gap_x (30.f),
	gap_y (30.f)
{
}

void info_overlay::init ()
{
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
	
	E_hyp_text = E_el_text;
	E_hyp_text.setFillColor (sf::Color::Black);
	A_hyp_text = E_hyp_text;
	P_hyp_text = E_hyp_text;
	S_hyp_text = E_hyp_text;
	B_hyp_text = E_hyp_text;
	C_hyp_text = E_hyp_text;

	E_el_text.setPosition (gap_x, gap_y);
	P_el_text.setPosition (gap_x, gap_y + 25);
	S_el_text.setPosition (gap_x, gap_y + 50);
	A_el_text.setPosition (gap_x, gap_y + 75);
	B_el_text.setPosition (gap_x, gap_y + 100);
	C_el_text.setPosition (gap_x, gap_y + 125);

	E_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y);
	P_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 25);
	S_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 50);
	A_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 75);
	B_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 100);
	C_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 125);

	S_c_text.setPosition (gap_x, m_window_height - gap_y - 25);
	P_c_text.setPosition (gap_x, m_window_height - gap_y - 50);
	R_c_text.setPosition (gap_x, m_window_height - gap_y - 75);
}

void info_overlay::update (float E_el, float P_el, float S_el, float E_hyp, float r_circ, float A_el, float B_el, float A_hyp, float B_hyp, float C)
{

	sprintf_s <32> (buffer, "E (el) = %.2f", E_el);
	E_el_text.setString (buffer);

	sprintf_s <32> (buffer, "P (el) = %.2f", P_el);
	P_el_text.setString (buffer);

	sprintf_s <32> (buffer, "E (hyp) = %.2f", E_hyp);
	E_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "P (hyp) = ");
	P_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "S (hyp) = ");
	S_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "R (circ) = %.2f", r_circ);
	R_c_text.setString (buffer);

	sprintf_s <32> (buffer, "P (circ) = %.2f", 2 * 3.1415 * r_circ);
	P_c_text.setString (buffer);

	sprintf_s <32> (buffer, "A (el) = %.2f", A_el);
	A_el_text.setString (buffer);

	sprintf_s <32> (buffer, "B (el) = %.2f", B_el);
	B_el_text.setString (buffer);

	sprintf_s <32> (buffer, "A (hyp) = %.2f", A_hyp);
	A_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "B (hyp) = %.2f", B_hyp);
	B_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "C (el) = %.2f", C);
	C_el_text.setString (buffer);

	sprintf_s <32> (buffer, "C (hyp) = %.2f", C);
	C_hyp_text.setString (buffer);

	sprintf_s <32> (buffer, "S (circ) = %.2f", 3.1415 * r_circ * r_circ);
	S_c_text.setString (buffer);

	sprintf_s <32> (buffer, "S (el) = %.2f", S_el);
	S_el_text.setString (buffer);
}

void info_overlay::draw (sf::RenderTarget& window)
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
}

void info_overlay::update_resolution (float window_width, float window_height)
{
	m_window_height = window_height;
	m_window_width = window_width;

	E_el_text.setPosition (gap_x, gap_y);
	P_el_text.setPosition (gap_x, gap_y + 25);
	S_el_text.setPosition (gap_x, gap_y + 50);
	A_el_text.setPosition (gap_x, gap_y + 75);
	B_el_text.setPosition (gap_x, gap_y + 100);
	C_el_text.setPosition (gap_x, gap_y + 125);

	E_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y);
	P_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 25);
	S_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 50);
	A_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 75);
	B_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 100);
	C_hyp_text.setPosition (m_window_width - 150 - gap_x, gap_y + 125);

	S_c_text.setPosition (gap_x, m_window_height - gap_y - 25);
	P_c_text.setPosition (gap_x, m_window_height - gap_y - 50);
	R_c_text.setPosition (gap_x, m_window_height - gap_y - 75);
}