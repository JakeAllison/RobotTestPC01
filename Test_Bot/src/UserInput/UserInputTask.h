/*
 * UserInputTask.h
 *
 *  Created on: Oct 24, 2018
 *      Author: Jake
 */

#ifndef USERINPUTTASK_H_
#define USERINPUTTASK_H_

#include <Controls/ControlsData.h>
#include <Output/DriveOutputData.h>
#include <SensorInput/SensorInputData.h>
#include <UserInput/UserInputData.h>

#include <ThreadBases/ThreadTaskBase.h>
#include <Utilities/TigerJoystick/TigerJoystick.h>
#include <RobotMap.h>
#include <Defines.h>

namespace frc
{

class UserInputTask : public ThreadTaskBase
{
public:
    UserInputTask(ThreadDataContainer* threadData);
    virtual ~UserInputTask();

private:
    void ThreadTask() override;

    // Declare private variables and inputs.
    // Nothing else will be really using these.

    TigerJoystick _driverJoystick;
    TigerJoystick _operatorJoystick;
};

} /* namespace frc */

#endif /* USERINPUTTASK_H_ */
