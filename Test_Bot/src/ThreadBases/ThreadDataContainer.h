/*
 * ThreadDataContainer.h
 *
 *  Created on: Nov 12, 2018
 *      Author: Jake
 */

#ifndef THREADBASES_THREADDATACONTAINER_H_
#define THREADBASES_THREADDATACONTAINER_H_

#include <Controls/ControlsData.h>
#include <Output/DriveOutputData.h>
#include <SensorInput/SensorInputData.h>
#include <UserInput/UserInputData.h>

namespace frc {

class ThreadDataContainer {
public:
    ThreadDataContainer();
    virtual ~ThreadDataContainer();

    ControlsData _controlsData;
    DriveOutputData _driveOutputData;
    SensorInputData _sensorInputData;
    UserInputData _userInputData;
};

} /* namespace frc */

#endif /* THREADBASES_THREADDATACONTAINER_H_ */
