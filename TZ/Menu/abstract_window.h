#pragma once
#include <SFML/Graphics.hpp>
#include "cursor_handler.h"

/**
 *  @brief Abstract class for window.
 *
 *  Сlass for window with all virtual events methods and draw function.
 */
class abstract_window
{
public:
	abstract_window (); //!< constructor

	virtual void draw (sf::RenderTarget & target) = 0; //!< draw func

	virtual bool contains (const sf::Vector2f & point) = 0; //!< containing checking func

	// Mouse events handlers
	virtual bool mouse_move (sf::Event::MouseMoveEvent event) = 0; //!< mouse move event handler virtual func
	virtual bool mouse_button_pressed (sf::Event::MouseButtonEvent event) = 0; //!< mouse button press event handler virtual func
	virtual bool mouse_button_released (sf::Event::MouseButtonEvent event) = 0; //!< mouse button release event handler virtual func

	//global mouse events handlers
	virtual bool global_mouse_button_pressed (sf::Event::MouseButtonEvent event) = 0; //!< handles button press in windows
	virtual bool global_mouse_button_released (sf::Event::MouseButtonEvent event) = 0; //!< handles button releas in windows

	//Keyboard events handlers
	virtual bool keyboard_key_pressed (sf::Event::KeyEvent event) = 0; //!< keyboard key press event handler virtual func
	virtual bool keyboard_key_released (sf::Event::KeyEvent event) = 0; //!< keyboard key release event handler virtual func 
	virtual bool keyboard_text_entered (sf::Event::KeyEvent event) = 0; //!< keyboard text entered event handler virtual func

	//Other handlers
    virtual void activate (); //!< window activation handler
	virtual void deactivate (); //!< window deactivation handler

	virtual cursor get_cursor () = 0; //!< getter of window cursor

protected:
	bool active_; //!< window state indicator
};

