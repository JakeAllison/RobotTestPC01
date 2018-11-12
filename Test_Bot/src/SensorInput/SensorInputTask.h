/*
 * SensorInputTask.h
 *
 *  Created on: Oct 24, 2018
 *      Author: Jake
 */

#ifndef SRC_SENSORINPUTTASK_H_
#define SRC_SENSORINPUTTASK_H_

#include <Controls/ControlsData.h>
#include <Output/DriveOutputData.h>
#include <SensorInput/SensorInputData.h>
#include <UserInput/UserInputData.h>

#include <ThreadBases/ThreadTaskBase.h>
#include <RobotMap.h>
#include <Defines.h>

#include <AHRS.h>

namespace frc
{

class SensorInputTask : public ThreadTaskBase
{
public:
    SensorInputTask(ControlsData* ControlData, DriveOutputData* DriveData,
                    SensorInputData* SensorData, UserInputData* UserData);
    virtual ~SensorInputTask();

private:
    ControlsData* _controlsData;
    DriveOutputData* _driveData;
    SensorInputData* _sensorData;
    UserInputData* _userData;

    void ThreadTask() override;
    void ServiceRequests();

    // Declare private variables and sensors.
    AHRS _imu;
};

} /* namespace frc */

#endif /* SRC_SENSORINPUTTASK_H_ */