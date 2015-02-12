

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

		enum ServerStatus
		{
			Init_Suc = 0,
			Start_Suc,
			Start_Fail,
		};

		class Acceptor;

#ifdef WIN32
		struct RequestHandle
		{
			OVERLAPPED	 _overlapped;
			unsigned char _type;
			std::shared_ptr<Acceptor> _tcpAccept;
			enum HANDLE_TYPE
			{
				HANDLE_ACCEPT,
				HANDLE_RECV,
				HANDLE_SEND,
				HANDLE_CONNECT,
				HANDLE_RECVFROM,
				HANDLE_SENDTO,
			};
		};
#endif
		class Connection;
		typedef std::function<void(ErrorCode, std::shared_ptr<Connection>)> Accept_Handler;
		
	}
}





#endif