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
#include <SFML/System/Err.hpp>

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
WindowImplWiz::WindowImplWiz(WindowHandle handle) :
myWindow      (0),
myKeyRepeat   (true)
{
	#warning Not implemented
}


////////////////////////////////////////////////////////////
WindowImplWiz::WindowImplWiz(VideoMode mode, const std::string& title, unsigned long style) :
myWindow      (0),
myKeyRepeat   (true)
{
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


////////////////////////////////////////////////////////////
::Display* WindowImplWiz::GetDisplay() const
{
    return myDisplay;
}


////////////////////////////////////////////////////////////
WindowHandle WindowImplWiz::GetSystemHandle() const
{
    return myWindow;
}


////////////////////////////////////////////////////////////
void WindowImplWiz::ProcessEvents()
{
    #warning Not implemented
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
