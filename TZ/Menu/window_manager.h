#pragma once
#include <vector>
#include "abstract_window.h"

/**
 * @brief manager for all windows
 *
 * This class is created for managing windows, drawing them and handling events.
 */
class window_manager
{
public:
    window_manager (); //!< constructor

    /**
     * @brief constructor with already initialized array of abstract_window class pointers
     *
     * Absolutly useless if windows pointer array is empty.
     *
     * @param windows array with loaded window ptrs
     */
    window_manager (std::vector<abstract_window *> windows);

    /**
     * @brief pushing window ptr to the array.
     *
     * @param window pointer to the window class
     * @return vector iterator to your pointer. Save it to be able to remove this pointer in the future (see remove_window)
     *
     * @see remove_window
     */
    std::vector<abstract_window *>::iterator add_window (abstract_window * window);

    /**
     * @brief removing window ptr from the array
     * 
     * @param iterator vector iterator for the array member you want to remove.
     *
     * @see add_window
     */
    void remove_window (std::vector<abstract_window *>::iterator iterator);

    /**
     * @brief render function
     *
     * This function is rendering all of your windows. Expected to be used once per iteration.
     * Function does not clear the canvas!!!
     *
     * @param target reference to the window or other render target.
     */
    void draw_windows (sf::RenderTarget & target);

    /**
     * @brief event handling function
     *
     * This function handles one event, translating this event for all event handling window members. 
     * Expected to be used int the event poll cycle (after handling system events).
     *
     * @param event an event you want to handle.
     */
    bool handle_event (const sf::Event & event);

    /**
     * @brief updates system cursor
     *
     * @param event a mouse move event
     * @param handle a window handle
     */
    void update_cursor (const sf::Event::MouseMoveEvent & event, const sf::WindowHandle & handle);

protected:
    std::vector<abstract_window *> windows_; //!< array of abstract_window class pointers
    abstract_window * active_;               //!< focused window pointer
};

