/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <SmartDashboard/SmartDashboard.h>
#include <SmartDashboard/SendableChooser.h>
#include <TimedRobot.h>

#include <string>
#include <thread>
#include <iostream>

#include <UserInput/UserInputTask.h>
#include <SensorInput/SensorInputTask.h>
#include <Controls/ControlsTask.h>
#include <Output/DriveOutputTask.h>

class Robot : public frc::TimedRobot
{
public:
    Robot();
    void RobotInit() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;

private:
    ControlsData RobotControlsData;
    DriveOutputData RobotDriveData;
    SensorInputData RobotSensorData;
    UserInputData RobotUserData;

    ControlsTask RobotControlsTask;
    DriveOutputTask RobotDriveTask;
    SensorInputTask RobotSensorTask;
    UserInputTask RobotUserTask;

    frc::SendableChooser<std::string> m_chooser;
    const std::string kAutoNameDefault = "Default";
    const std::string kAutoNameCustom = "My Auto";
    std::string m_autoSelected;
};
