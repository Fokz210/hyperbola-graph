#pragma once

#include "horisontal_slider.h"
#include "vertical_slider.h"
#include "Menu/Menu.h"
#include "hyperbola.h"
#include "ellipse.h"
#include "constants.h"

class model
{
public:
	model (window_manager& manager);

	void init (int A_ellipse, int B_ellipse, float thickness);
	void update ();
	void draw (sf::RenderTarget& window);

	window_manager& m_manager;
	hyperbola hyp;
	ellipse el;
	sf::CircleShape shape;
	sf::CircleShape cross1, cross2, cross3, cross4;

	horisontal_slider h_slider, h_slider2;
	vertical_slider v_slider, v_slider2;

	sf::RectangleShape X_axis, Y_axis;

	sf::CircleShape F1, F2;

	float A_el;
	float B_el;
	float C;
	float A_hyp;
	float B_hyp;
	float dot_x;
	float dot_y;
	float r_circ;
	float E_el;
	float E_hyp;
	float S_el;
	float S_c;

	float slider_x, slider_x2, slider_y, slider_y2;
	float slider_x_prev;
	float slider_y_prev;
	float slider_x2_prev;
	float slider_y2_prev;

	float m_thickness;

	float dot_radius;

	char buffer[32];
};

