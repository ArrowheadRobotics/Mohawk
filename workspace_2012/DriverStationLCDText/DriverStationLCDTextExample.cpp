#include "WPILib.h"
#include "stdio.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "netdb.h"
#include "errno.h"
#include "pthread.h"
#include "Joystick.h"
#include "Jaguar.h"

#define BUFLEN 512
#define PORT 8900
#define RIP "10.7.6.24"

/* GLOBAL VARIABLES / FUNCTIONS
  FOR POSIX STANDARD THREADING COMPLIANCE
  DONUT TOUCH
 */


/* START WINDEX UNSTANDARD SEWING APPLIANCE */

class Robot706 : public SimpleRobot
{
	Joystick leftstick;
	Joystick rightstick;
	Jaguar leftjag;
	Jaguar rightjag;
	Gyro oryg;
	char buf[BUFLEN];

	void clrBuf() {
		memset(&buf, 0, BUFLEN);
	}		
	
	float queryInfo() {
		DriverStationLCD *dsLCD;
		dsLCD = DriverStationLCD::GetInstance();
		struct sockaddr_in sai_remote;
		int s, gen;
		clrBuf();
		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s == -1)
			return 0.f;
		memset((char*)&sai_remote, 0, sizeof(sai_remote));
		sai_remote.sin_family = AF_INET;
		sai_remote.sin_addr.s_addr = inet_addr(RIP);
		sai_remote.sin_port = htons(PORT);
		dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Connecting...");
		dsLCD->UpdateLCD();
		gen = connect(s, (struct sockaddr *)&sai_remote, sizeof(sai_remote));
		if(gen < 0) {
			return 0.f;
		}
		dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Connected.");
		dsLCD->UpdateLCD();
		sprintf(buf, "706");
		send(s, buf, BUFLEN, 0);
		clrBuf();
		recv(s, buf, BUFLEN, 0);
		return atof(buf);
	}
public: 
	Robot706(void):
		leftstick(1), rightstick(2),
		leftjag(1), rightjag(2),
		oryg(1)
	{
	
	}
	
	void RobotMain()
	{
		DriverStationLCD *dsLCD;
		dsLCD = DriverStationLCD::GetInstance();
		dsLCD->Clear();
		dsLCD->UpdateLCD();
		int s; // TO BE SOCKET DONUT CHANGFE UWRSDABGASJH
		//bool toggle = false;
		while(true) {
			/*if(leftstick.GetTrigger()){
				toggle= true;
			}else{
				toggle=false;
			}
			
			if(toggle) {
				leftjag.Set(-.4);
				rightjag.Set(.4);
				float gdist = queryInfo();
				if(gdist <= 3.f)
					break;
			}else{
				leftjag.Set(0);
				rightjag.Set(0);
			}*/
			if(leftstick.GetRawButton(8))
				oryg.Reset(); // Recalibrate Gyro
			if(leftstick.GetRawButton(3)) {
				// assist user in balancing
				
			}
			leftjag.Set(leftstick.GetY());
			rightjag.Set(rightstick.GetY());
			Wait(0.01f);
		}
	}   
};

START_ROBOT_CLASS(Robot706);
