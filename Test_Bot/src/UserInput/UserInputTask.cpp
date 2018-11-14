/*
 * UserInputTask.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: Jake
 */

#include <UserInput/UserInputTask.h>
#include <SmartDashboard/SmartDashboard.h>

namespace frc
{

UserInputTask::UserInputTask(ThreadDataContainer* threadData)
: ThreadTaskBase(threadData)
        , _driverJoystick(Global_Constants::ThreadData::UserControl::ControllerPorts::kDRIVER_CONTROLLER_PORT)
        , _operatorJoystick(Global_Constants::ThreadData::UserControl::ControllerPorts::kOPERATOR_CONTROLLER_PORT)
{

    // Create keys for data output.

    using namespace Global_Constants::ThreadData::UserControl;

    _threadData->_userInputData.AddKey<int>(DriveModeOverride::kDRIVE_O);
    _threadData->_userInputData.AddKey<int>(DriveModes::kDRIVE_X);
    _threadData->_userInputData.AddKey<int>(DriveModes::kDRIVE_Y);
    _threadData->_userInputData.AddKey<int>(DriveModes::kDRIVE_R);

    _threadData->_userInputData.AddKey<double>(OutputDemand::kX_DEMAND_OL);
    _threadData->_userInputData.AddKey<double>(OutputDemand::kY_DEMAND_OL);
    _threadData->_userInputData.AddKey<double>(OutputDemand::kR_DEMAND_OL);
    _threadData->_userInputData.AddKey<double>(OutputDemand::kX_DEMAND_CL);
    _threadData->_userInputData.AddKey<double>(OutputDemand::kY_DEMAND_CL);
    _threadData->_userInputData.AddKey<double>(OutputDemand::kR_DEMAND_CL);
}

UserInputTask::~UserInputTask()
{
    // TODO Auto-generated destructor stub
}

void UserInputTask::ThreadTask()
{

    /**
     * Select the drive modes to be used.
     * Common controls are open loop / joystick, encoders, gyro, and camera tracking.
     */

    using namespace Global_Constants::ThreadData::UserControl;

    // Select overriding drive mode (normal, field-oriented, lockup)
    // The override mode persists even when this is not set.

    if (_driverJoystick.bButton.get()->Get())
    {
        _threadData->_userInputData.SetData(DriveModeOverride::kDRIVE_O, DriveModeOverride::kMODE_FIELD_ORIENTED);
    }
    else if (_operatorJoystick.bButton.get()->Get())
    {
        _threadData->_userInputData.SetData(DriveModeOverride::kDRIVE_O, DriveModeOverride::kMODE_FIELD_ORIENTED);
    }
    else if (_driverJoystick.aButton.get()->Get())
    {
        _threadData->_userInputData.SetData(DriveModeOverride::kDRIVE_O, DriveModeOverride::kMODE_NORMAL);
    }
    else if (_operatorJoystick.aButton.get()->Get())
    {
        _threadData->_userInputData.SetData(DriveModeOverride::kDRIVE_O, DriveModeOverride::kMODE_NORMAL);
    }

    // Choose source of X and Y demand.
    // This must be held for the operator to take over.

    if (_operatorJoystick.leftStickButton.get()->Get())
    {
        _threadData->_userInputData.SetData(OutputDemand::kX_DEMAND_OL, _operatorJoystick.GetLeftXAxis());
        _threadData->_userInputData.SetData(OutputDemand::kY_DEMAND_OL, _operatorJoystick.GetLeftYAxis());
    }
    else
    {
        _threadData->_userInputData.SetData(OutputDemand::kX_DEMAND_OL, _driverJoystick.GetLeftXAxis());
        _threadData->_userInputData.SetData(OutputDemand::kY_DEMAND_OL, _driverJoystick.GetLeftXAxis());
    }

    // Choose source of R demand.
    // This must be held for the operator to take over.

    if (_operatorJoystick.rightStickButton.get()->Get())
    {
        _threadData->_userInputData.SetData(OutputDemand::kR_DEMAND_OL, _operatorJoystick.GetRightXAxis());
        _threadData->_userInputData.SetData(OutputDemand::kR_DEMAND_CL, _operatorJoystick.GetRightXAxis() * 180.0);
    }
    else
    {
        _threadData->_userInputData.SetData(OutputDemand::kR_DEMAND_OL, _driverJoystick.GetRightXAxis());
        _threadData->_userInputData.SetData(OutputDemand::kR_DEMAND_CL, _operatorJoystick.GetRightXAxis() * 180.0);
    }

    // Choose what sensor to use to turn the robot.
    // Holding no buttons defaults to open-loop control.
    // If either user presses "leftShoulder", then the robot will use the gyro to face a selected
    // heading.
    if (_driverJoystick.leftShoulderButton.get()->Get())
    {
        _threadData->_userInputData.SetData(DriveModes::kDRIVE_R, DriveModes::kMODE_GYRO);
    }
    else if (_operatorJoystick.leftShoulderButton.get()->Get())
    {
        _threadData->_userInputData.SetData(DriveModes::kDRIVE_R, DriveModes::kMODE_GYRO);
    }
    else
    {
        _threadData->_userInputData.SetData(DriveModes::kDRIVE_R, DriveModes::kMODE_OPEN_LOOP);
    }

    // Call a service request to reset IMU yaw when "Y" is pressed.
    // The current parameters are non-blocking.
    if (_driverJoystick.yButton.get()->Get())
    {
        _threadData->_sensorInputData.ResetYaw(false, 0);
    }
    else if (_operatorJoystick.yButton.get()->Get())
    {
        _threadData->_sensorInputData.ResetYaw(false, 0);
    }
}

} /* namespace frc */
