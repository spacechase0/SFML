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

#ifndef SFML_WIZINPUTIMPL_HPP
#define SFML_WIZINPUTIMPL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////


namespace sf
{
namespace priv
{

struct WizInputImpl
{
	WizInputImpl();
	~WizInputImpl();
	
	void Update();

	~WizInputImpl();

	int buttonFd;
	volatile sf::Uint32* reg32;
	volatile sf::Uint16* reg16;
	
	int mouseFd;
	sf::Vector2i mousePos;
	bool mousePressed;
};

extern WizInputImpl inputImpl;

enum WizKeyEquivalents
{
	LEFT_SHOULDER_E  = sf::Keyboard::L,
	RIGHT_SHOULDER_E = sf::Keyboard::R,
	
	UP_E    = sf::Keyboard::Up,
	LEFT_E  = sf::Keyboard::Left,
	DOWN_E  = sf::Keyboard::Down,
	RIGHT_E = sf::Keyboard::Right,
	
	BUTTON_Y_E = sf::Keyboard::Y,
	BUTTON_A_E = sf::Keyboard::A,
	BUTTON_X_E = sf::Keyboard::X,
	BUTTON_B_E = sf::Keyboard::B,
	
	VOLUME_UP_E   = sf::Keyboard::Add,
	VOLUME_DOWN_E = sf::Keyboard::Subtract,
	
	MENU_E   = sf::Keyboard::Menu,
	SELECT_E = sf::Keyboard::Return,
};

enum WizKeyCodes
{
	LEFT_SHOULDER  = (1 << 7),
	RIGHT_SHOULDER = (1 << 6),
	
	UP    = (1 << 18),
	LEFT  = (1 << 16),
	DOWN  = (1 << 19),
	RIGHT = (1 << 17),
	
	BUTTON_Y = (1 << 23),
	BUTTON_A = (1 << 20),
	BUTTON_X = (1 << 22),
	BUTTON_B = (1 << 21),
	
	VOLUME_UP   = (1 << 10),
	VOLUME_DOWN = (1 << 11),
	
	MENU   = (1 << 9),
	SELECT = (1 << 8),
};

inline sf::Uint32 GetButtons()
{
	// C, then B.
	// What is A?
	return ~(((inputImpl.reg16[0xA098>>1]) << 16) | (inputImpl.reg16[0xA058>>1]));
}

} // namespace priv

} // namespace sf

#endif // SFML_WIZINPUTIMPL_HPP
