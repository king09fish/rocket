

#pragma once
#ifndef _ROCKET_COMMON_H
#define _ROCKET_COMMON_H

//common bead files
#include<assert.h>
#include<iostream>
#include<memory>
#include<functional>
#ifdef WIN32
	#include <WinSock2.h>
	#include <Windows.h>
	#include <MSWSock.h>

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

		enum ErrorCode
		{
			EC_SUCCESS = 0,
			EC_ERROR,
			EC_REMOTE_CLOSED,
			EC_REMOTE_HANGUP,
		};


	
		typedef std::function<void(ErrorCode, std::shared_ptr<Connection>)> _AcceptHandler;
		
	}
}





#endif