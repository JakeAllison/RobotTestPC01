/*
 * MultithreadDataArray.h
 *
 *  Created on: Nov 9, 2018
 *      Author: Jake
 */

#ifndef SRC_UTILITIES_THREADSAFEDATA_MULTITHREADDATAARRAY_H_
#define SRC_UTILITIES_THREADSAFEDATA_MULTITHREADDATAARRAY_H_

#include <unordered_map>
#include <mutex>
#include <string>
#include <Defines.h>

namespace frc
{
template <typename T>
class MultithreadDataArray
{
public:
    MultithreadDataArray();
    virtual ~MultithreadDataArray();
    bool AddKey(std::string NewKey, T InitData = 0);
    bool RemoveKey(std::string RemovedKey);
    bool GetData(std::string DataKey, T& OutputData, std::string ContextMessage = "");
    bool SetData(std::string DataKey, T InputData, std::string ContextMessage = "");

    void PrintData();
#ifdef FOR_ROBOT

    void SendToSmartDashboard();
#endif

private:
    std::mutex _dataGuard;
    std::unordered_map<std::string, T> _storedData;
};

} /* namespace frc */

#endif /* SRC_UTILITIES_THREADSAFEDATA_MULTITHREADDATAARRAY_H_ */
