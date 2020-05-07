#pragma once

#include "SelbaWard.hpp"
#include "constants.h"

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

	void render (sf::RenderTarget& target)
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
