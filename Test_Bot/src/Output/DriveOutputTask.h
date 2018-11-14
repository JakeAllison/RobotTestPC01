/*
 * DriveOutputTask.h
 *
 *  Created on: Oct 24, 2018
 *      Author: Jake
 */

#ifndef SRC_OUTPUT_DRIVEOUTPUTTASK_H_
#define SRC_OUTPUT_DRIVEOUTPUTTASK_H_

#include <ThreadBases/ThreadTaskBase.h>
#include <Utilities/TigerSwerve/TigerSwerve.h>
#include <RobotMap.h>
#include <Defines.h>

namespace frc
{

class DriveOutputTask : public ThreadTaskBase
{
public:
    DriveOutputTask(ThreadDataContainer* threadData);
    virtual ~DriveOutputTask();

private:
    void ThreadTask() override;
    void ConfigureRotationMotors();
    void ConfigureDriveMotors();
    void CalibrateWheels();

    std::unordered_map<std::string, std::shared_ptr<can::TalonSRX>> _talons;
    TigerSwerve _driveSystem;
};

} /* namespace frc */

#endif /* SRC_OUTPUT_DRIVEOUTPUTTASK_H_ */
