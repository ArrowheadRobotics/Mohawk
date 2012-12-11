#ifndef SOCKSH
#define SOCKSH
#include "WPILib.h"
#include "stdio.h" // standard i/o
#include "arpa/inet.h" // inet functions
#include "netinet/in.h" // inet functions
#include "stdio.h" // standard i/o (again)
#include "sys/types.h" // socket types
#include "sys/socket.h" // core socket functions
#include "netinet/in.h" // inet functions (again)
#include "netdb.h" // error ids for network functions
#include "errno.h" // error handling for network functions
#include "pthread.h" // POSIX threading
#include "ioctl.h"

//DON'T TOUCH

class RoboSock {
	bool connected, connecting;// bool for determining if connected
	char buf[512], ip[24]; // generic character buffer for sending
	int s, port; // socket
	struct sockaddr_in sai_remote; // sockaddr that determined server
	static void *connServ(void*);
public:
	bool emergencystop;
	enum Values { // enum for fetching value types
		DIST = 1, // queries server for distance data
		ANGLE = 2 // queries server for angular data
	};
	int err; // generic error integer
	RoboSock(); // constructor when not initing connection
	RoboSock(char*, unsigned short); // constructor when initing connection
	void initConn(char*, unsigned short); // inits connection
	bool isConnected() { return connected; }; // returns if connected to server
	float GetValue(RoboSock::Values); // queries server for corresponding value
	void Disconnect(); // disconnects from server
	~RoboSock(); // destructor (disconnects if connected)
};

#endif
