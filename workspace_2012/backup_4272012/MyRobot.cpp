#include "MyRobot.h" // ADD INCLUDE FILES INTO MYROBOT.H, NOT HERE

/*TODO:
 * Ball handling in the chute should be in its own thread? Done?
 * 		-handle more than one ball at a time.  NATHAN
 * fully implement the autonomous.  Cory has wrote a structure.
 *		Check the structure for logical errors before starting
 * THREADS NEED TO BE REDUNDANT
 * 		-if the vision dies, the robot doesnt
 * 		-the ball hanflinging needs to be able to restart
 * Check for turbo mode in the helev
 * Alec please check the auto aim functions!
 * turret needs set points
 * read encoder values
 */

/*CHANGES MADE WITH OUT TESTING
 * Autonomous structure
 * TURBOMODE
 * AUTO AIM
 */

RobotDemo::RobotDemo(void) : jstick1(1), jstick2(2), jstick3(3), // init joysticks
							 cjleft1(1), cjleft2(2), cjright1(3), cjright2(4), // init canjaguars
							 sshifter1(1), sshifter2(2), stipper1(3), stipper2(4), shood1(5),shood2(6), 
							 shootV(7), feedV(2), turretV(3), conV(4), intakeV(5), // init solenoids
							 cpres(1, 1), acballin(1), acpot(2), 
							 helev(&shootV, &feedV, &turretV, &conV, &intakeV, &acballin, &jstick1, &jstick2, &jstick3)
							  { // GET RID OF THIS DSJFSAFHSAFJ
	sock = new RoboSock(); // creates new socket object
	cycles = 0;
	stopaim = false;
	aiming = false;
	turbo_mode = false;
	//SmartDashboard::Log(test, "testvalue"); // test call for smartdashboard -- ignore
}

void RobotDemo::Autonomous(void) {
	DriverStation *ds3 = DriverStation::GetInstance();
		int cycles = 0;
		DriverStationEnhancedIO &dseio = ds3->GetEnhancedIO();
	if(!ds3->GetDigitalIn(2))helev.hBangB(1.5f);
	if(!ds3->GetDigitalIn(4))helev.hBangB(7.5f);
	if(!ds3->GetDigitalIn(2)&&!ds3->GetDigitalIn(4)){
			intakeV.Set(1.0f);
			feedV.Set(0.0f);
			conV.Set(-1.0f); // is this right?
			Wait(3.0f);
		}
	else helev.hBangB(4.0f);
	conV.Set(-1.0f);//todo correct?
	Wait(.25); // todo tune
	conV.Set(0.0f);
	feedV.Set(-1.0f);// todo correct?
	Wait(.05f);
	conV.Set(1.0f);
	Wait(4.0f);
	conV.Set(0.0f);
	shootV.Set(0.0f);
	feedV.Set(0.0f);
	if(!ds3->GetDigitalIn(3)){
			cjleft1.EnableControl();
			cjleft2.EnableControl();
			cjright1.EnableControl();
			cjright2.EnableControl();
			//drive(-.5, -.5);
			Wait(.5);
			
	}
}//END OF AUTO

void RobotDemo::OperatorControl(void) {//initialization of op control
	//sock->initConn("10.7.6.5", 1180); // queries ip at port with connection until accepted
	cpres.Start();
	cycles = 0;
	DriverStationLCD *ds;
	ds = DriverStationLCD::GetInstance();
	cjleft1.EnableControl();
	cjleft2.EnableControl();
	cjright1.EnableControl();
	cjright2.EnableControl();
	helev.StartHandle();
	bool shiftlast = false, aimlast = false;
//DANGER
	DriverStation *ds2 = DriverStation::GetInstance();
		
		DriverStationEnhancedIO &dseio = ds2->GetEnhancedIO();
	//END DANGER
	bool run = false, blink = false;
	while(IsEnabled()) {
		//TODO put the turbo mode here
		//turbo_mode = dseio->GetDigital(1)); //what one is this
		
		cycles++;//TODO TUNE MOD
		
			//printf("%f\n",cjleft1.GetPosition());
		
		//CR added turbo mode
		if(ds2->GetDigitalIn(1)) Drive(S1Y, S2Y); // drive according to joystick's y values
		else{//TURBO MODE
			cjleft1.Set(S1Y);
			cjleft2.Set(S1Y);
			cjright1.Set(S2Y);
			cjright2.Set(S2Y);
		}
		//if((cycles % 15) == 0) printf("%f\n", sock->GetValue(RoboSock::ANGLE));
		
		if(S2TRIG ) {
			ctrlSolenoids(RobotDemo::SHIFTERS,false); // shift in
		}else	ctrlSolenoids(RobotDemo::SHIFTERS, true);
		
		if(S3B8) ctrlSolenoids(RobotDemo::HOOD,true);
		if(S3B9) ctrlSolenoids(RobotDemo::HOOD,false);
		
		if(S1TRIG) ctrlSolenoids(RobotDemo::TIPPERS, true); // tip in
		else ctrlSolenoids(RobotDemo::TIPPERS, false); // tip out
		
		if(S3TRIG) helev.Shoot();
		char buf[255];
		sprintf(buf, "%f", (jstick3.GetThrottle() * .1 + .59));
		ds->Printf(DriverStationLCD::kUser_Line1, 1, buf);
		float x = jstick3.GetThrottle();
		sprintf(buf, "%f", (-375.52*(x*x*x*x)+1257*(x*x*x)-1570.2*(x*x)+877.9*x-168.18));
		ds->Printf(DriverStationLCD::kUser_Line2, 1, buf);
		ds->UpdateLCD();
		helev.rpm = S3Z;
		//if(S3TRIG)
		//
		
		if(S3B4)helev.dpurge = true;
		else helev.dpurge = false;
				//TODO Check to vision overide
		if(S3B11 && !aimlast) {
			aimlast = true;
			SpawnAim();
		} else {
			aimlast = false;
			if(aiming) KillAim();
			turretV.Set(S3X);
		}
		Wait(.025f);
		
		//ball handeling
		// .6f good for slow
		
		
		/*if(S2B5) velev.Set(.6f); else velev.Set(0.f);		
		
		if(S2B3) vballin.Set(-1.f); else vballin.Set(0.f);*/
		
//		if(S3TRIG) vshoot.Set(shooterPID(S3Z,.1f,.005f,.01f,.01f,.1f));
//		else vshoot.Set(0);
//		velev.Set(S1Z);
//		vballin.Set(-S2Z);
//		vfeed.Set(-.9);
		//Wait(.05f); // Minimum wait time between motor transactions DO NOT REMOVE

	}
	helev.StopHandle();
	sock->Disconnect(); // disconnect from server
}

