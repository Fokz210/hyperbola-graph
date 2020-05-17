#pragma once

#include "horisontal_slider.h"
#include "vertical_slider.h"
#include "Menu/Menu.h"
#include "hyperbola.h"
#include "ellipse.h"
#include "constants.h"
#include "canvas.h"

class model
{
public:
	model (window_manager& manager, float window_width, float window_height);

	void init (int A_ellipse, int B_ellipse, float thickness);
	void update ();
	void draw (sf::RenderTarget& window);

	void update_resolution (float window_width, float window_height);

	void lock ();
	void unlock ();
	void reset (int a, int b);
	void hide ();
	void show ();

	void set_scale (float scale);

	float m_window_width, m_window_height;

	window_manager& m_manager;
	hyperbola hyp;
	ellipse el;
	sf::CircleShape shape;
	sf::CircleShape cross1, cross2, cross3, cross4;

	horisontal_slider h_slider, h_slider2;
	vertical_slider v_slider, v_slider2;

	sf::RectangleShape X_axis, Y_axis;

	sf::CircleShape F1, F2;

	sw::Spline angle;

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
	float Phi;

	float slider_x, slider_x2, slider_y, slider_y2;
	float slider_x_prev;
	float slider_y_prev;
	float slider_x2_prev;
	float slider_y2_prev;

	float m_thickness;

	float dot_radius;

	char buffer[32];

	bool m_hidden;

	float m_scale;

	std::vector <std::vector<abstract_window *>::iterator> slider_iterators;
};

