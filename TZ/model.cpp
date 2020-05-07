#include "model.h"

#ifndef sqr
#define sqr(a)  ((a) * (a))
#endif 


model::model (window_manager& manager) :
	m_manager (manager),
	hyp (1, 1, 1, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2),
	el (200, 200),
	shape (),
	cross1 (),
	cross2 (),
	cross3 (),
	cross4 (),
	h_slider (sf::RectangleShape (), slider_x, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2 + 5, WINDOW_WIDTH),
	h_slider2 (sf::RectangleShape (), slider_x2, WINDOW_HEIGHT / 2, 0, WINDOW_WIDTH / 2 - 5),
	v_slider (sf::RectangleShape (), WINDOW_WIDTH / 2, slider_y, WINDOW_HEIGHT / 2 + 5, WINDOW_HEIGHT),
	v_slider2 (sf::RectangleShape (), WINDOW_WIDTH / 2, slider_y2, 0, WINDOW_HEIGHT / 2 - 5),
	X_axis (),
	Y_axis (),
	F1 (),
	F2 (),
	A_el (),
	B_el (),
	C (),
	A_hyp (),
	B_hyp (),
	dot_x (),
	dot_y (),
	r_circ (),
	E_el (),
	E_hyp (),
	S_el (),
	S_c (),
	slider_x (),
	slider_y (),
	slider_x2 (),
	slider_y2 (),
	slider_x_prev (),
	slider_y_prev (),
	slider_x2_prev (),
	slider_y2_prev (),
	buffer (""),
	m_thickness (),
	dot_radius (5.f)
{
}

