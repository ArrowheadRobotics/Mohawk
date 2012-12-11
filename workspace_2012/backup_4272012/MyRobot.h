#ifndef ROBOTH // essentially #pragma once
#define ROBOTH // essentially #pragma once
#include "WPILib.h"
#include "CANJaguar.h"
#include "Victor.h"
#include "Compressor.h"
#include "Encoder.h"
#include "socks.h" // robot sockets
#include "ballhandler.h"
#include "Solenoid.h"
#include "Relay.h"
#include "ugly.h" // Joystick defines

#include "math.h"

class RobotDemo : public SimpleRobot
{
	Joystick jstick1; // joystick 1
	Joystick jstick2; // joystick 2
	Joystick jstick3; // joystick 3
	
	RoboSock *sock; // robot socket object
	
	CANJaguar cjleft1; // left canjaguar one
	CANJaguar cjleft2; // left canjaguar two
	CANJaguar cjright1; // right canjaguar one
	CANJaguar cjright2; // right canjaguar two
		
	Solenoid sshifter1; // left shifter solenoid
	Solenoid sshifter2; // right shifter solenoid
	Solenoid stipper1; // left tipper solenoid
	Solenoid stipper2; // right tipper solenoid
	Solenoid shood1;
	Solenoid shood2;
	
	Victor shootV;
	Victor feedV;
	Victor turretV;
	Victor conV;
	Victor intakeV;

	// TODO: confirm and initialize encoders
	
	Compressor cpres; // compressor
	
	AnalogChannel acballin;  //bottom ball sesor  sonic
	AnalogChannel acpot;
	
	bool stopaim, aiming, turbo_mode;
	
	BallHandle helev;
	
	int cycles;
	
	static void *Auto_aim(void *);
public:
	enum Solenoids {SHIFTERS, TIPPERS, HOOD}; // enum for values passed into ctrlSolenoids function
	RobotDemo(void); // constructor
	void Autonomous(void); // autonomous mode
	void OperatorControl(void); // operator mode
	void Drive(float, float); // handles driving
	float rotateP(float set_volt);
	float abs(float n); // absolute function for floats
	// TODO: add more relative PIDs
	void ctrlSolenoids(Solenoids, bool); // handle solenoid movements
	void Halt(void); // stop robot on dime
	void SpawnAim(void);
	void KillAim(void);
	void KillRecv(void);
	
};

#endif // essentially #pragma once
