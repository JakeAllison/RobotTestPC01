/*
 * DriveOutputTask.h
 *
 *  Created on: Oct 24, 2018
 *      Author: Jake
 */

#ifndef SRC_OUTPUT_DRIVEOUTPUTTASK_H_
#define SRC_OUTPUT_DRIVEOUTPUTTASK_H_

#include <Controls/ControlsData.h>
#include <Output/DriveOutputData.h>
#include <SensorInput/SensorInputData.h>
#include <UserInput/UserInputData.h>

#include <ThreadBases/ThreadTaskBase.h>
#include <Utilities/TigerSwerve/TigerSwerve.h>
#include <RobotMap.h>
#include <Defines.h>

namespace frc
{

class DriveOutputTask : public ThreadTaskBase
{
public:
    DriveOutputTask(ControlsData* ControlData, DriveOutputData* DriveData,
                    SensorInputData* SensorData, UserInputData* UserData);
    virtual ~DriveOutputTask();

private:
    ControlsData* _controlsData;
    DriveOutputData* _driveData;
    SensorInputData* _sensorData;
    UserInputData* _userData;

    void ThreadTask() override;
    void ConfigureRotationMotors();
    void ConfigureDriveMotors();
    void CalibrateWheels();

    std::unordered_map<std::string, std::shared_ptr<can::TalonSRX>> _talons;
    TigerSwerve _driveSystem;
};

} /* namespace frc */

#endif /* SRC_OUTPUT_DRIVEOUTPUTTASK_H_ */
