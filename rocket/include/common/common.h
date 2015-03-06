

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

		//receive buffer length  and send buffer length 
		const unsigned int MSG_BUFF_SIZE = 64 * 1024 - 1;

		static unsigned int max_sessions_round = 300000000;
		inline unsigned int nextSessionId(unsigned int cur_session_id){ return (cur_session_id + 1) % max_sessions_round; }

		extern Env env;

		enum ErrorCode
		{
			EC_SUCCESS = 0,
			EC_ERROR,
			EC_REMOTE_CLOSED,
			EC_REMOTE_HANGUP,
		};

		enum SOCKET_STATUS
		{
			LS_UNINITIALIZE, //socket default status
			LS_WAITLINK, // socket status after init and will to connect.
			LS_ESTABLISHED, //socket status is established
			LS_CLOSED, // socket is closed. don't use it again.
		};

		enum ServerStatus
		{
			Init_Suc = 0,
			Start_Suc,
			Start_Fail,
		};

		class Acceptor;
		class Connection;

#ifdef WIN32
		struct RequestHandleTag
		{
			OVERLAPPED	 _overlapped;
			unsigned char _type;
			std::shared_ptr<Acceptor> _tcpAccept;
			std::shared_ptr<Connection> _connection;
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
#define ConvertOverlaped(ptr)  (*(RequestHandleTag*)((char*)ptr - (char*)&((RequestHandleTag*)NULL)->_overlapped))

#endif
		class Connection;
		typedef std::function<void(ErrorCode, std::shared_ptr<Connection>)> Accept_Handler;
		
		typedef std::function<void(ErrorCode, int)> Recv_Handler;

	}
}





#endif