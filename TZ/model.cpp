#include "model.h"

#ifndef sqr
#define sqr(a)  ((a) * (a))
#endif 

model::model (window_manager & manager, float window_width, float window_height) :
	m_window_width (window_width),
	m_window_height (window_height),
	m_manager (manager),
	hyp (1, 1, 1, m_window_width / 2, m_window_height / 2, m_window_width / 2),
	el (200, 200),
	shape (),
	cross1 (),
	cross2 (),
	cross3 (),
	cross4 (),
	h_slider (sf::RectangleShape (), slider_x, m_window_height / 2, m_window_width / 2 + 5, m_window_width),
	h_slider2 (sf::RectangleShape (), slider_x2, m_window_height / 2, 0, m_window_width / 2 - 5),
	v_slider (sf::RectangleShape (), m_window_width / 2, slider_y, m_window_height / 2 + 5, m_window_height),
	v_slider2 (sf::RectangleShape (), m_window_width / 2, slider_y2, 0, m_window_height / 2 - 5),
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
	dot_radius (5.f),
	slider_iterators (),
	m_hidden (false),
	Phi (),
	angle (2)
{
}

void model::init (int A_ellipse, int B_ellipse, float thickness)
{
	m_thickness = thickness;

	angle.setColor (sf::Color::Black);
	angle.setThickness (thickness);

	angle[0] = sf::Vector2f (m_window_width / 2, m_window_height / 2);
	
	hyp.set_color (sf::Color::Black);
	hyp.set_thickness (thickness);

	el.set_color (sf::Color (25, 118, 194));
	el.set_position (sf::Vector2f (m_window_width / 2, m_window_height / 2));
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

	slider_x = m_window_width / 2 + A_el;
	sf::RectangleShape slider_shape;
	slider_shape.setFillColor (sf::Color::Transparent);
	slider_shape.setSize (sf::Vector2f (50.f, 50.f));

	slider_shape.setOrigin (25, 25);
	
	h_slider.get_shape () = slider_shape;
	h_slider.get_shape ().setPosition (slider_x, m_window_height / 2);

	slider_y = m_window_height / 2 + B_el;
	v_slider.get_shape () = slider_shape;
	v_slider.get_shape ().setPosition (m_window_width / 2, slider_y);

    slider_x2 = m_window_width / 2 - A_el;
	h_slider2.get_shape () = slider_shape;
	h_slider2.get_shape ().setPosition (slider_x2, m_window_height / 2);

	slider_y2 = m_window_height / 2 - B_el;
	v_slider2.get_shape () = slider_shape;
	v_slider2.get_shape ().setPosition (m_window_width / 2, slider_y2);

	F1.setFillColor (sf::Color (0, 200, 0));
	F1.setRadius (thickness * 2);

	F2.setFillColor (sf::Color (0, 200, 0));
	F2.setRadius (thickness * 2);

	shape.setPointCount (100);

    slider_x_prev = slider_x;
	slider_y_prev = slider_y;
	slider_x2_prev = slider_x2;
	slider_y2_prev = slider_y2;

	slider_iterators.push_back(m_manager.add_window (&h_slider));
	slider_iterators.push_back(m_manager.add_window (&v_slider));
	slider_iterators.push_back(m_manager.add_window (&h_slider2));
	slider_iterators.push_back(m_manager.add_window (&v_slider2));

	v_slider.ymax_ = m_window_height / 2 + A_el;
	v_slider2.ymin_ = m_window_height / 2 - A_el;
	h_slider.xmin_ = m_window_width / 2 + B_el;
	h_slider2.xmax_ = m_window_width / 2 - B_el;
}

