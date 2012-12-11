#include "WPILib.h"
#include "DigitalInput.h"
#include "pthread.h"
#include "math.h"

#ifndef BALLINH
#define BALLINH

class BallHandle {
	Victor *shootV, *feedV, *conV, *intakeV;
	Joystick *rightstick, *leftstick, *manipulatorstick;
	DigitalInput s_bottom, /*s_middle,*/ s_top, s_intake;
	AnalogChannel *ballin;
	bool bottom1, bottom2, middle, top, tflag, shoot, threaded, bumval, topval;

	float perr; // static error
	float integral; // static integral
	float pout; //static output
	float err1;

	void Purge();
	static void *hQueue(void*);
	static void *hBang(void*);
	GearTooth gtshoot;
public:
	float rpm;
	bool dpurge, autonomous;
	//static float err;
	BallHandle();
	BallHandle(Victor*, Victor*, Victor*, Victor*, Victor*, AnalogChannel*, Joystick*, Joystick*, Joystick*);
	void Init(Victor*, Victor*, Victor*, Victor*, Victor*, AnalogChannel*, Joystick*, Joystick*, Joystick*);
	void StartHandle();
	void hBangB(double waittime);
	void CycleUp();
	void CycleDown();
	void Shoot();
	void StopHandle();
	float abs(float n); // absolute function for floats
	~BallHandle(){};
	float shooterPID(float setrpm, float kp, float ki, float kd, float dt, float merr); // handles shooter PID
	void VertPurge();
};

#endif
