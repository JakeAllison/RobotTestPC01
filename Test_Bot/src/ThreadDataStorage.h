/*
 * ThreadDataStorage.h
 *
 *  Created on: Nov 11, 2018
 *      Author: Jake
 */

#ifndef SRC_THREADDATASTORAGE_H_
#define SRC_THREADDATASTORAGE_H_

#include <Controls/ControlsData.h>
#include <Output/DriveOutputData.h>
#include <SensorInput/SensorInputData.h>
#include <UserInput/UserInputData.h>

namespace frc
{

class ThreadDataStorage
{
public:
    ThreadDataStorage();
    virtual ~ThreadDataStorage();

    ControlsData* Get_ControlsData() { return &_controlsData; }
    DriveOutputData* Get_DriveOutputData() { return &_driveOutputData; }
    SensorInputData* Get_SensorInputData() { return &_sensorInputData; }
    UserInputData* Get_UserInputData() { return &_userInputData; }
private:
    static ControlsData _controlsData;
    static DriveOutputData _driveOutputData;
    static SensorInputData _sensorInputData;
    static UserInputData _userInputData;
};

} /* namespace frc */

#endif /* SRC_THREADDATASTORAGE_H_ */
