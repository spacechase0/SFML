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
bool InputImpl::IsKeyPressed(Keyboard::Key key)
{
    sf::Uint32 buttons = GetButtons();
    
    // Get the right key
    #define DoKey(a) a ## _E:  return buttons & a;
    switch ( key )
    {
    	DoKey( LEFT_SHOULDER );
    	DoKey( RIGHT_SHOULDER );
    	
    	DoKey( UP );
    	DoKey( LEFT );
    	DoKey( DOWN );
    	DoKey( RIGHT );
    	
    	DoKey( BUTTON_Y );
    	DoKey( BUTTON_A );
    	DoKey( BUTTON_X );
    	DoKey( BUTTON_B );
    	
    	DoKey( VOLUME_UP );
    	DoKey( VOLUME_DOWN );
    	
    	DoKey( MENU );
    	DoKey( SELECT );
    }
    #undef DoKey
    
    return false;
}


////////////////////////////////////////////////////////////
bool InputImpl::IsMouseButtonPressed(Mouse::Button button)
{
    return inputImpl.mousePressed;
}


////////////////////////////////////////////////////////////
Vector2i InputImpl::GetMousePosition()
{
    return inputImpl.mousePos;
}


////////////////////////////////////////////////////////////
Vector2i InputImpl::GetMousePosition(const Window& relativeTo)
{
	return GetMousePosition();
}


////////////////////////////////////////////////////////////
void InputImpl::SetMousePosition(const Vector2i& position)
{
	// Impossible
}


////////////////////////////////////////////////////////////
void InputImpl::SetMousePosition(const Vector2i& position, const Window& relativeTo)
{
	// Impossible
}

} // namespace priv

} // namespace sf
