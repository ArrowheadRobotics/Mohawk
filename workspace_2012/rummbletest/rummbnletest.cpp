#include "WPILib.h"

/**
 * This is a demo program showing the use of the Gyro for driving in a straight
 * line. The Gyro object in the library returns the heading with 0.0 representing
 * straight and positive or negative angles in degrees for left and right turns.
 * The zero point is established when the gyro object is created so it is important
 * to have the robot still after turning it on.
 * 
 * If you are experiencing drift in the gyro, it can always be reset back to the
 * zero heading by calling Gyro.Reset().
 * 
 * Notice that there is no OperatorControl method. Since this program doesn't supply
 * one the default OperatorControl method will be called from the library.
 */
class Robo : public SimpleRobot
{
	//RobotDrive myRobot; // robot drive system
	//Gyro gyro;
	Victor shoot;

public:
	Robo(void):
		//myRobot(1, 2),		// initialize the sensors in initialization list
		//gyro(1)
		shoot(1)
	{
		//myRobot.SetExpiration(0.1);
	}

	
	void Autonomous(void)
	{
		//gyro.Reset();
		while (IsAutonomous())
		{
			//float angle = gyro.GetAngle();			// current heading (0 = target)
			//myRobot.Drive(-1.0, -angle / 30.0);		// proportionally drive in a straight line
			Wait(0.004);
		}
		//myRobot.Drive(0.0, 0.0); 	// stop robot
	}
	
	void OperatorControl(void)
	{
		//Joystick stick(1);
		
		DriverStationLCD *dsLCD;
		dsLCD = DriverStationLCD::GetInstance();
		
		while (IsOperatorControl())
		{
			//myRobot.ArcadeDrive(stick);
			
			dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "test");
			dsLCD->UpdateLCD();
			shoot.Set(.5);
			Wait(0.025);
		}
	}
};

START_ROBOT_CLASS(Robo);
