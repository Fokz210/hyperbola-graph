#pragma once
#include "abstract_window.h"

/**
 * @brief base class for all windows with sprites
 */
class sprite_window :
	public abstract_window
{
public:
	sprite_window (); //!< default constructor

	/**
	 * @brief constructor
	 *
	 * @param sprite an SFML sprite object
	 */
	sprite_window (sf::Sprite sprite);

    /**
     * @brief getter for sprite.
     *
     * @return the sprite
     */
    sf::Sprite & get_sprite ();

    /**
     * @brief overload of draw func.
     *
     * Function that draws sprite.
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

    virtual cursor get_cursor () override; //!< function that returns the cursor, which needed to display on this window

protected:
    sf::Sprite sprite_;
};

