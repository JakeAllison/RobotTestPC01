/*
 * SensorInputTask.cpp
 *
 *  Created on: Oct 24, 2018
 *      Author: Jake
 */

#include <SensorInput/SensorInputTask.h>
#include <SmartDashboard/SmartDashboard.h>

namespace frc
{

SensorInputTask::SensorInputTask(ControlsData* ControlData, DriveOutputData* DriveData,
                                 SensorInputData* SensorData, UserInputData* UserData)
        : _controlsData(ControlData)
        , _driveData(DriveData)
        , _sensorData(SensorData)
        , _userData(UserData)
        , _imu(frc::SPI::Port::kMXP)
{
    using namespace Global_Constants::ThreadData::SensorData;

    _sensorData->AddKey<double>(SensorReadings::kGYRO_ANGLE);
    _sensorData->AddKey<double>(SensorReadings::kGYRO_RATE);

    _imu.ZeroYaw();
}

SensorInputTask::~SensorInputTask()
{
    // TODO Auto-generated destructor stub
}

void SensorInputTask::ServiceRequests()
{
    std::unique_lock<std::mutex> lck(_sensorData->mtxNotifier);
    //----------------------------------------------------------
    _sensorData->serviceGuard.lock();

    bool temp1 = _sensorData->_resetYawRequest;

    _sensorData->serviceGuard.unlock();
    //----------------------------------------------------------

    // Service the "Yaw Reset" request.
    if (temp1)
    {
        _imu.ZeroYaw();
    }

    //----------------------------------------------------------
    _sensorData->serviceGuard.lock();

    // We do this to avoid resetting the flag in case a request was made
    // since servicing was started.
    if (temp1)
    {
        _sensorData->_resetYawRequest = false;
    }

    _sensorData->serviceGuard.unlock();
    //----------------------------------------------------------

    _sensorData->conditionWait.notify_all();
}

void SensorInputTask::ThreadTask()
{
    ServiceRequests();
    using namespace Global_Constants::ThreadData::SensorData;
    _sensorData->SetData(SensorReadings::kGYRO_ANGLE, double(_imu.GetYaw()));
    _sensorData->SetData(SensorReadings::kGYRO_RATE, _imu.GetRate());
}

} /* namespace frc */
