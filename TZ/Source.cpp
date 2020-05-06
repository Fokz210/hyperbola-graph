#include <cmath>
#include <cstdio>
#include <SFML/Graphics.hpp>
#include "SelbaWard.hpp"
#include "horisontal_slider.h"
#include "vertical_slider.h"
#include "Menu/Menu.h"

#define sqr(a)  ((a) * (a))

const int WINDOW_WIDTH = 1366;
const int WINDOW_HEIGHT = 768;

class hyperbola
{
public:

	hyperbola (float a, float b, float scale = 1.f, float offset_x = 400.f, float offset_y = 300.f, float range = 200.f) :
		range_ (range),
		first (range * 10),
		second (range * 10),
		a_ (a),
		b_ (b),
		offset_x_ (offset_x),
		offset_y_ (offset_y),
		scale_ (scale)
	{
	}

	void update ()
	{

		int i = 0;
		for (float x = a_ + range_ / scale_; x > a_; x -= 1 / scale_)
		{
			float sqrt = sqrtf (((x * x) / (a_ * a_) - 1) * (b_ * b_));

			first[i] = sf::Vector2f (offset_x_ + x * scale_, offset_y_ + scale_ * sqrt);
			second[i] = sf::Vector2f (offset_x_ - x * scale_, offset_y_ + scale_ * sqrt);

			i++;
		}

		for (float x = a_; x < a_ + range_ / scale_; x += 1 / scale_)
		{
			float sqrt = sqrtf (((x * x) / (a_ * a_) - 1) * (b_ * b_));

			first[i] = sf::Vector2f (offset_x_ + x * scale_, offset_y_ - scale_ * sqrt);
			second[i] = sf::Vector2f (offset_x_ - x * scale_, offset_y_ - scale_ * sqrt);

			i++;
		}

		first.update ();
		second.update ();
	}

	void set_range (float range) { range_ = range; }
	void set_a (float a) { a_ = a; }
	void set_b (float b) { b_ = b; }
	void set_offset_x (float offset_x) { offset_x_ = offset_x; }
	void set_offset_y (float offset_y) { offset_y_ = offset_y; }
	void set_scale (float scale) { scale_ = scale; }
	void set_position (sf::Vector2f position) { offset_x_ = position.x; offset_y_ = position.y; }
	void set_thickness (float thickness) { first.setThickness (thickness); second.setThickness (thickness); }
	void set_color (sf::Color color) { first.setColor (color); second.setColor (color); }

	float get_range () { return range_; }
	float get_a () { return a_; }
	float get_b () { return b_; }
	float get_offset_x () { return offset_x_; }
	float get_offset_y () { return offset_y_; }
	float get_scale () { return scale_; }
	float get_thickness () { return first.getThickness (); }
	sf::Color get_color () { return first.getColor (); }
	sf::Vector2f get_position () { return { offset_x_, offset_y_ }; }

	void render (sf::RenderTarget & target)
	{
		target.draw (first);
		target.draw (second);
	}

protected:
	float range_;
	sw::Spline first, second;
	float a_, b_;
	float offset_x_, offset_y_;
	float scale_;
};

class ellipse
{
public:
	ellipse (float radius_x, float radius_y, float offset_x = 400.f, float offset_y = 300.f, float polygons = 100.f) :
		polygons_ (polygons),
		radius_x_ (radius_x),
		radius_y_ (radius_y),
		offset_x_ (offset_x),
		offset_y_ (offset_y),
		shape_ (polygons)
	{
		shape_.setClosed (true);
	}

	void update ()
	{
		int i = 0;
		for (float angle = 0; angle < 3.1415f * 2 && i < 100; angle += 3.1415f * 2.f / polygons_)
		{
			shape_[i++] = sf::Vector2f (offset_x_ + cosf (angle) * radius_x_, offset_y_ + sinf (angle) * radius_y_);
		}
		shape_.update ();
	}

	void render (sf::RenderTarget & target)
	{
		target.draw (shape_);
	}

	void set_radius_x (float radius_x) { radius_x_ = radius_x; }
	void set_radius_y (float radius_y) { radius_y_ = radius_y; }
	void set_position (sf::Vector2f position) { offset_x_ = position.x; offset_y_ = position.y; }
	void set_color (sf::Color color) { shape_.setColor (color); }
	void set_thickness (float thickness) { shape_.setThickness (thickness); }

	float get_radius_x () { return radius_x_; }
	float get_radius_y () { return radius_y_; }
	sf::Vector2f get_position () { return sf::Vector2f (offset_x_, offset_y_); }
	sf::Color get_color () { return shape_.getColor (); }
	float get_thickness () { return shape_.getThickness (); }

protected:
	float polygons_;
	float radius_x_, radius_y_;
	float offset_x_, offset_y_;
	sw::Spline shape_;
};

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

