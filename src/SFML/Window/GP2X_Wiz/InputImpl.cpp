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
#include <SFML/Window/GP2X_Wiz/InputImpl.hpp>
#include <SFML/Window/GP2X_Wiz/WizInputImpl.hpp>
#include <SFML/Window/Window.hpp>

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
bool InputImpl::isKeyPressed(Keyboard::Key key)
{
    sf::Uint32 buttons = getButtons();
    
    // Get the right key
    #define doKey(a) case a ## _E:  return buttons & a;
    switch ( key )
    {
    	doKey( LEFT_SHOULDER );
    	doKey( RIGHT_SHOULDER );
    	
    	doKey( UP );
    	doKey( LEFT );
    	doKey( DOWN );
    	doKey( RIGHT );
    	
    	doKey( BUTTON_Y );
    	doKey( BUTTON_A );
    	doKey( BUTTON_X );
    	doKey( BUTTON_B );
    	
    	doKey( VOLUME_UP );
    	doKey( VOLUME_DOWN );
    	
    	doKey( MENU );
    	doKey( SELECT );
    }
    #undef doKey
    
    return false;
}


////////////////////////////////////////////////////////////
bool InputImpl::isMouseButtonPressed(Mouse::Button button)
{
    return inputImpl.mousePressed;
}


////////////////////////////////////////////////////////////
Vector2i InputImpl::getMousePosition()
{
	// For some reason x=0 is on the right side
    sf::Vector2i pos = inputImpl.mousePos;
    pos.x = static_cast< int >( -( ( pos.x / 1000.f ) * 320 ) + 320 );
    pos.y = static_cast< int >(    ( pos.y / 1000.f ) * 240         );
    
    return pos;
}


////////////////////////////////////////////////////////////
Vector2i InputImpl::getMousePosition(const Window& relativeTo)
{
	return getMousePosition();
}


////////////////////////////////////////////////////////////
void InputImpl::setMousePosition(const Vector2i& position)
{
	// Impossible
}


////////////////////////////////////////////////////////////
void InputImpl::setMousePosition(const Vector2i& position, const Window& relativeTo)
{
	// Impossible
}

} // namespace priv

} // namespace sf
