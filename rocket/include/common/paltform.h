#ifndef _ROCKET_PLATFORM_H
#define _ROCKET_PLATFORM_H


// default in windows use IOCP implementation
// default in linux use EPOLL LT implementation 
// default in mac use select implementation
// if can't compile on  some other system , you can try compile used ZSUMMERX_USE_SELECT.  It's be force compiled with select implementation.


#include<iostream>

#ifdef WIN32
	#include "iocp/iocp.h"
	#include "iocp/acceptor.h"

#else

#if __APPLE__ 


#else


#endif
#endif

#endif