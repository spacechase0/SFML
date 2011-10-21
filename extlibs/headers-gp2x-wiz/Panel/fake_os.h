//------------------------------------------------------------------------------
//
//	Copyright (C) 2003 MagicEyes Digital Co., Ltd All Rights Reserved
//	MagicEyes Digital Co. Proprietary & Confidential
//
//	MAGICEYES INFORMS THAT THIS CODE AND INFORMATION IS PROVIDED "AS IS" BASE AND 
//	WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//	THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//
//	Module     :
//	File       : Fake_OS.h
//	Description:
//	Author     : Yuni(yuni@mesdigital.com)
//	Export     :
//	History    :
//	   2007/01/22 Gamza first implementation
//------------------------------------------------------------------------------
#ifndef __FAKE_OS_H__
#define __FAKE_OS_H__

#ifdef linux
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
//	Type definition
//------------------------------------------------------------------------------
#ifndef		NULL
	#define		NULL	0
#endif

typedef	unsigned short	WORD;
typedef	unsigned int	DWORD;

#ifndef true
	#define true	1
#endif

#ifndef	false
	#define false	0
#endif

#ifndef	byte
	typedef char	byte;
#endif

//------------------------------------------------------------------------------
//	Initialize platform
//------------------------------------------------------------------------------
void 	OS_InitFakeOS( void );

//------------------------------------------------------------------------------
//	Window
//------------------------------------------------------------------------------
typedef	void*	OS_Display;
typedef void*	OS_Window;
OS_Window 		OS_CreateWindow( void );
void 			OS_GetWindowSize( const OS_Window window, int* pWidth, int* pHeight );

//------------------------------------------------------------------------------
//	Timer
//------------------------------------------------------------------------------
unsigned int 	OS_GetTickCount( void );
void			OS_Sleep( unsigned int milliseconds );

//------------------------------------------------------------------------------
//	File I/O
//------------------------------------------------------------------------------
#ifdef linux
#define OS_SEEK_SET		SEEK_SET
#define OS_SEEK_CUR		SEEK_CUR
#define OS_SEEK_END		SEEK_END
#define OS_FILE   FILE*
#define OS_fopen  fopen
#define OS_fclose fclose
#define OS_fseek  fseek
#define OS_fread  fread
#else
#define OS_SEEK_SET		0
#define OS_SEEK_CUR		1
#define OS_SEEK_END		2
typedef int OS_FILE;
OS_FILE OS_fopen( const char *filename, const char *mode );
int OS_fclose( OS_FILE stream );
int OS_fseek( OS_FILE stream, long offset, int origin );
unsigned int OS_fread( void *buffer, unsigned int size, unsigned int count, OS_FILE stream );
#endif

#ifdef __cplusplus
}
#endif
#endif // __FAKE_OS_H__

