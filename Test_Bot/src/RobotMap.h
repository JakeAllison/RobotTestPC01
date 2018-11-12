/**
 * \file RobotMap.h
 * \brief Holds constants for the robot
 * \author Drew Williams
 *
 * Here we hold all of the robots constants.
 * These are the default values when the robot starts up.
 */

#ifndef _ROBOTMAP_H
#define _ROBOTMAP_H

#include <string>

namespace Global_Constants
{
namespace ThreadData
{
namespace UserControl
{
namespace ControllerPorts
{
constexpr int kDRIVER_CONTROLLER_PORT = 0;
constexpr int kOPERATOR_CONTROLLER_PORT = 1;
}
namespace OutputDemand
{
const std::string kX_DEMAND_OL = "kXDemandOL";
const std::string kY_DEMAND_OL = "kYDemandOL";
const std::string kR_DEMAND_OL = "kRDemandOL";
const std::string kX_DEMAND_CL = "kXDemandCL";
const std::string kY_DEMAND_CL = "kYDemandCL";
const std::string kR_DEMAND_CL = "kRDemandCL";

constexpr double kDEMAND_DEFAULT = 0.0;

constexpr double kOL_DEMAND_MAX = 1.0;
constexpr double kOL_DEMAND_MIN = -1.0;
}
namespace DriveModes
{
const std::string kDRIVE_X = "DriveModeX";
const std::string kDRIVE_Y = "DriveModeY";
const std::string kDRIVE_R = "DriveModeR";

constexpr int kMODE_DEFAULT = 0;
constexpr int kMODE_NONE = 0;
constexpr int kMODE_OPEN_LOOP = 1;
constexpr int kMODE_GYRO = 2;
}
namespace DriveModeOverride
{
const std::string kDRIVE_O = "DriveOverrideMode";

constexpr int kMODE_DEFAULT = 0;
constexpr int kMODE_DISABLED = 0;
constexpr int kMODE_NORMAL = 1;
constexpr int kMODE_FIELD_ORIENTED = 2;
constexpr int kMODE_LOCKUP = 3;
}
}
namespace SensorData
{
namespace SensorReadings
{
const std::string kGYRO_ANGLE = "GyroAngle";
const std::string kGYRO_RATE = "GyroRate";

constexpr double kGYRO_ANGLE_DEFAULT = 0.0;
constexpr double kGYRO_RATE_DEFAULT = 0.0;
}
/*
 namespace SensorPorts
 {
 
 }
 
 namespace SensorConversions
 {
 
 }
 */
}
namespace ControlsData
{
namespace ControlOutputs
{
const std::string kDRIVE_OUT_X = "DriveOutX";
const std::string kDRIVE_OUT_Y = "DriveOutY";
const std::string kDRIVE_OUT_R = "DriveOutR";

const std::string kDRIVE_OUT_R_DONE = "DriveOutRDone";

const std::string kDRIVE_VELOCITY_X = "DriveVelX";
const std::string kDRIVE_VELOCITY_Y = "DriveVelY";

constexpr double kDRIVE_OUT_DEFAULT = 0.0;
constexpr double kDRIVE_OUT_MAX = 1.0;
constexpr double kDRIVE_OUT_MIN = -1.0;

constexpr int kDONE_VALUE_DEFAULT = 0;
constexpr int kDONE_VALUE_NOT_DONE = 0;
constexpr int kDONE_VALUE_DONE = 1;

constexpr double kDRIVE_OUT_R_SETTLING_TIME = 0.25;
}
}
}

namespace Swerve_Drive
{
// STRING CONSTS
const std::string FLMODULEID = "FrontLeftModule";
const std::string FRMODULEID = "FrontRightModule";
const std::string BLMODULEID = "BackLeftModule";
const std::string BRMODULEID = "BackRightModule";

const std::string FLDRIVEID = "FrontLeftDrive";
const std::string FRDRIVEID = "FrontRightDrive";
const std::string BLDRIVEID = "BackLeftDrive";
const std::string BRDRIVEID = "BackRightDrive";

const std::string FLROTID = "FrontLeftRotation";
const std::string FRROTID = "FrontRightRotation";
const std::string BLROTID = "BackLeftRotation";
const std::string BRROTID = "BackRightRotation";

// DRIVEBASE CALIBRATION
constexpr int kDRIVEBASE_FL_CAL = 3015;
constexpr int kDRIVEBASE_BL_CAL = 2463;
constexpr int kDRIVEBASE_FR_CAL = 4030;
constexpr int kDRIVEBASE_BR_CAL = 579;
constexpr int kDRIVEBASE_TICKS_PER_REV = 4096;

// CONVERSION FACTORS
constexpr double kINCHESPERWEELREV = 7.85; // inches
constexpr int kTICKSPERREVOFENCODER = 8192;
constexpr int kENCODERREVPERWHEELREV = 3.2;

// DRIVEBASE ROTATION PARAMETERS
constexpr double kROTATION_P = .03;
constexpr double kROTATION_I = 0.0;
constexpr double kROTATION_D = .1;
constexpr double kROTATION_ANGLE_TOLERANCE = 2;
constexpr double kROTATION_RATE_MULTIPLIER = 0.05;

// DRIVEBASE PHYSICAL PARAMS
constexpr double kDRIVEBASE_WIDTH = 26.249; // inches
constexpr double kDRIVEBASE_LENGTH = 21; // inches

// DRIVEBASE TALONS
constexpr int kDRIVETALON_FL_DRIVE_ID = 2;
constexpr int kDRIVETALON_FR_DRIVE_ID = 3;
constexpr int kDRIVETALON_BL_DRIVE_ID = 4;
constexpr int kDRIVETALON_BR_DRIVE_ID = 5;
constexpr int kDRIVETALON_FL_ROT_ID = 6;
constexpr int kDRIVETALON_FR_ROT_ID = 7;
constexpr int kDRIVETALON_BL_ROT_ID = 8;
constexpr int kDRIVETALON_BR_ROT_ID = 9;

// SWERVE MODULE PARAMS
constexpr double kSWERVE_ROT_P = 12;
constexpr double kSWERVE_ROT_I = 0;
constexpr double kSWERVE_ROT_D = 120;
constexpr double kSWERVE_CLOSED_LOOP_TOLERANCE = 5;

// SWERVE CONFIG
constexpr double kSWERVE_ROT_PEAKOUTPUT = 1;
constexpr double kSWERVE_CONT_AMPS = 10;
constexpr double kSWERVE_PEAK_AMPS = 0;
constexpr double kSWERVE_DRIVE_OPENLOOP_RAMP = .4;
constexpr double kSWERVE_ROT_INVERT = true;
constexpr double kSWERVE_DRIVE_INVERT = false;
constexpr double kSWERVE_ROT_PHASE = false;
constexpr double kSWERVE_DRIVE_PHASE = true;

// FORWARD KINEMATICS
constexpr double kFORWARD_KINEMATICS_WEIGHT = 0;
constexpr double KGYRO_WEIGHT = 1;

// AUTO CONFIG
constexpr double kAUTO_P = .5;
constexpr double kAUTO_I = 0;
constexpr double kAUTO_D = 0;
constexpr double kAUTO_V = .06;
constexpr double kCONTROLLER_PERIOD = 0.05;
}
}
#endif
