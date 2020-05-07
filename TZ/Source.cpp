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
#include "info_overlay.h"

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

	sf::RenderWindow window (sf::VideoMode (WINDOW_WIDTH, WINDOW_HEIGHT), "Test");

	window.setView (window.getDefaultView ());
	sf::Font font;
	font.loadFromFile ("font.ttf");

	window_manager w_manager;

	model first_model (w_manager, window.getSize().x, window.getSize().y);
	first_model.init (100, 100, thickness);
	model second_model (w_manager, window.getSize ().x, window.getSize ().y);
	//second_model.init (100, 100, thickness);

	info_overlay overlay (font, WINDOW_WIDTH, WINDOW_HEIGHT);

	overlay.init ();

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

			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea (0, 0, event.size.width, event.size.height);
				window.setView (sf::View (visibleArea));

				overlay.update_resolution (event.size.width, event.size.height);
				first_model.update_resolution (event.size.width, event.size.height);
				
			}

			w_manager.handle_event (event);
		}

		first_model.update ();
		//second_model.update ();

		overlay.update (first_model.E_el, first_model.S_el, first_model.E_hyp, first_model.r_circ, first_model.r_circ * 3.1415f * 2, first_model.A_el, first_model.B_el, first_model.A_hyp, first_model.B_hyp, first_model.C);

#ifdef MY_DEBUG
		w_manager.draw_windows (window);
#endif // MY_DEBUG

		first_model.draw (window);
		//second_model.draw (window);
		overlay.draw (window);

		window.display ();
	}

	return 0;
}
