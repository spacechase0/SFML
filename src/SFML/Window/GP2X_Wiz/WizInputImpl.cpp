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
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

namespace sf
{
namespace priv
{

WizInputImpl::WizInputImpl() 
{
	// Hello libcastor!
	buttonFd = open("/dev/mem", O_RDWR);
	if (buttonFd < 0)
	{
		sf::Err() << "Failed to open /dev/mem." << std::endl;
		return;
	}
	
	reg32 = (volatile sf::Uint32*)(mmap(0, 0x10000, PROT_READ | PROT_WRITE, MAP_SHARED, buttonFd, 0xC0000000));
	if (reg32 == (volatile sf::Uint32*)(0xFFFFFFFF))
	{
		sf::Err() << "Failed to get registers." << std::endl;
		close(buttonFd);
		buttonFd = -1;
		return;
	}
	
	reg16 = (volatile sf::Uint16*)(reg32);
	
	// Except this. I figured this part out myself. :P
	mouseFd = open("/dev/input/event0", O_RDONLY | O_NDELAY);
	if (mouseFd < 0)
	{
		sf::Err() << "Failed to open /dev/input/event0." << std::endl;
		return;
	}
}

void WizInputImpl::Update()
{
	int r = 0;
	struct input_event event;
	while ((r = read(mouseFd, &event, sizeof(input_event))) != -1)
	{
		if (r < sizeof(input_event))
		{
			break;
		}
		
		if (event.type == EV_KEY and event.code & BTN_MOUSE)
		{
			mousePressed = event.value;
		}
		// I have no idea which of these two I should do, so I'll just do both.
		else if (event.type == EV_ABS)
		{
			// I have no idea why these are flipped. :P
			if (event.code == ABS_Y)
			{
				mousePos.x += event.value - mousePos.x;
			}
			if (event.code == ABS_X)
			{
				mousePos.y += event.value - mousePos.y;
			}
		}
		else if (event.type == EV_REL)
		{
			if (event.code == ABS_Y)
			{
				mousePos.x += event.value;
			}
			if (event.code == ABS_X)
			{
				mousePos.y += event.value;
			}
		}
	}
}

WizInputImpl::~WizInputImpl()
{
	if (buttonFd >= 0)
	{
		close(buttonFd);
	}
	if (mouseFd >= 0)
	{
		close(mouseFd);
	}
}

WizInputImpl inputImpl;

} // namespace priv

} // namespace sf
