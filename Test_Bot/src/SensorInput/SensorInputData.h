/*
 * SensorInputData.h
 *
 *  Created on: Oct 23, 2018
 *      Author: Jake
 */

#ifndef SRC_SENSORINPUT_SENSORINPUTDATA_H_
#define SRC_SENSORINPUT_SENSORINPUTDATA_H_

#include <ThreadBases/ThreadDataBase.h>
#include <condition_variable>
#include <Defines.h>

namespace frc
{

class SensorInputData : public ThreadDataBase
{
public:
    friend class SensorInputTask;
    SensorInputData();
    virtual ~SensorInputData();
    void ResetYaw(bool Blocking, unsigned int MaxBlockTimeUS);

private:
    bool _resetYawRequest = false;
};

} /* namespace frc */

#endif /* SRC_SENSORINPUT_SENSORINPUTDATA_H_ */
