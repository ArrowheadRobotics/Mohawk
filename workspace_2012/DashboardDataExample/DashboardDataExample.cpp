#include "WPILib.h"

/**
 * This is a demo program showing the use of the Dashboard data packing class.
 */ 
class DashboardDataExample : public SimpleRobot
{
	Jaguar j1, j2, j3, j4;
public:
	DashboardDataExample(void)
	{
		GetWatchdog().SetExpiration(0.1);
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void RobotMain(void)
	{
		while(true) {
			
		}
	}
};

START_ROBOT_CLASS(DashboardDataExample);

