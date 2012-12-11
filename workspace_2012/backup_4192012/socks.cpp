#include "socks.h"

// FIXSIASDFDS AUTO AIM AND ASYNCHRONOSU SOCJSG

RoboSock::RoboSock(char *ip, unsigned short port) { // constructor, initializes connection
	connected = false; // sets connected to false
	connecting = false;
	emergencystop = false;
	initConn(ip, port); // calls internal function initConn
}

RoboSock::RoboSock(void) { // constructor, does not init connection
	connected = false; // sets connected to false
	connecting = false;
	emergencystop = false;
	err = -1; // sets error value to -1
}

void RoboSock::initConn(char *ip, unsigned short port) {
	if(!connecting && !connected) {
		sprintf(this->ip, "%s", ip);
		this->port = port;
		connecting = true;
		this->err = -1; // sets error value to -1
		pthread_t conn;
		pthread_create(&conn, NULL, connServ, (void *)this);
	} else printf("ALREADY CONWEABTGBGASDNG\n");
}

float RoboSock::GetValue(RoboSock::Values v) { // queries server for value
	int check = 0;
	if(connected) { // if connected to server
		memset(&buf, 0, 512); // clear buffer
		sprintf(buf, "%c", v); // attach data id to packet
		send(s, buf, 512, 0); // send packet with data id to server
		memset(&buf, 0, 512); // clear buffer
		printf("Querying server ...\n");
		while(!emergencystop && (errno == EAGAIN)) { printf("Getting... %i\n", errno); check = recv(s, buf, 512, 0); } // get corresponding data from server
		if(check == -1) {
			printf("ERROR IN RECV; REINITING CONNECTION\n");
			if(!connecting) {
				close(s);
				connected = false;
				connecting = true;
				pthread_t conn;
				pthread_create(&conn, NULL, connServ, (void *)this);
			}
			return -1.f;
		}
		try { // aka how to handle errors
			return atof(buf); // convert recv'd string to float
		} catch(...) {
			return -1.f; // error code for atof call failing to translate string to float
		}
	} else
		return -1.f; // error code for connection failure
}

void *RoboSock::connServ(void *arg) {
	RoboSock *s = (RoboSock *)arg;
	printf("Connecting ...\n");
	while(s->err == -1 && !s->emergencystop) { // so long as connection has proved ineffective
		s->connected = false; // set connected to false (just in case)
		s->s = socket(AF_INET, SOCK_STREAM, 0); // create socket (with TCP mode using AF family)
		if (s->s == -1) { // if socket creation failed
			printf("SOCK CRET ERR %i\n", errno);
			return 0; // exit
		}
		memset((char*)&s->sai_remote, 0, sizeof(s->sai_remote)); // clear sockaddr_in struct before use (to be safe)
		s->sai_remote.sin_family = AF_INET; // sets struct's family to INET
		s->sai_remote.sin_addr.s_addr = inet_addr(s->ip); // sets struct's address to provided address
		s->sai_remote.sin_port = htons(s->port); // sets struct's port to provided port
		fcntl(s->s, O_NONBLOCK);
		do {
			printf("Attempting ...\n");
			s->err = connect(s->s, (struct sockaddr *)&s->sai_remote, sizeof(s->sai_remote)); // determines if connection was erroneous
		} while(errno == EINPROGRESS && !s->emergencystop);
		s->connected = true; // now officially connected (we think)
		if(s->emergencystop) {
			s->Disconnect();
			s->emergencystop = false;
		}
		printf("ERR %i\n", errno);
		if(s->err == -1) { // so long as connecting has failed
			close(s->s);
			printf("Connection timed out: ERR %i. Retrying...\n", errno); // informative message
		}
	}
	s->connecting = false;
	printf("Connected.\n");
	return 0;
}

void RoboSock::Disconnect() { // disconnect from server
	if(connected || connecting) { // check if connected
		memset(&buf, 0, 512); // clear buffer
		sprintf(buf, "%c", 127); // attach data id for disconnecting (127)
		err = send(s, buf, 512, 0); // send data id to server
		connected = false; // not connected
		connecting = false;
		emergencystop = false;
		close(s);
	}
}

RoboSock::~RoboSock() { // destructor
	if(connected || connecting) { // check if connected
		memset(&buf, 0, 512); // clear buffer
		sprintf(buf, "%c", 127); // attach data id for disconnecting (127)
		err = send(s, buf, 512, 0); // send data id to server
		connected = false; // not connected
		connecting = false;
		emergencystop = false;
	}
}
