/*
 * SafeMultithreadDataArray.h
 *
 *  Created on: Nov 9, 2018
 *      Author: Jake
 */

#ifndef SRC_UTILITIES_THREADSAFEDATA_SAFEMULTITHREADDATAARRAY_H_
#define SRC_UTILITIES_THREADSAFEDATA_SAFEMULTITHREADDATAARRAY_H_

#include <unordered_map>
#include <mutex>
#include <string>
#include <Defines.h>
#include <Utilities/ThreadSafeData/SafeData.h>

namespace frc
{

template <typename T>
class SafeMultithreadDataArray
{
public:
    SafeMultithreadDataArray();
    virtual ~SafeMultithreadDataArray();
    bool AddKey(std::string NewKey, T InitData, T rangeMin = 0, T rangeMax = 0, unsigned int timeoutUS = 0);
    bool RemoveKey(std::string RemovedKey);
    bool GetData(std::string DataKey, T& OutputData, std::string ContextMessage = "", bool forceIfTest = false, bool forceIfDegraded = false,
                 bool forceIfInvalid = false);
    bool SetData(std::string DataKey, T InputData, std::string ContextMessage = "", bool isTest = false, bool forceIfDegraded = false);
    void PrintData();
#ifdef FOR_ROBOT

    void SendToSmartDashboard();
#endif


private:
    std::mutex _dataGuard;
    std::unordered_map<std::string, SafeData<T>> _storedData;
};

} /* namespace frc */

#endif /* SRC_UTILITIES_THREADSAFEDATA_SAFEMULTITHREADDATAARRAY_H_ */
