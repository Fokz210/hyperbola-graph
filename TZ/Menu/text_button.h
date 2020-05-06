#pragma once
#include "rectangular_window.h"

/**
 * @brief a button with a text on it.
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
 *     rectangular_button<decltype (lambda)> button (<...>, lambda);
 *     ...
 * @endcode
 */
template <class T> 
class text_button :
	public rectangular_window
{
public:
    /**
     * @brief constructor for button
     *
     * Inializes all members.
     *
     * @param x x-coord of upper left corner
     * @param y x-coord of upper left corner
     * @param width width of the button
     * @param height height of the button
     * @param fill_color color of the button
     * @param text_color color of the text
     * @param text text string
     * @param font text font
     * @param labmda function that runs when button is pressed
     */
    text_button (float x, float y, float width, float height, sf::Color fill_color, sf::Color text_color, sf::String text, sf::Font font, T lambda);

    /**
     * @brief simpler constructor
     *
     * @param shape shape SFML class
     * @param text text SFML class
     */
    text_button (sf::RectangleShape shape, sf::Text text, T lambda);

    /**
     * @brief text struct getter
     *
     * @return text struct
     */
    sf::Text & get_text ();
    
    /**
     * @brief text struct setter
     *
     * @param text text struct
     */
    void set_text (const sf::Text & text);

    virtual bool mouse_button_released(sf::Event::MouseButtonEvent event) override; //!< mouse button press event handler virtual func

    virtual void draw (sf::RenderTarget & target) override; //!< drawing func

    virtual cursor get_cursor () override; //!< function that returns the cursor, which needed to display on this window

protected:
    sf::Text text_; //!< SFML text class
    T lambda_;      //!< lambda variable
};

template<class T>
inline text_button<T>::text_button (float x, float y, float width, float height, sf::Color fill_color, sf::Color text_color, sf::String text, sf::Font font, T lambda) :
    rectangular_window (x, y, width, height, fill_color),
    text_ (),
    lambda_ (lambda)
{
    text_.setString (text);
    text_.setFillColor (text_color);
    text_.setFont (font);
    text_.setOrigin (text_.getLocalBounds ().width / 2, text_.getLocalBounds ().width / 2);
    text_.setPosition (shape_.getSize ().x + shape_.getLocalBounds ().width / 2, shape_.getSize ().y + shape_.getLocalBounds ().height / 2);
}

template<class T>
inline text_button<T>::text_button (sf::RectangleShape shape, sf::Text text, T lambda) :
    rectangular_window (shape),
    text_ (text),
    lambda_ (lambda)
{
}

template<class T>
inline sf::Text & text_button<T>::get_text ()
{
    return text_;
}

template<class T>
inline void text_button<T>::set_text (const sf::Text & text)
{
    text_ = text;
}

template<class T>
inline bool text_button<T>::mouse_button_released (sf::Event::MouseButtonEvent event)
{
    lambda_ ();

    return true;
}

template<class T>
inline void text_button<T>::draw (sf::RenderTarget & target)
{
    rectangular_window::draw (target);
    //target.draw (text_);
}

template<class T>
inline cursor text_button<T>::get_cursor ()
{
    return cursor (cursor::TYPE::HAND);
}
