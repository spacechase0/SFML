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
m_display   (0),
m_window    (0),
m_glDisplay (0),
m_glConfig  (0),
m_glContext (0),
m_glSurface (0),
m_ownsWindow(true)
{
    createContext(shared, ContextSettings());
}


////////////////////////////////////////////////////////////
WizGlContext::WizGlContext(WizGlContext* shared, const ContextSettings& settings, const WindowImpl* owner, unsigned int bitsPerPixel) :
m_display   (0),
m_window    (0),
m_glDisplay (0),
m_glConfig  (0),
m_glContext (0),
m_glSurface (0),
m_ownsWindow(true)
{
    // Use the same display as the owner window (important!)
    m_display = static_cast<const WindowImplWiz*>(owner)->getDisplay();

    // Get the owner window and its device context
    m_window = static_cast< ::OS_Window>(owner->getSystemHandle());

    // Create the context
    if (m_window)
        createContext(shared, settings);
}


////////////////////////////////////////////////////////////
WizGlContext::WizGlContext(WizGlContext* shared, const ContextSettings& settings, unsigned int width, unsigned int height) :
m_display   (0),
m_window    (0),
m_glDisplay (0),
m_glConfig  (0),
m_glContext (0),
m_glSurface (0),
m_ownsWindow(true)
{
    // Create the context
    createContext(shared, settings);
}


////////////////////////////////////////////////////////////
WizGlContext::~WizGlContext()
{
    // Destroy the context
    if (m_glContext)
    {
        if (eglGetCurrentContext() == m_glContext)
			eglMakeCurrent( m_glDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
		eglDestroySurface( m_glDisplay, m_glSurface ); 
		eglDestroyContext( m_glDisplay, m_glContext );
		eglTerminate( m_glDisplay );
    }
}


////////////////////////////////////////////////////////////
bool WizGlContext::makeCurrent()
{
    return m_glContext && eglMakeCurrent(m_glDisplay, m_glSurface, m_glSurface, m_glContext);
}


////////////////////////////////////////////////////////////
void WizGlContext::display()
{
    if (m_window)
        eglSwapBuffers(m_glDisplay, m_glSurface);
}


////////////////////////////////////////////////////////////
void WizGlContext::setVerticalSyncEnabled(bool enabled)
{
    #warning WizGlContext::setVerticalSyncEnabled not implemented.
}


////////////////////////////////////////////////////////////
void WizGlContext::createContext(WizGlContext* shared, const ContextSettings& settings)
{
	// Save the creation settings
    m_settings = settings;

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
    m_glDisplay = eglGetDisplay(static_cast< NativeDisplayType >(0));
    if (m_glDisplay == EGL_NO_DISPLAY)
    {
    	err() << "Failed to create display: " << glGetError() << std::endl;
    	return;
    }
    
	EGLint numConfigs;
    EGLint majorVersion;
    EGLint minorVersion;
    
    // Intiailize EGL
    if (!eglInitialize(m_glDisplay, &majorVersion, &minorVersion))
    {
    	err() << "Failed to init EGL: " << glGetError() << std::endl;
    	return;
    }
    
    // Choose config
    if(!eglChooseConfig(m_glDisplay, attrib_list, &m_glConfig, 1, &numConfigs))
    {
    	err() << "Failed to choose config: " << glGetError() << std::endl;
    	return;
    }
    
    // Create context
    m_glContext = eglCreateContext( m_glDisplay, m_glConfig, NULL, NULL );
    if ( m_glContext == 0 )
    {
    	err() << "Failed to create context: " << glGetError() << std::endl;
    	return;
    }
    
    // Create surface
    m_glSurface = eglCreateWindowSurface( m_glDisplay, m_glConfig, m_window, NULL );
    if ( m_glSurface == NULL )
    {
    	err() << "Failed to create surface: " << glGetError() << std::endl;
    	return;
    }
}

} // namespace priv

} // namespace sf
