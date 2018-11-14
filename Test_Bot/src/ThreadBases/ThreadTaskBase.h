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
#include <ThreadBases/ThreadDataContainer.h>

namespace frc {

class ThreadTaskBase {
public:
    ThreadTaskBase(ThreadDataContainer* threadData);
    virtual ~ThreadTaskBase();
    bool Start(const int periodUS);
    void Stop(bool joinThread);
    double GetPeriod();
protected:
    ThreadDataContainer* _threadData;
private:
    bool _stopThread = false;
    bool _taskOverloaded = false;
    long int _periodUS = 10000;
    std::thread _workerThread;
    std::mutex _workerThreadGuard;

    void ThreadMain(int periodUS);
    virtual void ThreadTask();
    // void ServiceRequestTemplate();
};

} /* namespace frc */

#endif /* SRC_THREADTASKBASE_H_ */