void model::init (int A_ellipse, int B_ellipse, float thickness)
{
	hyp.set_color (sf::Color::Black);
	hyp.set_thickness (thickness);

	el.set_color (sf::Color (25, 118, 194));
	el.set_position (sf::Vector2f (WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	el.set_thickness (thickness);
	
	A_el = A_ellipse;
	B_el = B_ellipse;
	C = sqrtf (sqr (A_el) - sqr (B_el));

	A_hyp = sqr (C) / A_el;
	B_hyp = sqrtf (sqr (C) - sqr (A_hyp));

	dot_x = ((A_el * A_hyp) * sqrtf (sqr (B_el) + sqr (B_hyp))) / sqrtf (sqr (A_el * B_hyp) + sqr (B_el * A_hyp));
	dot_y = (B_el * sqrtf (sqr (A_el) - sqr (dot_x))) / A_el;

	r_circ = sqrt (sqr (dot_x) + sqr (dot_y));

	shape.setRadius (r_circ);
	shape.setOutlineColor (sf::Color (235, 122, 40));
	shape.setFillColor (sf::Color::Transparent);
	shape.setOutlineThickness (thickness);

	cross1.setRadius (dot_radius);
	cross2.setRadius (dot_radius);
	cross3.setRadius (dot_radius);
	cross4.setRadius (dot_radius);

	cross1.setOrigin (sf::Vector2f (dot_radius, dot_radius));
	cross2.setOrigin (sf::Vector2f (dot_radius, dot_radius));
	cross3.setOrigin (sf::Vector2f (dot_radius, dot_radius));
	cross4.setOrigin (sf::Vector2f (dot_radius, dot_radius));

	cross1.setFillColor (sf::Color::Red);
	cross2.setFillColor (sf::Color::Red);
	cross3.setFillColor (sf::Color::Red);
	cross4.setFillColor (sf::Color::Red);

	X_axis.setFillColor (sf::Color (214, 214, 214));
	Y_axis.setFillColor (sf::Color (214, 214, 214));

	slider_x = WINDOW_WIDTH / 2 + A_el;
	sf::RectangleShape slider_shape;
	slider_shape.setFillColor (sf::Color::Red);
	slider_shape.setSize (sf::Vector2f (50.f, 50.f));

	slider_shape.setOrigin (25, 25);
	
	h_slider.get_shape () = slider_shape;
	h_slider.get_shape ().setPosition (slider_x, WINDOW_HEIGHT / 2);

	slider_y = WINDOW_HEIGHT / 2 + B_el;
	v_slider.get_shape () = slider_shape;
	v_slider.get_shape ().setPosition (WINDOW_WIDTH / 2, slider_y);

    slider_x2 = WINDOW_WIDTH / 2 - A_el;
	h_slider2.get_shape () = slider_shape;
	h_slider2.get_shape ().setPosition (slider_x2, WINDOW_HEIGHT / 2);

	slider_y2 = WINDOW_HEIGHT / 2 - B_el;
	v_slider2.get_shape () = slider_shape;
	v_slider2.get_shape ().setPosition (WINDOW_WIDTH / 2, slider_y2);

	F1.setFillColor (sf::Color (0, 200, 0));
	F1.setRadius (thickness * 2);

	F2.setFillColor (sf::Color (0, 200, 0));
	F2.setRadius (thickness * 2);

	shape.setPointCount (100);

    slider_x_prev = slider_x;
	slider_y_prev = slider_y;
	slider_x2_prev = slider_x2;
	slider_y2_prev = slider_y2;

	m_manager.add_window (&h_slider);
	m_manager.add_window (&v_slider);
	m_manager.add_window (&v_slider2);
	m_manager.add_window (&h_slider2);


}

void model::update ()
{
#ifdef MY_DEBUGG
	printf ("[INFO] slider_x = %f\n", slider_x);
	printf ("[INFO] slider_y = %f\n", slider_y);
	printf ("[INFO] slider_x2 = %f\n", slider_x2);
	printf ("[INFO] slider_y2 = %f\n", slider_y2);
	printf ("[INFO] slider_x_prev = %f\n", slider_x_prev);
	printf ("[INFO] slider_y_prev = %f\n", slider_y_prev);
	printf ("[INFO] slider_x2_prev = %f\n", slider_x2_prev);
	printf ("[INFO] slider_y2_prev = %f\n", slider_y2_prev);
#endif // MY_DEBUG

	if (slider_x != slider_x_prev)
	{
		A_el = slider_x - WINDOW_WIDTH / 2;
		slider_x2 = WINDOW_WIDTH / 2 - A_el;
		h_slider2.get_shape ().setPosition (WINDOW_WIDTH / 2 - A_el, WINDOW_HEIGHT / 2);
	}
	else if (slider_x2 != slider_x2_prev)
	{
		A_el = WINDOW_WIDTH / 2 - slider_x2;
		slider_x = WINDOW_WIDTH / 2 + A_el;
		h_slider.get_shape ().setPosition (WINDOW_WIDTH / 2 + A_el, WINDOW_HEIGHT / 2);
	}
	else if (slider_y != slider_y_prev)
	{
		B_el = slider_y - WINDOW_HEIGHT / 2;
		slider_y2 = WINDOW_HEIGHT / 2 - B_el;
		v_slider2.get_shape ().setPosition (WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - B_el);

		/*	printf_s ("[INFO] slider_y is changed to %f. changing B_el to %f and slider_y2 to %f.\n", slider_y, B_el, slider_y2);*/
	}
	else if (slider_y2 != slider_y2_prev)
	{
		B_el = WINDOW_HEIGHT / 2 - slider_y2;
		slider_y = WINDOW_HEIGHT + B_el;
		v_slider.get_shape ().setPosition (WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + B_el);
	}

	C = sqrtf (sqr (A_el) - sqr (B_el));

	A_hyp = sqr (C) / A_el;
	B_hyp = sqrtf (sqr (C) + sqr (A_hyp));

	el.set_radius_x (A_el);
	el.set_radius_y (B_el);
	el.update ();

	hyp.set_a (A_hyp);
	hyp.set_b (B_hyp);
	hyp.update ();

	dot_x = ((A_el * A_hyp) * sqrtf (sqr (B_el) + sqr (B_hyp))) / sqrtf (sqr (A_el * B_hyp) + sqr (B_el * A_hyp));
	dot_y = (B_el * sqrtf (sqr (A_el) - sqr (dot_x))) / A_el;

	r_circ = sqrt (sqr (dot_x) + sqr (dot_y));

	cross1.setPosition (WINDOW_WIDTH / 2 + dot_x, WINDOW_HEIGHT / 2 + dot_y);
	cross2.setPosition (WINDOW_WIDTH / 2 - dot_x, WINDOW_HEIGHT / 2 + dot_y);
	cross3.setPosition (WINDOW_WIDTH / 2 + dot_x, WINDOW_HEIGHT / 2 - dot_y);
	cross4.setPosition (WINDOW_WIDTH / 2 - dot_x, WINDOW_HEIGHT / 2 - dot_y);

	shape.setRadius (r_circ - m_thickness);
	shape.setPosition (sf::Vector2f (WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	shape.setOrigin (sf::Vector2f (shape.getLocalBounds ().width / 2, shape.getLocalBounds ().height / 2));

	E_el = C / A_el;
	E_hyp = C / A_hyp;
	S_el = 2 * 2.1415 * sqrtf ((sqr (A_el) + sqr (B_el)) / 2);

	X_axis.setSize (sf::Vector2f (A_el * 2, m_thickness));
	Y_axis.setSize (sf::Vector2f (m_thickness, B_el * 2));

	X_axis.setPosition (sf::Vector2f (WINDOW_WIDTH / 2 - A_el, WINDOW_HEIGHT / 2 - m_thickness / 2));
	Y_axis.setPosition (sf::Vector2f (WINDOW_WIDTH / 2 - m_thickness / 2, WINDOW_HEIGHT / 2 - B_el));

	F1.setPosition (WINDOW_WIDTH / 2 - C - m_thickness * 2, WINDOW_HEIGHT / 2 - m_thickness * 2);
	F2.setPosition (WINDOW_WIDTH / 2 + C - m_thickness * 2, WINDOW_HEIGHT / 2 - m_thickness * 2);

	slider_x_prev = slider_x;
	slider_y_prev = slider_y;
	slider_x2_prev = slider_x2;
	slider_y2_prev = slider_y2;
}

void model::draw (sf::RenderTarget& window)
{
	window.draw (X_axis);
	window.draw (Y_axis);

	hyp.render (window);
	el.render (window);
	window.draw (shape);

	window.draw (cross1);
	window.draw (cross2);
	window.draw (cross3);
	window.draw (cross4);

	window.draw (F1);
	window.draw (F2);
}