void model::update ()
{
#ifdef MY_DEBUG
	printf ("[INFO] slider_x = %f\n", slider_x);
	printf ("[INFO] slider_y = %f\n", slider_y);
	printf ("[INFO] slider_x2 = %f\n", slider_x2);
	printf ("[INFO] slider_y2 = %f\n", slider_y2);
	printf ("[INFO] slider_x_prev = %f\n", slider_x_prev);
	printf ("[INFO] slider_y_prev = %f\n", slider_y_prev);
	printf ("[INFO] slider_x2_prev = %f\n", slider_x2_prev);
	printf ("[INFO] slider_y2_prev = %f\n", slider_y2_prev);
#endif // MY_DEBUG

	if (B_el > A_el)
	{
		B_el = A_el;
		slider_y = m_window_height / 2 + B_el * m_scale;
		slider_y2 = m_window_height / 2 - B_el * m_scale;
	}

	if (A_el < B_el)
	{
		A_el = B_el;
		slider_x = m_window_width / 2 + A_el * m_scale;
		slider_x2 = m_window_width / 2 - A_el * m_scale;
	}

	if (slider_x != slider_x_prev)
	{
		A_el = (slider_x - m_window_width / 2) / m_scale;
		
		slider_x2 = m_window_width / 2 - A_el * m_scale;
		h_slider2.get_shape ().setPosition (m_window_width / 2 - A_el * m_scale, m_window_height / 2);

		v_slider.ymax_ = m_window_height / 2 + A_el * m_scale;
		v_slider2.ymin_ = m_window_height / 2 - A_el * m_scale;
	}

	if (slider_x2 != slider_x2_prev)
	{
		A_el = (m_window_width / 2 - slider_x2) / m_scale;
		
		slider_x = m_window_width / 2 + A_el * m_scale;
		h_slider.get_shape ().setPosition (m_window_width / 2 + A_el * m_scale, m_window_height / 2);

		v_slider.ymax_ = m_window_height / 2 + A_el * m_scale;
		v_slider2.ymin_ = m_window_height / 2 - A_el * m_scale;
	}

	if (slider_y != slider_y_prev)
	{
		B_el = (slider_y - m_window_height / 2) / m_scale;
		slider_y2 = m_window_height / 2 - B_el * m_scale;
		v_slider2.get_shape ().setPosition (m_window_width / 2, m_window_height / 2 - B_el * m_scale);

		h_slider.xmin_ = m_window_width / 2 + B_el * m_scale;
		h_slider2.xmax_ = m_window_width / 2 - B_el * m_scale;
		/*	printf_s ("[INFO] slider_y is changed to %f. changing B_el to %f and slider_y2 to %f.\n", slider_y, B_el, slider_y2);*/
	}

	 if (slider_y2 != slider_y2_prev)
	{
		B_el = (m_window_height / 2 - slider_y2) / m_scale;
		slider_y = m_window_height + B_el * m_scale;
		v_slider.get_shape ().setPosition (m_window_width / 2, m_window_height / 2 + B_el * m_scale);

		h_slider.xmin_ = m_window_width / 2 + B_el * m_scale;
		h_slider2.xmax_ = m_window_width / 2 - B_el * m_scale;
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

	angle[1] = sf::Vector2f (m_window_width / 2 + dot_x * m_scale, m_window_height / 2 - dot_y * m_scale);

	angle.update ();

	Phi = atan2f (dot_x, dot_y);

	r_circ = sqrt (sqr (dot_x) + sqr (dot_y));

	cross1.setPosition (m_window_width / 2 + dot_x * m_scale, m_window_height / 2 + dot_y * m_scale);
	cross2.setPosition (m_window_width / 2 - dot_x * m_scale, m_window_height / 2 + dot_y * m_scale);
	cross3.setPosition (m_window_width / 2 + dot_x * m_scale, m_window_height / 2 - dot_y * m_scale);
	cross4.setPosition (m_window_width / 2 - dot_x * m_scale, m_window_height / 2 - dot_y * m_scale);

	shape.setRadius (r_circ * m_scale - m_thickness);
	shape.setOrigin (sf::Vector2f (shape.getLocalBounds ().width / 2, shape.getLocalBounds ().height / 2));
	shape.setPosition (sf::Vector2f (m_window_width / 2, m_window_height / 2));

	E_el = C / A_el;
	E_hyp = C / A_hyp;
	S_el = 2 * 2.1415 * sqrtf ((sqr (A_el) + sqr (B_el)) / 2);

	X_axis.setSize (sf::Vector2f (A_el * 2 * m_scale, m_thickness));
	Y_axis.setSize (sf::Vector2f (m_thickness, B_el * 2 * m_scale));

	X_axis.setPosition (sf::Vector2f (m_window_width / 2 - A_el * m_scale, m_window_height / 2 - m_thickness / 2));
	Y_axis.setPosition (sf::Vector2f (m_window_width / 2 - m_thickness / 2, m_window_height / 2 - B_el * m_scale));

	F1.setPosition (m_window_width / 2 - C * m_scale - m_thickness * 2, m_window_height / 2 - m_thickness * 2);
	F2.setPosition (m_window_width / 2 + C* m_scale - m_thickness * 2, m_window_height / 2 - m_thickness * 2);

	slider_x_prev = slider_x;
	slider_y_prev = slider_y;
	slider_x2_prev = slider_x2;
	slider_y2_prev = slider_y2;
}

void model::draw (sf::RenderTarget & window)
{
	if (m_hidden)
		return;

	window.draw (angle);

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

void model::update_resolution (float window_width, float window_height)
{
	float w_offset_x = window_width - m_window_width;
	float w_offset_y = window_height - m_window_height;

	m_window_width = window_width;
	m_window_height = window_height;

	angle[0] = sf::Vector2f (m_window_width / 2, m_window_height / 2);

	el.set_position (sf::Vector2f (m_window_width / 2, m_window_height / 2));
	hyp.set_position (sf::Vector2f (m_window_width / 2, m_window_height / 2));
	
	slider_x += w_offset_x / 2;
	slider_x2 += w_offset_x / 2;
	slider_y += w_offset_y / 2;
	slider_y2 += w_offset_y / 2;

	h_slider.get_shape ().setPosition (slider_x, m_window_height / 2);
	v_slider.get_shape ().setPosition (m_window_width / 2, slider_y);
	h_slider2.get_shape ().setPosition (slider_x2, m_window_height / 2);
	v_slider2.get_shape ().setPosition (m_window_width / 2, slider_y2);

	h_slider.xmax_ = m_window_width - 5;
	h_slider.xmin_ = m_window_width / 2 + 5;
	h_slider2.xmax_ = m_window_width / 2 - 5;
	h_slider2.xmin_ = 5;

	v_slider.ymax_ = m_window_height - 5;
	v_slider.ymin_ = m_window_height / 2 + 5;
	v_slider2.ymax_ = m_window_height / 2 - 5;
	v_slider2.ymin_ = 5;

	slider_x_prev = slider_x;
	slider_y_prev = slider_y;
	slider_x2_prev = slider_x2;
	slider_y2_prev = slider_y2;

	v_slider.ymax_ = m_window_height / 2 + A_el * m_scale;
	v_slider2.ymin_ = m_window_height / 2 - A_el * m_scale;
	h_slider.xmin_ = m_window_width / 2 + B_el * m_scale;
	h_slider2.xmax_ = m_window_width / 2 - B_el;
}

void model::lock ()
{
	h_slider.lock ();
	h_slider2.lock ();
	v_slider.lock ();
	v_slider2.lock ();
}

void model::unlock ()
{
	h_slider.unlock ();
	h_slider2.unlock ();
	v_slider.unlock ();
	v_slider2.unlock ();
}

void model::reset (int a, int b)
{
	A_el = a;
	B_el = b;

	slider_x = m_window_width / 2 + A_el;
	slider_y = m_window_height / 2 + B_el;
	slider_x2 = m_window_width / 2 - A_el;
	slider_y2 = m_window_height / 2 - B_el;

	h_slider.get_shape ().setPosition (slider_x, m_window_height / 2);
	v_slider.get_shape ().setPosition (m_window_width / 2, slider_y);
	h_slider2.get_shape ().setPosition (slider_x2, m_window_height / 2);
	v_slider2.get_shape ().setPosition (m_window_width / 2, slider_y2);
}

void model::hide ()
{
	lock ();
	m_hidden = true;
}

void model::show ()
{
	unlock ();
	m_hidden = false;
}

void model::set_scale (float scale)
{
	hyp.set_scale (scale);
	el.set_scale (scale);
	m_scale = scale;

	slider_x = m_window_width / 2 + A_el * m_scale;
	slider_x2 = m_window_width / 2 - A_el * m_scale;
	slider_y = m_window_height / 2 + B_el * m_scale;
	slider_y2 = m_window_height / 2 - B_el * m_scale;

	h_slider.get_shape ().setPosition (slider_x, m_window_height / 2);
	v_slider.get_shape ().setPosition (m_window_width / 2, slider_y);
	h_slider2.get_shape ().setPosition (slider_x2, m_window_height / 2);
	v_slider2.get_shape ().setPosition (m_window_width / 2, slider_y2);
}


