#ifndef sqr
#define sqr(a)  ((a) * (a))
#endif 

#include "constants.h"

// Размер окна

#include <cmath>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include "SelbaWard.hpp"
#include "horisontal_slider.h"
#include "vertical_slider.h"
#include "Menu/Menu.h"
#include "ellipse.h"
#include "hyperbola.h"
#include "model.h"

// ----------------------------------------------------------------------------\
//						Изначально задается:                                   |
//					A_el - большая полуось эллипса							   |
//				    B_el - малая полуось эллипса                               |
//																			   |
//						Из них рассчитываются переменные:                      |
//					C = (A_el ^ 2 - B_el ^ 2) ^ (1/2) - фокус				   |
//																			   |
//					A_hyp = C ^ 2 / A_el - большая полуось гиперболы           |
//					B_hyp = C ^ 2 - A_hyp ^ 2 - малая полуось гиперболы        |
//																			   |
//					E_el = C / A_el - эксцентриситет эллипса				   |
//					E_hyp = C / A_hyp - эксцентриситет гиперболы			   |
// ----------------------------------------------------------------------------/

int APIENTRY WinMain (
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
	)
{
	float dot_radius = 5.f;
	float thickness = 2.f;

	sf::RenderWindow window (sf::VideoMode (WINDOW_WIDTH, WINDOW_HEIGHT), "Test", sf::Style::Titlebar | sf::Style::Close);

	sf::Font font;
	font.loadFromFile ("font.ttf");

	sf::Text E_el_text;
	E_el_text.setFont (font);
	E_el_text.setCharacterSize (20);
	E_el_text.setFillColor (sf::Color::Black);

	sf::Text E_hyp_text(E_el_text), S_el_text (E_el_text), S_c_text (E_el_text), R_c_text (E_el_text), A_el_text (E_el_text), B_el_text (E_el_text);

	E_el_text.setPosition (10, 10);
	S_el_text.setPosition (10, 30);
	E_hyp_text.setPosition (WINDOW_WIDTH - 150, 10);
	S_c_text.setPosition (10, WINDOW_HEIGHT - 30);
	R_c_text.setPosition (10, WINDOW_HEIGHT - 50);
	A_el_text.setPosition (WINDOW_WIDTH - 150, WINDOW_HEIGHT - 50);
	B_el_text.setPosition (WINDOW_WIDTH - 150, WINDOW_HEIGHT - 30);

	char buffer[32] = "";

	window_manager w_manager;

	model first_model (w_manager);
	first_model.init (300, 300, thickness);
	model second_model (w_manager);
	second_model.init (100, 100, thickness);

	while (window.isOpen ())
	{
		window.clear (sf::Color::White);

		sf::Event event;
		while (window.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
				window.close ();

			if (event.type == sf::Event::MouseMoved)
				w_manager.update_cursor (event.mouseMove, window.getSystemHandle ());

			w_manager.handle_event (event);
		}

		first_model.update ();
		second_model.update ();

		sprintf_s <32> (buffer, "E (el) = %.2f", first_model.E_el);
		E_el_text.setString (buffer);

		sprintf_s <32> (buffer, "S (el) = %.2f", first_model.S_el);
		S_el_text.setString (buffer);

		sprintf_s <32> (buffer, "E (hyp) = %.2f", first_model.E_hyp);
		E_hyp_text.setString (buffer);

		sprintf_s <32> (buffer, "R (circ) = %.2f", first_model.r_circ);
		R_c_text.setString (buffer);

		sprintf_s <32> (buffer, "S (circ) = %.2f", 2 * 3.1415 * first_model.r_circ);
		S_c_text.setString (buffer);

		sprintf_s <32> (buffer, "A (el) = %.2f", first_model.A_el);
		A_el_text.setString (buffer);

		sprintf_s <32> (buffer, "B (el) = %.2f", first_model.B_el);
		B_el_text.setString (buffer);

#ifdef MY_DEBUG
		w_manager.draw_windows (window);
#endif // MY_DEBUG

		first_model.draw (window);
		second_model.draw (window);

		window.draw (E_el_text);
		window.draw (S_el_text);
		window.draw (E_hyp_text);
		window.draw (R_c_text);
		window.draw (S_c_text);
		window.draw (A_el_text);
		window.draw (B_el_text);

		window.display ();
	}

	return 0;
}
