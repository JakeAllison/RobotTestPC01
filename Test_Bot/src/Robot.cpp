/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Robot.h>

Robot::Robot()
        : _threadDataContainer()
        , _controlsTask(&_threadDataContainer)
        , _driveOutputTask(&_threadDataContainer)
        , _sensorInputTask(&_threadDataContainer)
        , _userInputTask(&_threadDataContainer)
{
	// 200 hz rate
    _sensorInputTask.Start(50000);
    _userInputTask.Start(50000);
    _controlsTask.Start(50000);
    _driveOutputTask.Start(50000);
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
    _threadDataContainer._controlsData.PrintData();
    _threadDataContainer._driveOutputData.PrintData();
    _threadDataContainer._sensorInputData.PrintData();
    _threadDataContainer._userInputData.PrintData();
}

START_ROBOT_CLASS(Robot)
