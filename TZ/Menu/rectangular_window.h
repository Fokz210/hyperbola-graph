#pragma once
#include "abstract_window.h"

/**
 * @brief A window, based on rectangular shape.
 *
 * A child of abstract_window class.
 */
class rectangular_window :
	public abstract_window
{
public:
    /**
     * @brief basic default constructor.
     */
    rectangular_window ();
    
    /**
     * @brief constructor from shape class
     *
     * @param shape SFML shape class initializer
     */
    rectangular_window (const sf::RectangleShape & shape);

    /**
     * @brief constructor.
     *
     * @param x      x-coord of upper left corner of the window
     * @param y      y-coord of upper left corner of the window
     * @param width  width of the window
     * @param height height of the window
     * @param color  the color of the window
     */
    rectangular_window (float x, float y, float width, float height, sf::Color color);

    /**
     * @brief getter for shape struct.
     * 
     * @return The shape ref.
     */
    sf::RectangleShape & get_shape ();

    /**
     * @brief setter for shape struct.
     * 
     * @param a shape struct to set.
     */
    void set_shape (const sf::RectangleShape & shape);

    /**
     * @brief overload of draw func.
     * 
     * Function that draws rectangle shape.
     * 
     * @param target render target.
     */
    virtual void draw (sf::RenderTarget & target) override;

    /**
     * @brief contain checking function for rect
     *
     * This function is checking if the rectangle  of the window.
     *
     * @param point coordinates of the point to check
     * @return true if contains
     */
    virtual bool contains (const sf::Vector2f & point) override;

    // Mouse events handlers
    virtual bool mouse_move (sf::Event::MouseMoveEvent event) override; //!< mouse move event handler overload
    virtual bool mouse_button_pressed (sf::Event::MouseButtonEvent event) override; //!< mouse button press event handler overload
    virtual bool mouse_button_released (sf::Event::MouseButtonEvent event) override; //!< mouse button release event handler overload

    //Keyboard events handlers
    virtual bool keyboard_key_pressed (sf::Event::KeyEvent event) override; //!< keyboard key press event handler overload
    virtual bool keyboard_key_released (sf::Event::KeyEvent event) override; //!< keyboard key release event handler overload 
    virtual bool keyboard_text_entered (sf::Event::KeyEvent event) override; //!< keyboard text entered event handler overload

    virtual bool global_mouse_button_pressed (sf::Event::MouseButtonEvent event) override; //!< handles button press in windows
    virtual bool global_mouse_button_released (sf::Event::MouseButtonEvent event) override; //!< handles button releas in windows

    virtual cursor get_cursor () override; //!< function that returns the cursor, which needed to display on this window

protected:
    sf::RectangleShape shape_; //!< an SFML rectangle shape struct
};

