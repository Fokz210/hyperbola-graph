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
#include "Menu/slider.h"

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

#ifndef _DEBUG
int APIENTRY WinMain (
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
	)
#else
int main()
#endif
{
	float dot_radius = 5.f;
	float thickness = 2.f;

	sf::RenderWindow window (sf::VideoMode (WINDOW_WIDTH, WINDOW_HEIGHT), "Test");

	window.setView (window.getDefaultView ());

	sf::Font font;
	font.loadFromFile ("font.ttf");

	window_manager w_manager;

	std::vector <model *> models;
	models.push_back (nullptr);
	models.push_back (nullptr);

	info_overlay overlay (font, WINDOW_WIDTH, WINDOW_HEIGHT, models);

	w_manager.add_window (&overlay);

	overlay.init (w_manager);


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

				for (auto && el : models)
					el->update_resolution (event.size.width, event.size.height);

			}

			w_manager.handle_event (event);
		}

		for (auto && el : models)
		{
			if (el)
			{
				el->update ();
				el->draw (window);
			}
		}

		overlay.update ();
		w_manager.draw_windows (window);

		window.display ();

	}

	return 0;
}
