#include "ballhandler.h"

//handle the position of the balls. We need to provide functions for cycling upwards, downards
//provide led on dash
//WE NEED TO DO THIS BY RECIEVED DATA / STATES, not a theoretical array of ball positions
//todo motor safety, too many counts on high, stop them until a button pressed

BallHandle::BallHandle(Victor *shoot, Victor *feed, Victor *turret,
		Victor *elev, Victor *ballin, AnalogChannel *acballin, Joystick *right,
		Joystick *left, Joystick *manip) :
	s_bottom(6), /*s_middle(13),*/s_top(3)/*TODO GET THIS TO BE RIGHT*/,
			s_intake(4), gtshoot(7) {
	//err =0;
	perr = 0; // static error
	integral = 0; // static integral
	pout = 0; //static output
	err1 = 0;
	gtshoot.Start();
	Init(shoot, feed, turret, elev, ballin, acballin, right, left, manip);
}
/* . . . .
 * E E E E O O O O
 * E E O O E E O O
 * E O E O E O E O
 */

void BallHandle::StartHandle() {
	tflag = true;
	pthread_t handler;
	pthread_create(&handler, NULL, hQueue, (void *) this);
}

void BallHandle::StopHandle() {
	tflag = false;
}

void *BallHandle::hQueue(void *arg) {
	BallHandle *obj = (BallHandle *) arg;
	obj->intakeV->Set(-.25f);
	/*
		// turretV is on pwm3
		if(S1B3){
			tole = !tole;
		}  //
		if (!tole) {
			turretV.Set(PID(S1Z*4000));
		} else {
			turretV.Set(S1Z);
		}
		Wait(.05f);
	 */
	while (obj->tflag) {
		if(!obj->s_top.Get()) 
			obj->intakeV->Set(.25f);
		else
			obj->intakeV->Set(-.25f);
		if ((!obj->s_intake.Get() && obj->s_top.Get()) && obj->shoot == false) {
			printf("hi");
			obj->conV->Set(.35);

			obj->intakeV->Set(-1);
			Wait(1.6); //Todo tune
			printf("3\n");
			bool bumval = !obj->s_bottom.Get();
			bool topval = !obj->s_top.Get();
			while (!obj->bumval) {
				if (obj->rightstick->GetRawButton(3))
					break;

				bumval = !obj->s_bottom.Get();
				topval = !obj->s_top.Get();
				//							if(s_top.Get()) intakeV.Set(1);
				//			 				else intakeV.Set(-1);
				//							printf("orbiting: %d %d %d\n",s_intake.Get(),s_bottom.Get(),s_top.Get());
			}
			
			obj->conV->Set(0);
		}			
		if(obj->shoot) {
			obj->shoot = 1;
			obj->conV->Set(-1);//todo correct?
			Wait(.25); // todo tune
			obj->conV->Set(0);
	
			obj->feedV->Set(-1);// todo correct?
			while (obj->manipulatorstick->GetTop()) {
				if (obj->rightstick->GetRawButton(3))
					break;
				obj->conV->Set(0);
			}
			obj->conV->Set(.25);//todo correct
			while (obj->manipulatorstick->GetTrigger()) {
				if (obj->rightstick->GetRawButton(3))
					break;
				Wait(.05);
				while (obj->manipulatorstick->GetTop()) {
					if (obj->rightstick->GetRawButton(3))
						break;
					obj->conV->Set(0);
				}
				obj->conV->Set(.5);
			}
			obj->conV->Set(0);
			//				shootV.Set(0);
			obj->feedV->Set(0);
			obj->shoot = 0;
		} else {
			obj->shoot = 0;
			obj->conV->Set(0);
			//				shootV.Set(0);
			obj->feedV->Set(0);
		}
		obj->shoot = false;
	}
	// TODO handle autopurge
	obj->tflag = true;
	return 0;
}

float BallHandle::shooterPID(float setrpm, float kp, float ki, float kd,
	float dt, float merr) { // pid function for shooter
	
	
	float crpm = 60.0 / (48.0 * gtshoot.GetPeriod());
	//TODO set perr
	float dx; // change in x
	float out; // output value
	err1 = (setrpm - crpm) / setrpm; // calculate current error
	if (abs(err1) > merr) // if not within acceptable range
		integral = integral + err1 * dt; // adjust integral proportional to error
	dx = (err1 - perr); // calculate change in x
	out = pout + kp * err1 + ki * integral + kd * dx; // calculate out using PID formula
	out = (out > 1) ? 1 : out; // R = {y:yER,0<=y<=1}
	out = (out < 0) ? 0 : out; // R = {y:yER,0<=y<=1}
	pout = out;
	
	printf("%f: %f %f %f  %f\n", out, crpm, setrpm, err1 * setrpm, kp);
	perr = err1;
	return out; // gives fixed out value
}

void BallHandle::Init(Victor *shoot, Victor *feed, Victor *turret,
	Victor *elev, Victor *ballin, AnalogChannel *acballin, Joystick *right,
	Joystick *left, Joystick *manip) {
	this->shoot = false;
	bottom1 = false;
	bottom2 = false;
	middle = false;
	top = false;
	shootV = shoot;
	feedV = feed;
	conV = elev;
	intakeV = ballin;
	threaded = false;
	rightstick = right;
	leftstick = left;
	manipulatorstick = manip;
	this->ballin = acballin;
}

void BallHandle::CycleUp() {

}

void BallHandle::CycleDown() {

}

void BallHandle::Shoot() {
	if (!shoot)
		shoot = true;
}

float BallHandle::abs(float n) { // absolute function that supports floats
	return (n < 0) ? -n : n; // returns positive n
}

void BallHandle::VertPurge() { //TODO bind to button and tune
	shootV->Set(1.f);
	Wait(.5f);
	intakeV->Set(1.f);
	feedV->Set(-1.f);
	conV->Set(1.f); // is this right?
	Wait(5.f);
}

void BallHandle::Purge() {
	printf("Purging the dishwasher\n");
}

//first / no balls
//ball roller on if sensor, turn on the shaft
//once in, put that ball in first pos

//second balls
//ball roller on if sensor, turn on the shaft
//time
//first pos -> second pos

//third ball
//ball roller on if sensor, turn on the shaft
//time
//first pos -> second pos - third pos
//turn off roller

//after third
//ball roller reverse
//first pos -> second pos - third pos
