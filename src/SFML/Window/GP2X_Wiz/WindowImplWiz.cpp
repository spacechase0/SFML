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
myWindow      (0),
myKeyRepeat   (true),

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
myWindow      (0),
myKeyRepeat   (true),

prevMousePos( 0, 0 ),
prevMousePress( false )
{
	for ( std::size_t i = 0; i < sf::Keyboard::KeyCount; ++i )
	{
		prevKeys[ i ] = false;
	}
	
	// Window attributes
	myWidth = 320;
    myHeight = 240;

	// Create window
	myWindow = OS_CreateWindow();
    if (!myWindow)
    {
        Err() << "Failed to create window." << std::endl;
        return;
    }
}


////////////////////////////////////////////////////////////
WindowImplWiz::~WindowImplWiz()
{
}

::OS_Display* WindowImplWiz::GetDisplay() const
{
	return myDisplay;
}

////////////////////////////////////////////////////////////
WindowHandle WindowImplWiz::GetSystemHandle() const
{
    return myWindow;
}


////////////////////////////////////////////////////////////
sf::Event DoKey( sf::priv::WizKeyEquivalents keyAlt, bool* prevKeys )
{
	sf::Keyboard::Key key = static_cast< sf::Keyboard::Key >( keyAlt );
	
	sf::Event event;
	event.Type = sf::Event::Count;
	event.Key.Code = key;
	
	bool pressed = sf::Keyboard::IsKeyPressed( key );
	if ( pressed and !prevKeys[ key ] )
	{
		event.Type = sf::Event::KeyPressed;
	}
	else if ( !pressed and prevKeys[ key ] )
	{
		event.Type = sf::Event::KeyReleased;
	}
	
	prevKeys[ key ] = pressed;
	return event;
}

sf::Event DoMouseButton( bool& prevMousePress )
{
	sf::Event event;
	event.Type = sf::Event::Count;
	event.MouseButton.Button = sf::Mouse::Left;
	event.MouseButton.X = sf::Mouse::GetPosition().x;
	event.MouseButton.Y = sf::Mouse::GetPosition().y;
	
	bool pressed = sf::Mouse::IsButtonPressed( sf::Mouse::Left );
	if ( pressed and !prevMousePress )
	{
		event.Type = sf::Event::MouseButtonPressed;
	}
	else if ( !pressed and prevMousePress )
	{
		event.Type = sf::Event::MouseButtonReleased;
	}
	
	prevMousePress = pressed;
	return event;
}

sf::Event DoMousePosition( sf::Vector2i& prevMousePos )
{
	sf::Event event;
	event.Type = sf::Event::Count;
	
	sf::Vector2i mousePos = sf::Mouse::GetPosition();
	if ( mousePos != prevMousePos )
	{
		event.Type = sf::Event::MouseMoved;
		event.MouseMove.X = mousePos.x;
		event.MouseMove.Y = mousePos.y;
	}
	
	prevMousePos = mousePos;
	return event;
}

void WindowImplWiz::ProcessEvents()
{
    inputImpl.Update();
    
    sf::Event events[ 16 ];
	events[ 0  ] = DoKey( LEFT_SHOULDER_E, prevKeys );
	events[ 1  ] = DoKey( RIGHT_SHOULDER_E, prevKeys );
	events[ 2  ] = DoKey( UP_E, prevKeys );
	events[ 3  ] = DoKey( LEFT_E, prevKeys );
	events[ 4  ] = DoKey( DOWN_E, prevKeys );
	events[ 5  ] = DoKey( RIGHT_E, prevKeys );
	events[ 6  ] = DoKey( BUTTON_Y_E, prevKeys );
	events[ 7  ] = DoKey( BUTTON_A_E, prevKeys );
	events[ 8  ] = DoKey( BUTTON_X_E, prevKeys );
	events[ 9  ] = DoKey( BUTTON_B_E, prevKeys );
	events[ 10 ] = DoKey( VOLUME_UP_E, prevKeys );
	events[ 11 ] = DoKey( VOLUME_DOWN_E, prevKeys );
	events[ 12 ] = DoKey( MENU_E, prevKeys );
	events[ 13 ] = DoKey( SELECT_E, prevKeys );
	events[ 14 ] = DoMouseButton( prevMousePress );
	events[ 15 ] = DoMousePosition( prevMousePos );
	
	for ( std::size_t i = 0; i < 16; ++i )
	{
		if ( events[ i ].Type != sf::Event::Count )
		{
			PushEvent( events[ i ] );
		}
	}
}


////////////////////////////////////////////////////////////
void WindowImplWiz::ShowMouseCursor(bool show)
{
	// No cursor
}


////////////////////////////////////////////////////////////
void WindowImplWiz::SetPosition(int x, int y)
{
    // Can't be moved
}


////////////////////////////////////////////////////////////
void WindowImplWiz::SetSize(unsigned int width, unsigned int height)
{
	// Same size all the time
}


////////////////////////////////////////////////////////////
void WindowImplWiz::SetTitle(const std::string& title)
{
	// Doesn't have a title
}


////////////////////////////////////////////////////////////
void WindowImplWiz::Show(bool show)
{
    // Only one window can exist, so this doesn't matter
}


////////////////////////////////////////////////////////////
void WindowImplWiz::EnableKeyRepeat(bool enabled)
{
    myKeyRepeat = enabled;
}


////////////////////////////////////////////////////////////
void WindowImplWiz::SetIcon(unsigned int width, unsigned int height, const Uint8* pixels)
{
    // No icons
}

} // namespace priv

} // namespace sf
