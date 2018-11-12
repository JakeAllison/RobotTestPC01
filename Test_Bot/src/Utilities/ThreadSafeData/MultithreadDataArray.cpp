/*
 * MultithreadDataArray.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: Jake
 */

#include <Utilities/ThreadSafeData/MultithreadDataArray.h>
#include <iostream>

#ifdef FOR_ROBOT
#include <SmartDashboard/SmartDashboard.h>
#endif

namespace frc
{
template <typename T>
MultithreadDataArray<T>::MultithreadDataArray()
{
    // TODO Auto-generated constructor stub
}
template MultithreadDataArray<int>
::MultithreadDataArray();
template MultithreadDataArray<double>
::MultithreadDataArray();

template <typename T>
MultithreadDataArray<T>::~MultithreadDataArray()
{
    // TODO Auto-generated destructor stub
}
template MultithreadDataArray<int>
::~MultithreadDataArray();
template MultithreadDataArray<double>
::~MultithreadDataArray();

template <typename T>
bool MultithreadDataArray<T>::AddKey(std::string NewKey, T InitData)
{
    bool success = true;
    _dataGuard.lock();
    bool insertSuccess = _storedData.insert(std::pair<std::string, T>(NewKey, InitData)).second;
    if (!insertSuccess)
    {
        success = false;
    }
    _dataGuard.unlock();
    return success;
}
template bool MultithreadDataArray<int>
::AddKey(std::string NewKey, int InitData);
template bool MultithreadDataArray<double>
::AddKey(std::string NewKey, double InitData);

template <typename T>
bool MultithreadDataArray<T>::RemoveKey(std::string RemovedKey)
{
    bool success = false;
    _dataGuard.lock();
    bool keyErased = _storedData.erase(RemovedKey) != 0;
    if (keyErased)
    {
        success = true;
    }
    _dataGuard.unlock();
    return success;
}
template bool MultithreadDataArray<int>
::RemoveKey(std::string RemovedKey);
template bool MultithreadDataArray<double>
::RemoveKey(std::string RemovedKey);

template <typename T>
bool MultithreadDataArray<T>::GetData(std::string DataKey, T& OutputData, std::string ContextMessage)
{
    bool success = true;
    _dataGuard.lock();
    bool keyExists = _storedData.find(DataKey) != _storedData.end();
    if (keyExists)
    {
        OutputData = _storedData.at(DataKey);
    }
    else
    {
        if (ContextMessage != "")
        {
            std::cout << "Get() Key Failure: " << ContextMessage << ", " << DataKey << std::endl;
        }
        success = false;
    }
    _dataGuard.unlock();

    return success;
}
template bool MultithreadDataArray<int>
::GetData(std::string DataKey, int& OutputData, std::string ContextMessage);
template bool MultithreadDataArray<double>
::GetData(std::string DataKey, double& OutputData, std::string ContextMessage);

template <typename T>
bool MultithreadDataArray<T>::SetData(std::string DataKey, T InputData, std::string ContextMessage)
{
    bool success = true;
    _dataGuard.lock();
    if (_storedData.find(DataKey) != _storedData.end())
    {
        _storedData[DataKey] = InputData;
    }
    else
    {
        if (ContextMessage != "")
        {
            std::cout << "Set() Key Failure: " << ContextMessage << ", " << DataKey << ": " << InputData
            << std::endl;
        }
        success = false;
    }
    _dataGuard.unlock();
    return success;
}
template bool MultithreadDataArray<int>
::SetData(std::string DataKey, int InputData, std::string ContextMessage);
template bool MultithreadDataArray<double>
::SetData(std::string DataKey, double InputData, std::string ContextMessage);

template <typename T>
void MultithreadDataArray<T>::PrintData()
{
    for (std::pair<std::string, T> element : _storedData)
    {
        T temp = element.second;
        std::cout << element.first << ": " << static_cast<double>(temp) << std::endl;
    }
}
template void MultithreadDataArray<int>
::PrintData();
template void MultithreadDataArray<double>
::PrintData();

#ifdef FOR_ROBOT

template <typename T>
void MultithreadDataArray<T>::SendToSmartDashboard()
{
    for (std::pair<std::string, T> element : _storedData)
    {
        T temp = element.second;
        frc::SmartDashboard::PutNumber(element.first, static_cast<double>(temp));
    }
}
template void MultithreadDataArray<int>
::SendToSmartDashboard();
template void MultithreadDataArray<double>
::SendToSmartDashboard();

#endif

} /* namespace frc */
