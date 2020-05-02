#include <cmath>
#include <SFML/Graphics.hpp>
#include "SelbaWard.hpp"

class hyperbola
{
public:

	hyperbola (float a, float b, float scale = 100.f, float offset_x = 400.f, float offset_y = 300.f, float range = 300.f) :
		range_ (range),
		first (range),
		second (range),
		a_ (a),
		b_ (b),
		offset_x_ (offset_x),
		offset_y_ (offset_y),
		scale_ (scale)
	{
	}

	void update ()
	{
		first.removeVertices (0, range_);
		second.removeVertices (0, range_);

		for (float x = a_ + range_ / scale_; x > a_; x -= 0.01)
		{
			first.addVertex (sf::Vector2f (offset_x_ + x * scale_, offset_y_ + scale_ * sqrtf (((x * x) / (a_ * a_) - 1) / (b_ * b_))));
			second.addVertex (sf::Vector2f (offset_x_ - x * scale_, offset_y_ + scale_ * sqrtf (((x * x) / (a_ * a_) - 1) / (b_ * b_))));
		}

		for (float x = a_; x < a_ + range_ / scale_; x += 0.01)
		{
			first.addVertex (sf::Vector2f (offset_x_ + x * scale_, offset_y_ - scale_ * sqrtf (((x * x) / (a_ * a_) - 1) / (b_ * b_))));
			second.addVertex (sf::Vector2f (offset_x_ - x * scale_, offset_y_ - scale_ * sqrtf (((x * x) / (a_ * a_) - 1) / (b_ * b_))));
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
		//shape_.setClosed (true);
	}

	void update ()
	{
		shape_.removeVertices (0, polygons_);

		for (float angle = 0; angle < 3.1415f * 2; angle += 3.1415f * 2.f / polygons_)
			shape_.addVertex (sf::Vector2f (offset_x_ + cosf (angle) * radius_x_, offset_y_ +  sinf (angle) * radius_y_));
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

int main ()
{
	sf::RenderWindow window (sf::VideoMode (800, 600), "Test");

	hyperbola hyp (1, 1);
	hyp.set_color (sf::Color::Blue);
	hyp.set_thickness (5.f);
	hyp.update ();

	ellipse el (200, 100);
	el.set_color (sf::Color::Black);
	el.set_position (sf::Vector2f (400, 300));
	el.set_thickness (5.f);

	el.update ();
	
	while (window.isOpen ())
	{

		window.clear (sf::Color::White);
		sf::Event event;
		while (window.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
				window.close ();


		}



		hyp.render (window);
		el.render (window);
		window.display ();
	}

	return 0;
}

