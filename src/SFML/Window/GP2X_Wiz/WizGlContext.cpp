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
#include <SFML/Window/GP2X_Wiz/WizGlContext.hpp>
#include <SFML/Window/GP2X_Wiz/WindowImplWiz.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System/Err.hpp>

namespace
{
	class NanoGl
	{
		NanoGl()
		{
			nanoGL_Init();
		}
		
		~NanoGl()
		{
			nanoGL_Destroy();
		}
		
		static NanoGl nanoGl;
	};
	NanoGl NanoGl::nanoGl;
}

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
WizGlContext::WizGlContext(WizGlContext* shared) :
myDisplay   (0),
myWindow    (0),
myGlDisplay (0),
myGlConfig  (0),
myGlContext (0),
myGlSurface (0),
myOwnsWindow(true)
{
    CreateContext(shared, ContextSettings());
}


////////////////////////////////////////////////////////////
WizGlContext::WizGlContext(WizGlContext* shared, const ContextSettings& settings, const WindowImpl* owner, unsigned int bitsPerPixel) :
myDisplay   (0),
myWindow    (0),
myGlDisplay (0),
myGlConfig  (0),
myGlContext (0),
myGlSurface (0),
myOwnsWindow(true)
{
    // Use the same display as the owner window (important!)
    myDisplay = static_cast<const WindowImplWiz*>(owner)->GetDisplay();

    // Get the owner window and its device context
    myWindow = static_cast< ::OS_Window>(owner->GetSystemHandle());

    // Create the context
    if (myWindow)
        CreateContext(shared, settings);
}


////////////////////////////////////////////////////////////
WizGlContext::WizGlContext(WizGlContext* shared, const ContextSettings& settings, unsigned int width, unsigned int height) :
myDisplay   (0),
myWindow    (0),
myGlDisplay (0),
myGlConfig  (0),
myGlContext (0),
myGlSurface (0),
myOwnsWindow(true)
{
    // Create the context
    CreateContext(shared, settings);
}


////////////////////////////////////////////////////////////
WizGlContext::~WizGlContext()
{
    // Destroy the context
    if (myGlContext)
    {
        if (eglGetCurrentContext() == myGlContext)
			eglMakeCurrent( myGlDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
		eglDestroySurface( myGlDisplay, myGlSurface ); 
		eglDestroyContext( myGlDisplay, myGlContext );
		eglTerminate( myGlDisplay );
    }
}


////////////////////////////////////////////////////////////
bool WizGlContext::MakeCurrent()
{
    return myGlContext && eglMakeCurrent(myGlDisplay, myGlSurface, myGlSurface, myGlContext);
}


////////////////////////////////////////////////////////////
void WizGlContext::Display()
{
    if (myWindow)
        eglSwapBuffers(myGlDisplay, myGlContext);
}


////////////////////////////////////////////////////////////
void WizGlContext::EnableVerticalSync(bool enabled)
{
    #warning WizGlContext::EnableVerticalSync not implemented.
}


////////////////////////////////////////////////////////////
void WizGlContext::CreateContext(WizGlContext* shared, const ContextSettings& settings)
{
	// Save the creation settings
    mySettings = settings;

    // Get the attributes of the target window
    EGLint attrib_list_fsaa[] =
	{
	  EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	  EGL_BUFFER_SIZE,  0,
	  EGL_DEPTH_SIZE,   16,
	  EGL_SAMPLE_BUFFERS, 1,
	  EGL_SAMPLES,        4,
	  EGL_NONE
	};
	
	EGLint attrib_list[] =
	{
	  EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	  EGL_BUFFER_SIZE,  0,
	  EGL_DEPTH_SIZE,   16,
	  EGL_NONE
	};
	
	// Create the display.
    myGlDisplay = eglGetDisplay(static_cast< NativeDisplayType >(0));
    if (myGlDisplay == EGL_NO_DISPLAY)
    {
    	Err() << "Failed to create display: " << glGetError() << std::endl;
    	return;
    }
    
	EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    
    // Intiailize EGL
    if (!eglInitialize(myGlDisplay, &majorVersion, &minorVersion))
    {
    	Err() << "Failed to init EGL: " << glGetError() << std::endl;
    	return;
    }
    
    // Choose config
    if(!eglChooseConfig(myGlDisplay, attrib_list, &myGlConfig, 1, &numConfigs))
    {
    	Err() << "Failed to choose config: " << glGetError() << std::endl;
    	return;
    }
    
    // Create context
    myGlContext = eglCreateContext( myGlDisplay, myGlConfig, NULL, NULL );
    if ( myGlContext == 0 )
    {
    	Err() << "Failed to create context: " << glGetError() << std::endl;
    	return;
    }
    
    // Create surface
    myGlSurface = eglCreateWindowSurface( myGlDisplay, myGlConfig, myWindow, NULL );
    if ( myGlSurface == NULL )
    {
    	Err() << "Failed to create surface: " << glGetError() << std::endl;
    	return;
    }
}

} // namespace priv

} // namespace sf
