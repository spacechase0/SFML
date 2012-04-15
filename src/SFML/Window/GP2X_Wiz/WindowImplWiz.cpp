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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Window/WindowStyle.hpp> // important to be included first (conflict with None)
#include <SFML/Window/GP2X_Wiz/WindowImplWiz.hpp>
#include <SFML/Window/GP2X_Wiz/WizInputImpl.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Err.hpp>

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
WindowImplWiz::WindowImplWiz(WindowHandle handle) :
m_window      (0),
m_keyRepeat   (true),

prevMousePos( 0, 0 ),
prevMousePress( false )
{
	for ( std::size_t i = 0; i < sf::Keyboard::KeyCount; ++i )
	{
		prevKeys[ i ] = false;
	}
	
	#warning Not implemented
}


////////////////////////////////////////////////////////////
WindowImplWiz::WindowImplWiz(VideoMode mode, const std::string& title, unsigned long style) :
m_window      (0),
m_keyRepeat   (true),

prevMousePos( 0, 0 ),
prevMousePress( false )
{
	for ( std::size_t i = 0; i < sf::Keyboard::KeyCount; ++i )
	{
		prevKeys[ i ] = false;
	}

	// Create window
	m_window = OS_CreateWindow();
    if (!m_window)
    {
        err() << "Failed to create window." << std::endl;
        return;
    }
}


////////////////////////////////////////////////////////////
WindowImplWiz::~WindowImplWiz()
{
}

::OS_Display* WindowImplWiz::getDisplay() const
{
	return m_display;
}

////////////////////////////////////////////////////////////
WindowHandle WindowImplWiz::getSystemHandle() const
{
    return m_window;
}


////////////////////////////////////////////////////////////
sf::Event doKey( sf::priv::WizKeyEquivalents keyAlt, bool* prevKeys )
{
	sf::Keyboard::Key key = static_cast< sf::Keyboard::Key >( keyAlt );
	
	sf::Event event;
	event.type = sf::Event::Count;
	event.key.code = key;
	
	bool pressed = sf::Keyboard::isKeyPressed( key );
	if ( pressed and !prevKeys[ key ] )
	{
		event.type = sf::Event::KeyPressed;
	}
	else if ( !pressed and prevKeys[ key ] )
	{
		event.type = sf::Event::KeyReleased;
	}
	
	prevKeys[ key ] = pressed;
	return event;
}

sf::Event doMouseButton( bool& prevMousePress )
{
	sf::Event event;
	event.type = sf::Event::Count;
	event.mouseButton.button = sf::Mouse::Left;
	event.mouseButton.x = sf::Mouse::getPosition().x;
	event.mouseButton.y = sf::Mouse::getPosition().y;
	
	bool pressed = sf::Mouse::isButtonPressed( sf::Mouse::Left );
	if ( pressed and !prevMousePress )
	{
		event.type = sf::Event::MouseButtonPressed;
	}
	else if ( !pressed and prevMousePress )
	{
		event.type = sf::Event::MouseButtonReleased;
	}
	
	prevMousePress = pressed;
	return event;
}

sf::Event doMousePosition( sf::Vector2i& prevMousePos )
{
	sf::Event event;
	event.type = sf::Event::Count;
	
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if ( mousePos != prevMousePos )
	{
		event.type = sf::Event::MouseMoved;
		event.mouseMove.x = mousePos.x;
		event.mouseMove.y = mousePos.y;
	}
	
	prevMousePos = mousePos;
	return event;
}

void WindowImplWiz::processEvents()
{
    inputImpl.update();
    
    sf::Event events[ 16 ];
	events[ 0  ] = doKey( LEFT_SHOULDER_E, prevKeys );
	events[ 1  ] = doKey( RIGHT_SHOULDER_E, prevKeys );
	events[ 2  ] = doKey( UP_E, prevKeys );
	events[ 3  ] = doKey( LEFT_E, prevKeys );
	events[ 4  ] = doKey( DOWN_E, prevKeys );
	events[ 5  ] = doKey( RIGHT_E, prevKeys );
	events[ 6  ] = doKey( BUTTON_Y_E, prevKeys );
	events[ 7  ] = doKey( BUTTON_A_E, prevKeys );
	events[ 8  ] = doKey( BUTTON_X_E, prevKeys );
	events[ 9  ] = doKey( BUTTON_B_E, prevKeys );
	events[ 10 ] = doKey( VOLUME_UP_E, prevKeys );
	events[ 11 ] = doKey( VOLUME_DOWN_E, prevKeys );
	events[ 12 ] = doKey( MENU_E, prevKeys );
	events[ 13 ] = doKey( SELECT_E, prevKeys );
	events[ 14 ] = doMouseButton( prevMousePress );
	events[ 15 ] = doMousePosition( prevMousePos );
	
	for ( std::size_t i = 0; i < 16; ++i )
	{
		if ( events[ i ].type != sf::Event::Count )
		{
			pushEvent( events[ i ] );
		}
	}
}


////////////////////////////////////////////////////////////
void WindowImplWiz::setMouseCursorVisible(bool show)
{
	// No cursor
}


////////////////////////////////////////////////////////////
sf::Vector2i WindowImplWiz::getPosition() const
{
	return sf::Vector2i( 0, 0 );
}


////////////////////////////////////////////////////////////
void WindowImplWiz::setPosition(const Vector2i& position)
{
    // Can't be moved
}


////////////////////////////////////////////////////////////
sf::Vector2u WindowImplWiz::getSize() const
{
	return sf::Vector2u( 320, 240 );
}


////////////////////////////////////////////////////////////
void WindowImplWiz::setSize(const sf::Vector2u& size)
{
	// Same size all the time
}


////////////////////////////////////////////////////////////
void WindowImplWiz::setTitle(const std::string& title)
{
	// Doesn't have a title
}


////////////////////////////////////////////////////////////
void WindowImplWiz::setVisible(bool show)
{
    // Only one window can exist, so this doesn't matter
}


////////////////////////////////////////////////////////////
void WindowImplWiz::setKeyRepeatEnabled(bool enabled)
{
    m_keyRepeat = enabled;
}


////////////////////////////////////////////////////////////
void WindowImplWiz::setIcon(unsigned int width, unsigned int height, const Uint8* pixels)
{
    // No icons
}

} // namespace priv

} // namespace sf
