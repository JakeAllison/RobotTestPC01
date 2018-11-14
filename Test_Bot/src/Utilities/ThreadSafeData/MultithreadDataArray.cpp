/*
 * MultithreadDataArray.cpp
 *
 *  Created on: Nov 9, 2018
 *      Author: Jake
 */

#ifndef SRC_UTILITIES_THREADSAFEDATA_MULTITHREADDATAARRAY_CPP_
#define SRC_UTILITIES_THREADSAFEDATA_MULTITHREADDATAARRAY_CPP_

#include <Utilities/ThreadSafeData/MultithreadDataArray.h>
#include <iostream>

#ifdef FOR_ROBOT
#include <SmartDashboard/SmartDashboard.h>
#endif

namespace frc {
template <typename T>
MultithreadDataArray<T>::MultithreadDataArray() {
    // TODO Auto-generated constructor stub
}

template <typename T>
MultithreadDataArray<T>::~MultithreadDataArray() {
    // TODO Auto-generated destructor stub
}

template <typename T>
bool MultithreadDataArray<T>::AddKey(std::string NewKey, T InitData) {
    bool success = true;
    _dataGuard.lock();

    bool insertSuccess = _storedData.insert(std::pair<std::string, T>(NewKey, InitData)).second;
    if (!insertSuccess) {
        success = false;
    }

    _dataGuard.unlock();
    return success;
}

template <typename T>
bool MultithreadDataArray<T>::RemoveKey(std::string RemovedKey) {
    bool success = false;
    _dataGuard.lock();

    bool keyErased = _storedData.erase(RemovedKey) != 0;
    if (keyErased) {
        success = true;
    }

    _dataGuard.unlock();
    return success;
}

template <typename T>
bool MultithreadDataArray<T>::GetData(std::string DataKey, T& OutputData, std::string ContextMessage) {
    bool success = true;
    _dataGuard.lock();

    bool keyExists = _storedData.find(DataKey) != _storedData.end();
    if (keyExists) {
        OutputData = _storedData.at(DataKey);
    } else {
        if (ContextMessage != "") {
            std::cout << "Get() Key Failure: " << ContextMessage << ", " << DataKey << std::endl;
        }
        success = false;
    }

    _dataGuard.unlock();

    return success;
}

template <typename T>
bool MultithreadDataArray<T>::SetData(std::string DataKey, T InputData, std::string ContextMessage) {
    bool success = true;
    _dataGuard.lock();

    if (_storedData.find(DataKey) != _storedData.end()) {
        _storedData[DataKey] = InputData;
    } else {
        if (ContextMessage != "") {
            std::cout << "Set() Key Failure: " << ContextMessage << ", " << DataKey << ": " << InputData
            << std::endl;
        }
        success = false;
    }

    _dataGuard.unlock();
    return success;
}

template <typename T>
void MultithreadDataArray<T>::PrintData() {
    _dataGuard.lock();

    for (std::pair<std::string, T> element : _storedData) {
        T temp = element.second;
        std::cout << element.first << ": " << temp << std::endl;
    }

    _dataGuard.unlock();
}

#ifdef FOR_ROBOT

template <typename T>
void MultithreadDataArray<T>::SendToSmartDashboard() {
    for (std::pair<std::string, T> element : _storedData) {
        T temp = element.second;
        frc::SmartDashboard::PutNumber(element.first, static_cast<double>(temp));
    }
}

#endif

} /* namespace frc */

#endif
