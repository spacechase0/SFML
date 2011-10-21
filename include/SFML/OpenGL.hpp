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

#ifndef SFML_OPENGL_HPP
#define SFML_OPENGL_HPP


////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.hpp>


////////////////////////////////////////////////////////////
/// This file just includes the OpenGL (GL and GLU) headers,
/// which have actually different paths on each system
////////////////////////////////////////////////////////////
#if defined(SFML_SYSTEM_WINDOWS)

    // The Visual C++ version of gl.h uses WINGDIAPI and APIENTRY but doesn't define them
    #ifdef _MSC_VER
        #include <windows.h>
    #endif

    #include <GL/gl.h>
    #include <GL/glu.h>

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD)
	
	// GP2X Wiz
	#if defined(SFML_SYSTEM_GP2X_WIZ)
		#include <GL/egl.h>
		#include <OpenGLES/gl.h>
		#include <OpenGLES/libogl.h>
		#include <GL/nanogl.h>
	#else
		#include <GL/gl.h>
		#include <GL/glu.h>
	#endif

#elif defined(SFML_SYSTEM_MACOS)

    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>

#endif


#endif // SFML_OPENGL_HPP
