/*
 * ThreadTaskBase.h
 *
 *  Created on: Oct 23, 2018
 *      Author: Jake
 */

#ifndef SRC_THREADTASKBASE_H_
#define SRC_THREADTASKBASE_H_

#include <thread>
#include <mutex>
#include <condition_variable>
#include <Defines.h>

namespace frc
{

class ThreadTaskBase
{
public:
    ThreadTaskBase();
    virtual ~ThreadTaskBase();
    bool Start(const int periodUS);
    void Stop(bool joinThread);
    double GetPeriod();

private:
    /*
     * Instead of using direct pointers in the derived classes,
     * an unordered map containing shared_ptr's to the other data
     * structures might be used to access data from other threads.
     */
    bool _stopThread = false;
    bool _taskOverloaded = false;
    double _periodSec = 0.01;
    std::thread _workerThread;
    std::mutex _workerThreadGuard;

    void ThreadMain(int periodUS);
    virtual void ThreadTask();
    // void ServiceRequestTemplate();
};

} /* namespace frc */

#endif /* SRC_THREADTASKBASE_H_ */
