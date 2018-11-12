/*
 * DriveOutputTask.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: Jake
 */

#include <Output/DriveOutputTask.h>
#include <SmartDashboard/SmartDashboard.h>

using namespace Global_Constants::Swerve_Drive;

namespace frc
{

DriveOutputTask::DriveOutputTask(ControlsData* ControlData, DriveOutputData* DriveData,
                                 SensorInputData* SensorData, UserInputData* UserData)
        : _controlsData(ControlData)
        , _driveData(DriveData)
        , _sensorData(SensorData)
        , _userData(UserData)
        , _driveSystem(_talons)
{

    _talons.insert(std::make_pair(FLDRIVEID, std::make_unique<can::TalonSRX>(kDRIVETALON_FL_DRIVE_ID)));
    _talons.insert(std::make_pair(FRDRIVEID, std::make_unique<can::TalonSRX>(kDRIVETALON_FR_DRIVE_ID)));
    _talons.insert(std::make_pair(BLDRIVEID, std::make_unique<can::TalonSRX>(kDRIVETALON_BL_DRIVE_ID)));
    _talons.insert(std::make_pair(BRDRIVEID, std::make_unique<can::TalonSRX>(kDRIVETALON_BR_DRIVE_ID)));

    _talons.insert(std::make_pair(FLROTID, std::make_unique<can::TalonSRX>(kDRIVETALON_FL_ROT_ID)));
    _talons.insert(std::make_pair(FRROTID, std::make_unique<can::TalonSRX>(kDRIVETALON_FR_ROT_ID)));
    _talons.insert(std::make_pair(BLROTID, std::make_unique<can::TalonSRX>(kDRIVETALON_BL_ROT_ID)));
    _talons.insert(std::make_pair(BRROTID, std::make_unique<can::TalonSRX>(kDRIVETALON_BR_ROT_ID)));

    ConfigureRotationMotors();
    ConfigureDriveMotors();
}

DriveOutputTask::~DriveOutputTask()
{
    // TODO Auto-generated destructor stub
}

/**
 * Configures the rotation motors to the correct parameters
 */
void DriveOutputTask::ConfigureRotationMotors()
{
    for (auto talonToConfigure : _talons)
    {
        // if we have a rotation motor
        if (talonToConfigure.first.find("Rotation") != std::string::npos)
        {
            talonToConfigure.second->ConfigSelectedFeedbackSensor(
                FeedbackDevice::CTRE_MagEncoder_Relative, 0, 10);
            talonToConfigure.second->SetSensorPhase(kSWERVE_ROT_PHASE);
            talonToConfigure.second->SetInverted(kSWERVE_ROT_INVERT);
            talonToConfigure.second->Config_kP(0, kSWERVE_ROT_P, 10);
            talonToConfigure.second->Config_kI(0, kSWERVE_ROT_I, 10);
            talonToConfigure.second->Config_kD(0, kSWERVE_ROT_D, 10);
            talonToConfigure.second->ConfigPeakOutputForward(kSWERVE_ROT_PEAKOUTPUT, 10);
            talonToConfigure.second->ConfigPeakOutputReverse(-kSWERVE_ROT_PEAKOUTPUT, 10);
            talonToConfigure.second->ConfigAllowableClosedloopError(
                0, kSWERVE_CLOSED_LOOP_TOLERANCE, 10);
            talonToConfigure.second->ConfigContinuousCurrentLimit(kSWERVE_CONT_AMPS, 10);
            talonToConfigure.second->ConfigPeakCurrentLimit(kSWERVE_PEAK_AMPS, 10);
            talonToConfigure.second->SetStatusFramePeriod(Status_2_Feedback0, 10, 0);
        }
    }
}

/**
 * Configures the drive motors to the correct parameters
 */
void DriveOutputTask::ConfigureDriveMotors()
{
    for (auto talonToConfigure : _talons)
    {
        if (talonToConfigure.first.find("Drive") != std::string::npos)
        {
            talonToConfigure.second->SetInverted(kSWERVE_DRIVE_INVERT);
            talonToConfigure.second->GetSensorCollection().SetQuadraturePosition(0, 10);
            talonToConfigure.second->ConfigSelectedFeedbackSensor(
                FeedbackDevice::QuadEncoder, 0, 10);
            talonToConfigure.second->SetSensorPhase(kSWERVE_DRIVE_PHASE);
            talonToConfigure.second->ConfigOpenloopRamp(kSWERVE_DRIVE_OPENLOOP_RAMP, 10);
            talonToConfigure.second->SetStatusFramePeriod(Status_2_Feedback0, 10, 0);
        }
    }
}

void DriveOutputTask::CalibrateWheels()
{

    for (auto talonToConfigure : _talons)
    {
        // if we have a rotation motor
        if (talonToConfigure.first.find("Rotation") != std::string::npos)
        {
            talonToConfigure.second->ConfigSelectedFeedbackSensor(
                FeedbackDevice::CTRE_MagEncoder_Relative, 0, 0);
        }
    }

    int flpw = _talons[FLROTID]->GetSensorCollection().GetPulseWidthPosition() & 0xFFF;
    int frpw = _talons[FRROTID]->GetSensorCollection().GetPulseWidthPosition() & 0xFFF;
    int blpw = _talons[BLROTID]->GetSensorCollection().GetPulseWidthPosition() & 0xFFF;
    int brpw = _talons[BRROTID]->GetSensorCollection().GetPulseWidthPosition() & 0xFFF;

    int flset = flpw - kDRIVEBASE_FL_CAL;
    int frset = frpw - kDRIVEBASE_FR_CAL;
    int blset = blpw - kDRIVEBASE_BL_CAL;
    int brset = brpw - kDRIVEBASE_BR_CAL;

    _talons[FLROTID]->Set(ControlMode::Position, flset);
    _talons[FRROTID]->Set(ControlMode::Position, frset);
    _talons[BLROTID]->Set(ControlMode::Position, blset);
    _talons[BRROTID]->Set(ControlMode::Position, brset);
}

void DriveOutputTask::ThreadTask()
{
    using namespace Global_Constants::ThreadData::ControlsData;
    using namespace Global_Constants::ThreadData::UserControl;
    using namespace Global_Constants::ThreadData::SensorData;

    double driveX, driveY, driveR = ControlOutputs::kDRIVE_OUT_DEFAULT;
    int overrideDriveMode = DriveModeOverride::kMODE_DEFAULT;
    double gyroAngle = SensorReadings::kGYRO_ANGLE_DEFAULT;

    // Get drive mode from user.
    _userData->GetData(DriveModeOverride::kDRIVE_O, overrideDriveMode);

    // Drive based on mode given.
    switch (overrideDriveMode)
    {
    case DriveModeOverride::kMODE_DISABLED:
        // Do nothing
        break;

    case DriveModeOverride::kMODE_NORMAL:
        // Get X, Y, and R outputs from the PID control system.
        _controlsData->GetData(ControlOutputs::kDRIVE_OUT_X, driveX);
        _controlsData->GetData(ControlOutputs::kDRIVE_OUT_Y, driveY);
        _controlsData->GetData(ControlOutputs::kDRIVE_OUT_R, driveR);
        break;

    case DriveModeOverride::kMODE_FIELD_ORIENTED:
        // Get X, Y, and R outputs from the PID control system.
        _controlsData->GetData(ControlOutputs::kDRIVE_OUT_X, driveX);
        _controlsData->GetData(ControlOutputs::kDRIVE_OUT_Y, driveY);
        _controlsData->GetData(ControlOutputs::kDRIVE_OUT_R, driveR);
        _sensorData->GetData(SensorReadings::kGYRO_ANGLE, gyroAngle);
        break;

    case DriveModeOverride::kMODE_LOCKUP:
        // DriveX and DriveY are zero.
        // Wheels will naturally turn to lockup position upon turning the robot.
        _controlsData->GetData(ControlOutputs::kDRIVE_OUT_R, driveR);
        break;

    default:
        // Do nothing
        break;
    }

    _driveSystem.DriveFieldOriented(driveX, driveY, driveR, gyroAngle);
}

} /* namespace frc */
