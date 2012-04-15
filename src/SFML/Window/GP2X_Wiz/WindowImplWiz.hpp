////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_WINDOWIMPLWIZ_HPP
#define SFML_WINDOWIMPLWIZ_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window/Event.hpp>
#include <SFML/Window/WindowImpl.hpp>
#include <Panel/fake_os.h>


namespace sf
{
namespace priv
{

////////////////////////////////////////////////////////////
/// \brief GP2X Wiz implementation of WindowImpl
///
////////////////////////////////////////////////////////////
class WindowImplWiz : public WindowImpl
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Construct the window implementation from an existing control
    ///
    /// \param handle Platform-specific handle of the control
    ///
    ////////////////////////////////////////////////////////////
    WindowImplWiz(WindowHandle handle);

    ////////////////////////////////////////////////////////////
    /// \brief Create the window implementation
    ///
    /// \param mode  Video mode to use
    /// \param title Title of the window
    /// \param style Window style (resizable, fixed, or fullscren)
    ///
    ////////////////////////////////////////////////////////////
    WindowImplWiz(VideoMode mode, const std::string& title, unsigned long style);

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    ~WindowImplWiz();

    ////////////////////////////////////////////////////////////
    /// \brief Get the display used by the window
    ///
    /// This functions is meant to be used internally by WizGlContext.
    ///
    /// \return Pointer to the OS_Diplay of the window
    ///
    ////////////////////////////////////////////////////////////
    ::OS_Display* getDisplay() const;

private :

    ////////////////////////////////////////////////////////////
    /// \brief Get the OS-specific handle of the window
    ///
    /// \return Handle of the window
    ///
    ////////////////////////////////////////////////////////////
    virtual WindowHandle getSystemHandle() const;

    ////////////////////////////////////////////////////////////
    /// \brief Process incoming events from the operating system
    ///
    ////////////////////////////////////////////////////////////
    virtual void processEvents();

    ////////////////////////////////////////////////////////////
    /// \brief Show or hide the mouse cursor
    ///
    /// \param show True to show, false to hide
    ///
    ////////////////////////////////////////////////////////////
    virtual void setMouseCursorVisible(bool show);

    ////////////////////////////////////////////////////////////
    /// \brief Get the position of the window
    ///
    /// \return Position of the window, in pixels
    ///
    ////////////////////////////////////////////////////////////
    virtual Vector2i getPosition() const;

    ////////////////////////////////////////////////////////////
    /// \brief Change the position of the window on screen
    ///
    /// \param position New position of the window, in pixels
    ///
    ////////////////////////////////////////////////////////////
    virtual void setPosition(const Vector2i& position);

    ////////////////////////////////////////////////////////////
    /// \brief Get the client size of the window
    ///
    /// \return Size of the window, in pixels
    ///
    ////////////////////////////////////////////////////////////
    virtual Vector2u getSize() const;

    ////////////////////////////////////////////////////////////
    /// \brief Change the size of the rendering region of the window
    ///
    /// \param size New size, in pixels
    ///
    ////////////////////////////////////////////////////////////
    virtual void setSize(const Vector2u& size);

    ////////////////////////////////////////////////////////////
    /// \brief Change the title of the window
    ///
    /// \param title New title
    ///
    ////////////////////////////////////////////////////////////
    virtual void setTitle(const std::string& title);

    ////////////////////////////////////////////////////////////
    /// \brief Show or hide the window
    ///
    /// \param show True to show, false to hide
    ///
    ////////////////////////////////////////////////////////////
    virtual void setVisible(bool show);

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable automatic key-repeat
    ///
    /// \param enabled True to enable, false to disable
    ///
    ////////////////////////////////////////////////////////////
    virtual void setKeyRepeatEnabled(bool enabled);

    ////////////////////////////////////////////////////////////
    /// \brief Change the window's icon
    ///
    /// \param width  Icon's width, in pixels
    /// \param height Icon's height, in pixels
    /// \param pixels Pointer to the pixels in memory, format must be RGBA 32 bits
    ///
    ////////////////////////////////////////////////////////////
    virtual void setIcon(unsigned int width, unsigned int height, const Uint8* pixels);

    ////////////////////////////////////////////////////////////
    /// \brief Switch to fullscreen mode
    ///
    /// \param Mode video mode to switch to
    ///
    ////////////////////////////////////////////////////////////
    void switchToFullscreen(const VideoMode& mode);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    ::OS_Window   m_window;  ///< Window
    ::OS_Display* m_display; ///< Display
    int           m_screen;     ///< Screen identifier
    bool          m_keyRepeat;  ///< Is the KeyRepeat feature enabled ?
    
    sf::Vector2i prevMousePos; ///< The previous mouse position.
    bool prevMousePress;       ///< The previous mouse pressed state.
    bool prevKeys[ sf::Keyboard::KeyCount ]; ///< The previous key states.
};

} // namespace priv

} // namespace sf


#endif // SFML_WINDOWIMPLWIZ_HPP
