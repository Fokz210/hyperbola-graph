#pragma once
#include "sprite_window.h"


/**
 * @brief a button with an image.
 *
 * Template type T is used to store the lambda type.
 *
 * Usage:
 * @code
 *     ...
 *     bool param;
 *     auto lambda = [&]()
 *     {
 *         param = true;
 *     };
 *     sprite_button<decltype (lambda)> button (<...>, lambda);
 *     ...
 * @endcode
 */
template <class T>
class sprite_button :
	public sprite_window
{
public:
	sprite_button (); //!< default constructor

    /**
     * @brief constructor
     * 
     * Inits all members
     *
     * @param sprite an SFML sprite object
     * @param lamda a func that runs on click
     */
    sprite_button (sf::Sprite & sprite, T lambda);

    void set_lambda (T lambda); //!< setter for lambda func
    
    virtual bool mouse_button_pressed (sf::Event::MouseButtonEvent event) override; //!< handler for mouse button press event

    virtual cursor get_cursor () override; //!< function that returns the cursor, which needed to display on this window

protected:
    T lambda_;
};

template<class T>
inline sprite_button<T>::sprite_button () :
    sprite_window ()
{
}

template<class T>
inline sprite_button<T>::sprite_button (sf::Sprite & sprite, T lambda) :
    sprite_window (sprite),
    lambda_ (lambda)
{
}

template<class T>
inline void sprite_button<T>::set_lambda (T lambda) 
{
    lambda_ = lambda;
}

template<class T>
inline bool sprite_button<T>::mouse_button_pressed (sf::Event::MouseButtonEvent event) 
{
    lambda_ ();

    return true;
}

template<class T>
inline cursor sprite_button<T>::get_cursor ()
{
    return cursor (cursor::TYPE::HAND);
}