//void RobotDemo::Feed(){
//	
//	
//}

void RobotDemo::Drive(float left, float right) { // simplistic drive function TODO: revise?
	static float left_old = 0;
	static float right_old = 0;
	float leftvalue = 0;
	float rightvalue = 0;
	
	const float k0 = .25, k1 = -.5, k2 = 2, k3 = 2; //k2=forward base, k3=backward base
	
	if (left < 0) {//forward
		if (abs(left_old - left) > k0)
			leftvalue = k1 * left;
		else
			leftvalue = ((2 / k2) * (pow(k2, left) - 1));//both must be equal
	
	} else
		leftvalue = ((1 / k3) * (pow(k3, left) - 1));
	
	if (right < 0) {//forward
		if (abs(right_old - right) > k0)
			rightvalue = k1 * right;
		else
			rightvalue = ((2 / k2) * (pow(k2, right) - 1));//both must equal
	
	} else
		rightvalue = ((1 / k3) * (pow(k3, right) - 1));
	
	left_old = left;
	right_old = right;
	
	cjleft1.Set(leftvalue); // sets first canjaguar on left to passed left value
	cjleft2.Set(leftvalue); // sets second canjaguar on left to passed left value
	cjright1.Set(rightvalue); // sets first canjaguar on right to passed right value
	cjright2.Set(rightvalue); // sets second canjaguar on right to passed right value
}

void RobotDemo::ctrlSolenoids(Solenoids s, bool value) { // handles solenoids
	if(s == RobotDemo::SHIFTERS) { // if querying shifters
		sshifter1.Set(value); // set left shifter
		sshifter2.Set(!value); // set right shifter
	} else if(s == RobotDemo::TIPPERS) { // if querying tippers
		stipper1.Set(value); // set left tipper
		stipper2.Set(!value); // set right tipper
	} else {
		shood1.Set(value);
		shood2.Set(!value);
	}
	
}

float RobotDemo::rotateP(float set_value){
	//TODO SET THESE THINGS TO 360 DEGREES BASE ON VOLTAGE - cory
	//TODO OVER LIMIT, UNDER LIMIT
	if(acpot.GetVoltage()>set_value+10) turretV.Set(.5);//over set
	else if(acpot.GetVoltage()<set_value-10) turretV.Set(-.5);//under set
	else turretV.Set(0);//band pass
	return 0.f;
}

void RobotDemo::Halt(void) { // stop robot on dime
	cjleft1.Set(0); // stop left canjaguar one
	cjleft2.Set(0); // stop left canjaguar two
	cjright1.Set(0); // stop right canjaguar one
	cjright2.Set(0); // stop right canjaguar two
}

void RobotDemo::SpawnAim() {
	if(!aiming) {
		aiming = true;
		pthread_t aim;
		pthread_create(&aim, NULL, Auto_aim, (void *)this);
	}
}

void RobotDemo::KillAim() {
	if(aiming) {
		aiming = false;
		stopaim = false;
		sock->emergencystop = true;
	}
}

void RobotDemo::KillRecv() {  //kills receving
	if(aiming) {
		sock->emergencystop = true;
	}
}

float RobotDemo::abs(float n) { // absolute function that supports floats
	return (n<0)?-n:n; // returns positive n
}

void *RobotDemo::Auto_aim(void *arg){
	RobotDemo *robit = (RobotDemo *)arg;
	
	static float angle = 340;
	static float distance = 1;
	while(!robit->stopaim) {
		if((robit->cycles % 10) == 0) {//TODO WHAT IS THIS?  ALEC
			angle = robit->sock->GetValue(RoboSock::ANGLE);
			distance = robit->sock->GetValue(RoboSock::DIST);
		}
		//printf("%f\n", angle);
		if(angle == -1) {
			printf("ERROR IN SOCKETS>>>>>NEGATIVE 1\n");//Negative 1 is the error code	
		}else{
			printf("IM ACTUALLY MOVING!\n");
			if(angle>380){ //level three tune. DONT USE!  USE PID
				//robit->vturret.Set(-.3f);
				printf("TURNING LEFT AT %f WITH %f FT\n",angle,distance);
			}//TODO CORRECT DIRECTION?
			else if(angle<300) {
				//robit->vturret.Set(.3f);
				printf("TURNING RIGHT AT %f WITH %f FT\n",angle,distance);
			} else {
				printf("IM HERE AT %f WITH %f FT/n",angle,distance);
				//robit->vturret.Set(0);
			}			
		}
	}
	return (void *)0;
} 

START_ROBOT_CLASS(RobotDemo);
