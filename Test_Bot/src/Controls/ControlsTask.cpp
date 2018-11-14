/*
 * ControlsTask.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: Jake
 */

#include <Controls/ControlsTask.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Vector>

namespace frc
{

ControlsTask::ControlsTask(ThreadDataContainer* threadData)
		: ThreadTaskBase(threadData)
        , _driveModeXPrev(Global_Constants::ThreadData::UserControl::DriveModes::kMODE_DEFAULT)
        , _driveModeYPrev(Global_Constants::ThreadData::UserControl::DriveModes::kMODE_DEFAULT)
        , _driveModeRPrev(Global_Constants::ThreadData::UserControl::DriveModes::kMODE_DEFAULT)
{

    using namespace Global_Constants::ThreadData::ControlsData;

    // Add all keys for controls data output.

    _threadData->_controlsData.AddKey<double>(ControlOutputs::kDRIVE_OUT_X);
    _threadData->_controlsData.AddKey<double>(ControlOutputs::kDRIVE_OUT_Y);
    _threadData->_controlsData.AddKey<double>(ControlOutputs::kDRIVE_OUT_R);
    _threadData->_controlsData.AddKey<double>(ControlOutputs::kDRIVE_OUT_R_DONE);

    // Set up PID controls.

    _GyroPID.Set_Multipliers(1.0, 0.2, 0.1);
    int gyroSetupErrorCode
    = _GyroPID.Set_Parameters(5.0, PID_Calc::PID_Control_Mode::kPIDControlModePositionControl,
                              1.0, 0.0, 45.0, 5.0, 0.1, true, 0.0, 360.0);

    frc::SmartDashboard::PutNumber("ControlsTaskSetup01", double(gyroSetupErrorCode));
}

ControlsTask::~ControlsTask()
{
    // TODO Auto-generated destructor stub
}

void ControlsTask::ThreadTask()
{
    using namespace Global_Constants::ThreadData::ControlsData;
    using namespace Global_Constants::ThreadData::UserControl;
    using namespace Global_Constants::ThreadData::SensorData;

    double driveX, driveY, driveR = ControlOutputs::kDRIVE_OUT_DEFAULT;
    int driveModeX, driveModeY, driveModeR = DriveModes::kMODE_DEFAULT;
    int driveDoneR = ControlOutputs::kDONE_VALUE_DEFAULT;

    double driveRCLDemand = OutputDemand::kDEMAND_DEFAULT;
    double gyroAngle = SensorReadings::kGYRO_ANGLE_DEFAULT;

    //-------------------------------------------------------
    // Get the drive modes for X, Y, and R.
    // Drive Modes are set to default values unless the input
    //     data contains allowable values.
    //-------------------------------------------------------

    _threadData->_userInputData.GetData(DriveModes::kDRIVE_X, driveModeX);
    _threadData->_userInputData.GetData(DriveModes::kDRIVE_Y, driveModeY);
    _threadData->_userInputData.GetData(DriveModes::kDRIVE_R, driveModeR);

    //-------------------------------------------------------
    // Select which inputs to use as the drive system inputs.
    // Drive outputs are set to a default value unless the
    //     input data contains allowable values.
    //-------------------------------------------------------

    switch (driveModeX)
    {
    case DriveModes::kMODE_OPEN_LOOP:
    	_threadData->_userInputData.GetData(OutputDemand::kX_DEMAND_OL, driveX);
        break;

    default:
        // Do nothing
        break;
    }

    switch (driveModeY)
    {
    case DriveModes::kMODE_OPEN_LOOP:
    	_threadData->_userInputData.GetData(OutputDemand::kY_DEMAND_OL, driveY);
        break;

    default:
        // Do nothing
        break;
    }

    switch (driveModeR)
    {
    case DriveModes::kMODE_OPEN_LOOP:
    	_threadData->_userInputData.GetData(OutputDemand::kR_DEMAND_OL, driveR);
        break;

    case DriveModes::kMODE_GYRO:
        if (_threadData->_userInputData.GetData(OutputDemand::kR_DEMAND_CL, driveRCLDemand)
                && _threadData->_sensorInputData.GetData(SensorReadings::kGYRO_ANGLE, gyroAngle))
        {
            driveRCLDemand *= 180;
            driveR = _GyroPID.Calc_PID(gyroAngle, driveRCLDemand, GetPeriod());

            if (_GyroPID.Is_Done(ControlOutputs::kDRIVE_OUT_R_SETTLING_TIME))
            {
                driveDoneR = ControlOutputs::kDONE_VALUE_DONE;
            }
            else
            {
                driveDoneR = ControlOutputs::kDONE_VALUE_NOT_DONE;
            }
        }
        break;

    default:
        // Do nothing
        break;
    }

    //-------------------------------------------------------
    // Set the output data for X, Y, and R.
    //-------------------------------------------------------

    _threadData->_controlsData.SetData(ControlOutputs::kDRIVE_OUT_X, driveX);
    _threadData->_controlsData.SetData(ControlOutputs::kDRIVE_OUT_Y, driveY);
    _threadData->_controlsData.SetData(ControlOutputs::kDRIVE_OUT_R, driveR);
    _threadData->_controlsData.SetData(ControlOutputs::kDRIVE_OUT_R_DONE, driveDoneR);

}

} /* namespace frc */
