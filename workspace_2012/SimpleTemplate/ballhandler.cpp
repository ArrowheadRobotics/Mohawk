#include "ballhandler.h"

//handle the position of the balls. We need to provide functions for cycling upwards, downards
//provide led on dash
//WE NEED TO DO THIS BY RECIEVED DATA / STATES, not a theoretical array of ball positions
//todo motor safety, too many counts on high, stop them until a button pressed

BallHandle::BallHandle(Victor *shoot, Victor *feed, Victor *turret,
		Victor *elev, Victor *ballin, AnalogChannel *acballin, Joystick *right,
		Joystick *left, Joystick *manip) :
	s_bottom(9), /*s_middle(13),*/s_top(3)/*TODO GET THIS TO BE RIGHT*/,
			s_intake(14), gtshoot(5) {
	//err =0;
	perr = 0; // static error
	integral = 0; // static integral
	pout = 0; //static output
	err1 = 0;
	gtshoot.Start();
	dpurge = false;
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

void *BallHandle::hBang(void *arg) {
	BallHandle *obj = (BallHandle *) arg;	
	float new_time;  //current timer
	Timer t;
	t.Start();
	obj->gtshoot.Start();
	int counts;  //geartooth counter
	float shooter_rpm, pshooter_rpm = 0, filter_rpm = 0;  //current rpm, previous rpm, running average rpm
	float prev_time = 1;  //previous timer
	int target_rpm = 3000;  //goal
	float krpm = 0.04;  //constant used with filter
	float new_motor_cmd, prev_motor_cmd = 0;  //motor output, previous motor output
	float max_delta = 1.f;  //maximum change
	int cycle = 0;
	DriverStation *ds4 = DriverStation::GetInstance();
	DriverStationEnhancedIO &dseio = ds4->GetEnhancedIO();
	while (obj->tflag) {
		if(!ds4->GetDigitalIn(5))target_rpm = 9000; // max it out
		else target_rpm = 3000;  
		//krpm = obj->manipulatorstick->GetThrottle();  //constant used with filter
		t.Reset();
		counts = obj->gtshoot.Get();  //get geartooth value
		shooter_rpm = (60.0f/48.0f)*(1/obj->gtshoot.GetPeriod());  //current rpm equation  48 gears per rotations
		if(counts<100) shooter_rpm = 0;
		filter_rpm = krpm*filter_rpm + (1-krpm)*shooter_rpm;  //average of previous filter and current rpms
		if(filter_rpm>=target_rpm)new_motor_cmd=0.0f;  //if filter (lags slightly) is above goal, stop the motor
		else new_motor_cmd =1.0f;  //otherwise keep going
		if(new_motor_cmd > prev_motor_cmd + max_delta) new_motor_cmd = prev_motor_cmd + max_delta;  //maximum change possible -- useless now
		//printf("%f | %f | %f | %f | %d\n",shooter_rpm,filter_rpm,new_motor_cmd,target_rpm-shooter_rpm,counts);
		prev_motor_cmd = new_motor_cmd;  //reset variables
		pshooter_rpm = shooter_rpm;
		obj->shootV->Set(new_motor_cmd);  //set the motor
		//printf("%f %f %f\n",t.Get(),target_rpm-shooter_rpm,krpm);
		Wait(0.02);
	}
	obj->tflag = true;
	return 0;
}

void BallHandle::hBangB(double wait) {	
	autonomous = true;
	float new_time;  //current timer
	Timer t;
	t.Start();
	gtshoot.Start();
	int counts;  //geartooth counter
	float shooter_rpm, pshooter_rpm = 0, filter_rpm = 0;  //current rpm, previous rpm, running average rpm
	float prev_time = 1;  //previous timer
	int target_rpm = 3000;  //goal
	float krpm = 0.04;  //constant used with filter
	float new_motor_cmd, prev_motor_cmd = 0;  //motor output, previous motor output
	float max_delta = 1.f;  //maximum change
	int cycle = 0;
	while (t.Get() < wait) {
		counts = gtshoot.Get();  //get geartooth value
		shooter_rpm = (60.0f/48.0f)*(1/gtshoot.GetPeriod());  //current rpm equation  48 gears per rotations
		if(counts<100) shooter_rpm = 0;
		filter_rpm = krpm*filter_rpm + (1-krpm)*shooter_rpm;  //average of previous filter and current rpms
		if(filter_rpm>=target_rpm)new_motor_cmd=0.0f;  //if filter (lags slightly) is above goal, stop the motor
		else new_motor_cmd =1.0f;  //otherwise keep going
		if(new_motor_cmd > prev_motor_cmd + max_delta) new_motor_cmd = prev_motor_cmd + max_delta;  //maximum change possible -- useless now
		//printf("%f | %f | %f | %f | %d\n",shooter_rpm,filter_rpm,new_motor_cmd,target_rpm-shooter_rpm,counts);
		prev_motor_cmd = new_motor_cmd;  //reset variables
		pshooter_rpm = shooter_rpm;
		shootV->Set(new_motor_cmd);  //set the motor
		Wait(0.02);
	}
	return;
}

void *BallHandle::hQueue(void *arg) {
	BallHandle *obj = (BallHandle *) arg;
	pthread_t handler;
	pthread_create(&handler, NULL, obj->hBang, arg);
	obj->intakeV->Set(-.25f);	//suck ball in	
	/*
		// turretV is on pwm3
		if(S1B3){
			tole = !tole;
		}  //+
		if (!tole) {
			turretV.Set(PID(S1Z*4000));
		} else {
			turretV.Set(S1Z);
		}
		Wait(.05f);
	 */
	DriverStation *dsl = DriverStation::GetInstance();
	int cycles = 0;
	DriverStationEnhancedIO &dseio = dsl->GetEnhancedIO();
	bool run = false;
	bool intakeB;
	bool topB;
	bool shootB;
	Timer t;
	while (obj->tflag) {
		/*if(dseio.GetDigital(2)) {
			//printf("top: \n");
		}*/
		//printf("top: %i\nintake: %i\nbottom: %i\n", obj->s_top.Get(), obj->s_intake.Get(), obj->s_bottom.Get());
		if(cycles % 20 ==0 ){
			if(obj->s_top.Get()) dseio.SetDigitalOutput(9,true);
						else dseio.SetDigitalOutput(9,false);
			if(obj->s_bottom.Get()) dseio.SetDigitalOutput(11,true);
						else dseio.SetDigitalOutput(11,false);
		}
		if(cycles % 100 == 0){
			if(dseio.GetDigital(1)) dseio.SetDigitalOutput(13,true);
			else dseio.SetDigitalOutput(13,false);
		}
		cycles++;
		
		if(!obj->s_top.Get()) 
			obj->intakeV->Set(.25f);	//suck ball in NOT if top sw sensed
		else
			obj->intakeV->Set(-.25f);	//suck ball in
		//printf("hey %d %d %d\n",obj->s_intake.Get(),obj->s_top.Get(),obj->shoot);
		intakeB = true;
		for(int i=0;i<5;i++) {
			if(obj->s_intake.Get()) {
				intakeB = false;
				break;
			}
			Wait(.001f);
		}
		if ((intakeB and obj->s_top.Get()) and !obj->shoot) {
			printf("hi %d %d %d\n",obj->s_intake.Get(),obj->s_top.Get(),obj->shoot);
			obj->conV->Set(.35);

			obj->intakeV->Set(-1);  //suck ball in
			t.Stop();
			t.Reset();
			t.Start();
			while (obj->s_bottom.Get()  || obj->s_top.Get()){
				if(t.Get()>.5)break;
			}
			while (!obj->s_bottom.Get() || obj->s_top.Get()){
				if(t.Get()>1) break;
			}
			t.Reset();
			
			//Wait(.5); //Todo tune
			//printf("3\n");
			/*
			bool bumval = !obj->s_bottom.Get();
			bool topval = !obj->s_top.Get();
			
			while (!obj->bumval) {  //bottom switch
				printf("step1");
				if (obj->rightstick->GetRawButton(3))
					break;

				bumval = !obj->s_bottom.Get();
				topval = !obj->s_top.Get();
				//							if(s_top.Get()) intakeV.Set(1);
				//			 				else intakeV.Set(-1);
				//							printf("orbiting: %d %d %d\n",s_intake.Get(),s_bottom.Get(),s_top.Get());
			}	
			*/		
			obj->conV->Set(0);
		}			
		
		while(obj->dpurge){
			obj->VertPurge();
		}
		
		
		if(obj->shoot) {
			obj->shoot = 1;
			obj->conV->Set(-1);//todo correct?
			Wait(.25); // todo tune
			obj->conV->Set(0);
	
			obj->feedV->Set(-1);// todo correct?
			while (obj->manipulatorstick->GetTop()) {
				printf("step2");
				if (obj->rightstick->GetRawButton(3))
					break;
				obj->conV->Set(0);
			}
			obj->conV->Set(.25);//todo correct
			while (obj->manipulatorstick->GetTrigger()) {
				printf("step3");
				if (obj->rightstick->GetRawButton(3))
					break;
				Wait(.05);
				while (obj->manipulatorstick->GetTop()) {
					printf("step4");
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
		//Wait(.1f);
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
	
	//printf("%f: %f %f %f  %f\n", out, crpm, setrpm, err1 * setrpm, kp);
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
	Wait(.5f);
	intakeV->Set(1.f);
	feedV->Set(0.f);
	conV->Set(-1.f); // is this right?
	Wait(5.f);
}

void BallHandle::Purge() {
	conV->Set(1);//todo correct
	feedV->Set(-1);
	intakeV->Set(-1);
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