int main ()
{
	float dot_radius = 5.f;
	float thickness = 2.f;

	sf::RenderWindow window (sf::VideoMode (WINDOW_WIDTH, WINDOW_HEIGHT), "Test", sf::Style::Titlebar | sf::Style::Close);

	hyperbola hyp (1, 1, 1, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2);
	hyp.set_color (sf::Color::Black);
	hyp.set_thickness (thickness);

	ellipse el (200, 200);
	el.set_color (sf::Color (25, 118, 194));
	el.set_position (sf::Vector2f (WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	el.set_thickness (thickness);

	float A_el = 100;
	float B_el = 100;
	float C = sqrtf (sqr (A_el) - sqr (B_el));

	float A_hyp = sqr (C) / A_el;
	float B_hyp = sqrtf (sqr (C) - sqr (A_hyp));
	
	float dot_x = ((A_el * A_hyp) * sqrtf (sqr (B_el) + sqr (B_hyp))) / sqrtf (sqr (A_el * B_hyp) + sqr (B_el * A_hyp));
	float dot_y = (B_el * sqrtf (sqr (A_el) - sqr (dot_x))) / A_el;

	float r_circ = sqrt (sqr (dot_x) + sqr (dot_y));

	sf::CircleShape shape (r_circ);
	shape.setOutlineColor (sf::Color (235, 122, 40));
	shape.setFillColor (sf::Color::Transparent);
	shape.setOutlineThickness (thickness);

	shape.setPointCount (100);

	window.setFramerateLimit (60);

	sf::CircleShape cross1, cross2, cross3, cross4;

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

	float E_el = 0;
	float E_hyp = 0;
	float S_el = 0;
	float S_c = 0;

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

	sf::RectangleShape X_axis, Y_axis;
	X_axis.setFillColor (sf::Color (214, 214, 214));
	Y_axis.setFillColor (sf::Color (214, 214, 214));

	float slider_x = WINDOW_WIDTH / 2 + A_el;
	sf::RectangleShape slider_shape;
	slider_shape.setFillColor (sf::Color::Red);
	slider_shape.setSize (sf::Vector2f (50.f, 50.f));
	horisontal_slider h_slider (slider_shape, slider_x, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2 + 5, WINDOW_WIDTH);

	float slider_y = WINDOW_HEIGHT / 2 + B_el;
	vertical_slider v_slider (slider_shape, WINDOW_WIDTH / 2, slider_y, WINDOW_HEIGHT / 2 + 5, WINDOW_HEIGHT);

	float slider_x2 = WINDOW_WIDTH / 2 - A_el;
	horisontal_slider h_slider2 (slider_shape, slider_x2, WINDOW_HEIGHT / 2, 0, WINDOW_WIDTH / 2 - 5);

	float slider_y2 = WINDOW_HEIGHT / 2 - B_el;
	vertical_slider v_slider2 (slider_shape, WINDOW_WIDTH / 2, slider_y2, 0, WINDOW_HEIGHT / 2 - 5);

	window_manager w_manager;
	w_manager.add_window (&h_slider);
	w_manager.add_window (&v_slider);
	w_manager.add_window (&v_slider2);
	w_manager.add_window (&h_slider2);

	float slider_x_prev = slider_x;
	float slider_y_prev = slider_y;
	float slider_x2_prev = slider_x2;
	float slider_y2_prev = slider_y2;

	sf::CircleShape F1;
	F1.setFillColor (sf::Color (0, 200, 0));
	F1.setRadius (thickness * 2);

	sf::CircleShape F2 (F1);

	while (window.isOpen ())
	{

		window.clear (sf::Color::White);

		slider_x_prev = slider_x;
		slider_y_prev = slider_y;
		slider_x2_prev = slider_x2;
		slider_y2_prev = slider_y2;

		sf::Event event;
		while (window.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
				window.close ();

			if (event.type == sf::Event::MouseMoved)
				w_manager.update_cursor (event.mouseMove, window.getSystemHandle ());

			w_manager.handle_event (event);
		}

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

		shape.setRadius (r_circ - thickness);
		shape.setPosition (sf::Vector2f (WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
		shape.setOrigin (sf::Vector2f (shape.getLocalBounds ().width / 2, shape.getLocalBounds ().height / 2));

		E_el = C / A_el;
		E_hyp = C / A_hyp;
		S_el = 2 * 2.1415 * sqrtf ((sqr (A_el) + sqr (B_el)) / 2);

		sprintf_s <32> (buffer, "E (el) = %.2f", E_el);
		E_el_text.setString (buffer);

		sprintf_s <32> (buffer, "S (el) = %.2f", S_el);
		S_el_text.setString (buffer);

		sprintf_s <32> (buffer, "E (hyp) = %.2f", E_hyp);
		E_hyp_text.setString (buffer);

		sprintf_s <32> (buffer, "R (circ) = %.2f", r_circ);
		R_c_text.setString (buffer);

		sprintf_s <32> (buffer, "S (circ) = %.2f", 2 * 3.1415 * r_circ);
		S_c_text.setString (buffer);

		sprintf_s <32> (buffer, "A (el) = %.2f", A_el);
		A_el_text.setString (buffer);

		sprintf_s <32> (buffer, "B (el) = %.2f", B_el);
		B_el_text.setString (buffer);

		X_axis.setSize (sf::Vector2f (A_el * 2, thickness));
		Y_axis.setSize (sf::Vector2f (thickness, B_el * 2));

		X_axis.setPosition (sf::Vector2f (WINDOW_WIDTH / 2 - A_el, WINDOW_HEIGHT / 2 - thickness / 2));
		Y_axis.setPosition (sf::Vector2f (WINDOW_WIDTH / 2 - thickness / 2, WINDOW_HEIGHT / 2 - B_el));

		F1.setPosition (WINDOW_WIDTH / 2 - C - thickness * 2, WINDOW_HEIGHT / 2 - thickness * 2);
		F2.setPosition (WINDOW_WIDTH / 2 + C - thickness * 2, WINDOW_HEIGHT / 2 - thickness * 2);

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

		window.draw (E_el_text);
		window.draw (S_el_text);
		window.draw (E_hyp_text);
		window.draw (R_c_text);
		window.draw (S_c_text);
		window.draw (A_el_text);
		window.draw (B_el_text);

		//w_manager.draw_windows (window);

		window.display ();
	}

	return 0;
}

