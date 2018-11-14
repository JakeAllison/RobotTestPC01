/*
 * ControlsTask.h
 *
 *  Created on: Oct 23, 2018
 *      Author: Jake
 */

#ifndef SRC_CONTROLSTASK_H_
#define SRC_CONTROLSTASK_H_

#include <Controls/ControlsData.h>
#include <Output/DriveOutputData.h>
#include <SensorInput/SensorInputData.h>
#include <UserInput/UserInputData.h>

#include <ThreadBases/ThreadTaskBase.h>
#include <Controls/PID.h>
#include <RobotMap.h>
#include <Defines.h>

namespace frc
{

class ControlsTask : public ThreadTaskBase
{
public:
    ControlsTask(ThreadDataContainer* threadData);
    virtual ~ControlsTask();

private:
    void ThreadTask() override;

    PID_Calc _GyroPID;
    int _driveModeXPrev;
    int _driveModeYPrev;
    int _driveModeRPrev;
};

} /* namespace frc */

#endif /* SRC_CONTROLSTASK_H_ */
