/*
 * ThreadDataBase.h
 *
 *  Created on: Oct 23, 2018
 *      Author: Jake
 */

#ifndef SRC_THREADDATABASE_H_
#define SRC_THREADDATABASE_H_


#include <Utilities/ThreadSafeData/MultithreadDataArray.h>
#include <Utilities/ThreadSafeData/SafeMultithreadDataArray.h>
#include <unordered_map>
#include <mutex>
#include <string>
#include <condition_variable>
#include <Defines.h>

namespace frc {
class ThreadDataBase {
public:
    ThreadDataBase();
    virtual ~ThreadDataBase();
    template<typename T>
    bool GetData(std::string DataKey, T& OutputData, std::string ContextMessage = "");
    template<typename T>
    bool GetSafeData(std::string DataKey, T& OutputData, std::string ContextMessage = "", bool forceIfTest = true, bool forceIfDegraded = true, bool forceIfInvalid = true);

    void PrintData();

#ifdef FOR_ROBOT

    void SendToSmartDashboard();
#endif
    // void MakeAServiceRequest(bool Blocking, unsigned int MaxBlockTimeUS);
protected:
    template<typename T>
    bool SetData(std::string DataKey, T InputData, std::string ContextMessage = "");
    template<typename T>
    bool SetSafeData(std::string DataKey, T InputData, std::string ContextMessage = "", bool isTest = false, bool forceIfDegraded = false);

    template<typename T>
    bool AddKey(std::string NewIndex, T initData = 0);
    template<typename T>
    bool AddSafeKey(std::string NewIndex, T initData = 0, T Min = 0, T Max = 0, unsigned int TimeoutUS = 0);

    template<typename T>
    bool RemoveKey(std::string RemovedKey);
    template<typename T>
    bool RemoveSafeKey(std::string RemovedKey);

    std::mutex serviceGuard;
    std::mutex mtxNotifier;
    std::condition_variable conditionWait;

private:
    MultithreadDataArray<int> _intData;
    MultithreadDataArray<double> _doubleData;
    SafeMultithreadDataArray<int> _intDataSafe;
    SafeMultithreadDataArray<double> _doubleDataSafe;

};

} /* namespace frc */

#endif /* SRC_THREADDATABASE_H_ */
