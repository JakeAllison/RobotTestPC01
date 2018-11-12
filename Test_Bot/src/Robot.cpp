/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Robot.h>

Robot::Robot()
        : RobotControlsData()
        , RobotDriveData()
        , RobotSensorData()
        , RobotUserData()
        , RobotControlsTask(&RobotControlsData, &RobotDriveData, &RobotSensorData, &RobotUserData)
        , RobotDriveTask(&RobotControlsData, &RobotDriveData, &RobotSensorData, &RobotUserData)
        , RobotSensorTask(&RobotControlsData, &RobotDriveData, &RobotSensorData, &RobotUserData)
        , RobotUserTask(&RobotControlsData, &RobotDriveData, &RobotSensorData, &RobotUserData)
{

    RobotSensorTask.Start(50000);
    RobotUserTask.Start(50000);
    RobotControlsTask.Start(50000);
    RobotDriveTask.Start(50000);
}

void Robot::RobotInit()
{
    m_chooser.AddDefault(kAutoNameDefault, kAutoNameDefault);
    m_chooser.AddObject(kAutoNameCustom, kAutoNameCustom);
    frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

    SetPeriod(0.1);
}

void Robot::DisabledInit()
{}

void Robot::DisabledPeriodic()
{}

void Robot::AutonomousInit()
{
    m_autoSelected = m_chooser.GetSelected();
    // m_autoSelected = SmartDashboard::GetString("Auto Selector",
    //		 kAutoNameDefault);
    std::cout << "Auto selected: " << m_autoSelected << std::endl;

    if (m_autoSelected == kAutoNameCustom)
    {
        // Custom Auto goes here
    }
    else
    {
        // Default Auto goes here
    }
}

void Robot::AutonomousPeriodic()
{
    if (m_autoSelected == kAutoNameCustom)
    {
        // Custom Auto goes here
    }
    else
    {
        // Default Auto goes here
    }
}

void Robot::TeleopInit()
{}

void Robot::TeleopPeriodic()
{
    RobotControlsData.SendToSmartDashboard();
    RobotDriveData.SendToSmartDashboard();
    RobotSensorData.SendToSmartDashboard();
    RobotUserData.SendToSmartDashboard();
}

START_ROBOT_CLASS(Robot)
