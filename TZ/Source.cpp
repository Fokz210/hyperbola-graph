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
	ellipse (float radius_x, float radius_y) :
		radius_x_ (radius_x),
		radius_y_ (radius_y),
		shape_ ()
	{

	}

	void update ()
	{
		shape_.setRadius (radius_x_);
		shape_.setScale (sf::Vector2f (1, radius_y_ / radius_x_));
	}

protected:
	float radius_x_, radius_y_;
	sf::CircleShape shape_;
};

int main ()
{
	sf::RenderWindow window (sf::VideoMode (800, 600), "Test");

	hyperbola hyp (1, 1);
	hyp.update ();

	while (window.isOpen ())
	{
		sf::Event event;
		while (window.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
				window.close ();


		}



		hyp.render (window);
		window.display ();
	}

	return 0;
}

