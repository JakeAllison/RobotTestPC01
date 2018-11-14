/*
 * SafeMultithreadDataArray.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: Jake
 */

//#include <Utilites/ThreadSafeData/SafeMultithreadDataArray.h>
#include <Utilities/ThreadSafeData/SafeMultithreadDataArray.h>
#include <iostream>

#ifdef FOR_ROBOT
#include <SmartDashboard/SmartDashboard.h>
#endif

namespace frc
{
template <typename T>
SafeMultithreadDataArray<T>::SafeMultithreadDataArray()
{
    // TODO Auto-generated constructor stub
}
template SafeMultithreadDataArray<int>
::SafeMultithreadDataArray();
template SafeMultithreadDataArray<double>
::SafeMultithreadDataArray();

template <typename T>
SafeMultithreadDataArray<T>::~SafeMultithreadDataArray()
{
    // TODO Auto-generated destructor stub
}
template SafeMultithreadDataArray<int>
::~SafeMultithreadDataArray();
template SafeMultithreadDataArray<double>
::~SafeMultithreadDataArray();

template <typename T>
bool SafeMultithreadDataArray<T>::AddKey(std::string NewKey, T InitData, T rangeMin, T rangeMax, unsigned int timeoutUS)
{
    bool success = true;
    _dataGuard.lock();
    bool insertSuccess = _storedData.emplace(std::pair<std::string, CheckedData<T>>(NewKey, CheckedData<T>(InitData, rangeMin, rangeMax, timeoutUS))).second;
    //bool insertSuccess = _storedData.emplace(std::piecewise_construct, std::forward_as_tuple(NewKey), std::forward_as_tuple(InitData, rangeMin, rangeMax, timeoutUS)).second;
    if (!insertSuccess)
    {
        success = false;
    }
    _dataGuard.unlock();
    return success;
}
template bool SafeMultithreadDataArray<int>
::AddKey(std::string NewKey, int InitData, int rangeMin, int rangeMax, unsigned int timeoutUS);
template bool SafeMultithreadDataArray<double>
::AddKey(std::string NewKey, double InitData, double rangeMin, double rangeMax, unsigned int timeoutUS);

template <typename T>
bool SafeMultithreadDataArray<T>::RemoveKey(std::string RemovedKey)
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
template bool SafeMultithreadDataArray<int>
::RemoveKey(std::string RemovedKey);
template bool SafeMultithreadDataArray<double>
::RemoveKey(std::string RemovedKey);

template <typename T>
bool SafeMultithreadDataArray<T>::GetData(std::string DataKey, T& OutputData, std::string ContextMessage, bool forceIfTest, bool forceIfDegraded,
        bool forceIfInvalid)
{
    bool success = true;
    _dataGuard.lock();
    bool keyExists = _storedData.find(DataKey) != _storedData.end();
    if (keyExists)
    {
        DataValidity validity = _storedData.at(DataKey).GetData(OutputData, forceIfTest, forceIfDegraded, forceIfInvalid);
        switch (validity)
        {
        case DataValidity::DATA_VALIDITY_DEGRADED:
            if(forceIfDegraded)
            {
                if (ContextMessage != "")
                {
                    std::cout << "Get() Forced Degraded: " << ContextMessage << ", " << DataKey << std::endl;
                }
            }
            else
            {
                if (ContextMessage != "")
                {
                    std::cout << "Get() Degraded: " << ContextMessage << ", " << DataKey << std::endl;
                }
                success = false;
            }
            break;
        case DataValidity::DATA_VALIDITY_INVALID:
            if(forceIfDegraded)
            {
                if (ContextMessage != "")
                {
                    std::cout << "Get() Forced Invalid: " << ContextMessage << ", " << DataKey << std::endl;
                }
            }
            else
            {
                if (ContextMessage != "")
                {
                    std::cout << "Get() Invalid: " << ContextMessage << ", " << DataKey << std::endl;
                }
                success = false;
            }
            break;
        case DataValidity::DATA_VALIDITY_TEST:
            if(forceIfDegraded)
            {
                if (ContextMessage != "")
                {
                    std::cout << "Get() Forced Test: " << ContextMessage << ", " << DataKey << std::endl;
                }
            }
            else
            {
                if (ContextMessage != "")
                {
                    std::cout << "Get() Test: " << ContextMessage << ", " << DataKey << std::endl;
                }
                success = false;
            }
            break;
        default:

            break;
        }

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
template bool SafeMultithreadDataArray<int>
::GetData(std::string DataKey, int& OutputData, std::string ContextMessage, bool forceIfTest, bool forceIfDegraded,
          bool forceIfInvalid);
template bool SafeMultithreadDataArray<double>
::GetData(std::string DataKey, double& OutputData, std::string ContextMessage, bool forceIfTest, bool forceIfDegraded,
          bool forceIfInvalid);

template <typename T>
bool SafeMultithreadDataArray<T>::SetData(std::string DataKey, T InputData, std::string ContextMessage, bool isTest, bool forceIfDegraded)
{
    bool success = true;
    _dataGuard.lock();
    if (_storedData.find(DataKey) != _storedData.end())
    {
        DataValidity validity = _storedData.at(DataKey).SetData(InputData, isTest, forceIfDegraded);
        switch (validity)
        {
        case DataValidity::DATA_VALIDITY_DEGRADED:
            if(forceIfDegraded)
            {
                if (ContextMessage != "")
                {
                    std::cout << "Set() Forced Degraded: " << ContextMessage << ", " << DataKey << std::endl;
                }
            }
            else
            {
                if (ContextMessage != "")
                {
                    std::cout << "Set() Degraded: " << ContextMessage << ", " << DataKey << std::endl;
                }
                success = false;
            }
            break;
        default:

            break;
        }
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
template bool SafeMultithreadDataArray<int>
::SetData(std::string DataKey, int InputData, std::string ContextMessage, bool isTest, bool forceIfDegraded);
template bool SafeMultithreadDataArray<double>
::SetData(std::string DataKey, double InputData, std::string ContextMessage, bool isTest, bool forceIfDegraded);

template <typename T>
void SafeMultithreadDataArray<T>::PrintData()
{
    for (std::pair<std::string, CheckedData<T>> element : _storedData)
    {
        T temp;
        DataValidity validity = element.second.GetData(temp, true, true, true);
        std::cout << element.first << ": " << validity << ", " << static_cast<double>(temp) << std::endl;
    }
}
template void SafeMultithreadDataArray<int>
::PrintData();
template void SafeMultithreadDataArray<double>
::PrintData();

#ifdef FOR_ROBOT

template <typename T>void SafeMultithreadDataArray<T>::SendToSmartDashboard()
{
    for (std::pair<std::string, CheckedData<T>> element : _storedData)
    {
        T temp;
        DataValidity validity = element.second.GetData(temp, true, true, true);
        frc::SmartDashboard::PutNumber(element.first + " Validity", static_cast<double>(validity));
        frc::SmartDashboard::PutNumber(element.first, static_cast<double>(temp));
    }
}
template void SafeMultithreadDataArray<int>::SendToSmartDashboard();
template void SafeMultithreadDataArray<double>::SendToSmartDashboard();

#endif
} /* namespace frc */
