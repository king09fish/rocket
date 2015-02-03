

#pragma once
#ifndef _ROCKET_COMMON_H
#define _ROCKET_COMMON_H

//common bead files
#include<assert.h>
#include<iostream>

#ifdef WIN32
	#include <WinSock2.h>
	#include <Windows.h>
#endif


namespace rocket
{
	namespace network
	{
		class Env
		{
		public:
			Env();

			~Env();

			void InitEnv();

		};
		extern Env env;
		
	}
}





#endif