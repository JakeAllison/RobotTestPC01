/*
 * SensorInputData.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: Jake
 */

#include <SensorInput/SensorInputData.h>
#include <SmartDashboard/SmartDashboard.h>

namespace frc
{

SensorInputData::SensorInputData()
{
    // TODO Auto-generated constructor stub
}

SensorInputData::~SensorInputData()
{
    // TODO Auto-generated destructor stub
}

void SensorInputData::ResetYaw(bool Blocking, unsigned int MaxBlockTimeUS)
{
    std::unique_lock<std::mutex> lck(mtxNotifier);

    //----------------------------------------------------------
    serviceGuard.lock();

    _resetYawRequest = true;

    serviceGuard.unlock();
    //----------------------------------------------------------

    if (Blocking)
    {
        if (MaxBlockTimeUS > 0)
        {
            conditionWait.wait_for(lck, std::chrono::microseconds(MaxBlockTimeUS));
        }
        else
        {
            conditionWait.wait(lck);
        }
    }
}

} /* namespace frc */
