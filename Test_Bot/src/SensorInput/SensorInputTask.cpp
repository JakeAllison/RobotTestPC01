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

SensorInputTask::SensorInputTask(ThreadDataContainer* threadData)
: ThreadTaskBase(threadData)
        , _imu(frc::SPI::Port::kMXP)
{
    using namespace Global_Constants::ThreadData::SensorData;

    _threadData->_sensorInputData.AddKey<double>(SensorReadings::kGYRO_ANGLE);
    _threadData->_sensorInputData.AddKey<double>(SensorReadings::kGYRO_RATE);

    _imu.ZeroYaw();
}

SensorInputTask::~SensorInputTask()
{
    // TODO Auto-generated destructor stub
}

void SensorInputTask::ServiceRequests()
{
    std::unique_lock<std::mutex> lck(_threadData->_sensorInputData.mtxNotifier);
    //----------------------------------------------------------
    _threadData->_sensorInputData.serviceGuard.lock();

    bool temp1 = _threadData->_sensorInputData._resetYawRequest;

    _threadData->_sensorInputData.serviceGuard.unlock();
    //----------------------------------------------------------

    // Service the "Yaw Reset" request.
    if (temp1)
    {
        _imu.ZeroYaw();
    }

    //----------------------------------------------------------
    _threadData->_sensorInputData.serviceGuard.lock();

    // We do this to avoid resetting the flag in case a request was made
    // since servicing was started.
    if (temp1)
    {
        _threadData->_sensorInputData._resetYawRequest = false;
    }

    _threadData->_sensorInputData.serviceGuard.unlock();
    //----------------------------------------------------------

    _threadData->_sensorInputData.conditionWait.notify_all();
}

void SensorInputTask::ThreadTask()
{
    ServiceRequests();
    using namespace Global_Constants::ThreadData::SensorData;
    _threadData->_sensorInputData.SetData(SensorReadings::kGYRO_ANGLE, double(_imu.GetYaw()));
    _threadData->_sensorInputData.SetData(SensorReadings::kGYRO_RATE, _imu.GetRate());
}

} /* namespace frc */
