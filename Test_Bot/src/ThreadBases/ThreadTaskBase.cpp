/*
 * ThreadTaskBase.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: Jake
 */

#include <ThreadBases/ThreadTaskBase.h>
#include <iostream>

#ifdef FOR_ROBOT
#include <SmartDashboard/SmartDashboard.h>
#endif

namespace frc
{

/**
 * Default constructor.
 * Runs the default constructor for the worker thread, but doesn't
 * actually start the thread.
 */
ThreadTaskBase::ThreadTaskBase()
        : _workerThread()

{
    // Nothing to do here.
}

/**
 * Default destructor.
 * Calls the Stop() function with the parameter TRUE to end the worker thread's
 * execution and wait for it to finish.
 */
ThreadTaskBase::~ThreadTaskBase()
{
    Stop(true);
}

/**
 * Default task that is executed periodically by ThreadMain().
 * This is overridden by the user.
 */
void ThreadTaskBase::ThreadTask()
{
    // Override this!!!
};

/**
 * Starts the worker thread which executes the main thread.
 * Success if a worker thread was successfully created.
 * Failure if a worker thread is already running, indicated by the mutex lock.
 * @param periodUS The time period for processing cycles to occur in microseconds (US).
 * @return Success Returns true if success, false if failure.
 */
bool ThreadTaskBase::Start(int periodUS)
{
    if (_workerThreadGuard.try_lock())
    {
        _workerThread = std::thread(&ThreadTaskBase::ThreadMain, this, periodUS);
        _workerThreadGuard.unlock();
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Sends the signal to stop thread execution.
 * @param joinThread Whether or not to wait for the thread to finish execution.
 */
void ThreadTaskBase::Stop(bool joinThread)
{
    _stopThread = true;
    if (joinThread && _workerThread.joinable())
    {
        _workerThread.join();
    }
}

/**
 * Returns the period of thread in seconds.
 * @return Period Period between processing cycles.
 */
double ThreadTaskBase::GetPeriod()
{
    return _periodSec;
}

/**
 * Main worker thread which executes ThreadTask() periodically.
 * @param periodUS The time period for processing cycles to occur in microseconds (US).
 */
void ThreadTaskBase::ThreadMain(const int periodUS)
{
    _periodSec = periodUS * 0.000001;
    _stopThread = false;
    _workerThreadGuard.lock();
    while (!_stopThread)
    {
        auto nextCycleTime = std::chrono::steady_clock::now() + std::chrono::microseconds(periodUS);
        ThreadTask();
        auto cycleEndTime = std::chrono::steady_clock::now();
        if (cycleEndTime > nextCycleTime)
        {
            _taskOverloaded = true;
        }
        else
        {
            _taskOverloaded = false;
        }
        std::this_thread::sleep_until(nextCycleTime);
    }
    _workerThreadGuard.unlock();
}

/*
 * This function services requests made by other threads.
 * Those threads may or may not be blocked by pending requests.
 * Any requests are made by toggling the request variables.
 * This reads those variables and services those requests if necessary.
 */
/*
 void ThreadTaskBase::ServiceRequestTemplate() {
 std::unique_lock<std::mutex> lck(threadData->mtxNotifier);
 
 //----------------------------------------------------------
 threadData->serviceGuard.lock();
 
 //--------- Make temp copies of request variables here ---------
 
 threadData->serviceGuard.unlock();
 //----------------------------------------------------------
 
 //--------- Service any pending requests here ---------
 
 //----------------------------------------------------------
 threadData->serviceGuard.lock();
 
 //--------- Reset service request variables here ---------
 
 threadData->serviceGuard.unlock();
 //----------------------------------------------------------
 
 threadData-> conditionWait.notify_all();
 }
 */

} /* namespace frc */
