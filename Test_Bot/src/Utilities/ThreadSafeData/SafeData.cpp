/*
 * SafeData.cpp
 *
 *  Created on: Nov 8, 2018
 *      Author: Jake
 */

//#include <Utilites/ThreadSafeData/SafeData.h>
#include <Utilities/ThreadSafeData/SafeData.h>
namespace frc
{
template <typename T>
CheckedData<T>::CheckedData()
        : _zeroCompare(std::chrono::microseconds(0))
        , _updateDeadline(std::chrono::steady_clock::now())
        , _timeoutUS(std::chrono::microseconds(0))
        , _validity(DataValidity::DATA_VALIDITY_INVALID)
        , _rangeMin(0)
        , _rangeMax(0)
        , _storedData(0)
{
    // Nothing to do.
}
template CheckedData<int>
::CheckedData();
template CheckedData<double>
::CheckedData();

template <typename T>
CheckedData<T>::CheckedData(T initData, T rangeMin, T rangeMax, unsigned int timeoutUS)
        : _zeroCompare(std::chrono::microseconds(0))
        , _updateDeadline(std::chrono::steady_clock::now())
        , _timeoutUS(std::chrono::microseconds(timeoutUS))
        , _validity(DataValidity::DATA_VALIDITY_INVALID)
        , _rangeMin(rangeMin)
        , _rangeMax(rangeMax)
        , _storedData(initData)
{
    // Nothing here
}
template CheckedData<int>
::SafeData(int initData, int rangeMin, int rangeMax, unsigned int timeoutUS);
template CheckedData<double>
::SafeData(double initData, double rangeMin, double rangeMax, unsigned int timeoutUS);

template <typename T>
CheckedData<T>::~CheckedData()
{
    // Nothing here
}
template CheckedData<int>
::~CheckedData();
template CheckedData<double>
::~CheckedData();

template <typename T>
bool CheckedData<T>::SetRange(T rangeMin, T rangeMax)
{
    bool success = true;

    if (rangeMax >= rangeMin)
    {
        _rangeMax = rangeMax;
        _rangeMin = rangeMin;
    }
    else
    {
        success = false;
    }
    return success;
}
template bool CheckedData<int>
::SetRange(int rangeMin, int rangeMax);
template bool CheckedData<double>
::SetRange(double rangeMin, double rangeMax);

template <typename T>
bool CheckedData<T>::SetTimeoutUS(unsigned int timeoutUS)
{
    _timeoutUS = std::chrono::microseconds(timeoutUS);
    return true;
}
template bool CheckedData<int>
::SetTimeoutUS(unsigned int timeoutUS);
template bool CheckedData<double>
::SetTimeoutUS(unsigned int timeoutUS);

template <typename T>
DataValidity CheckedData<T>::SetData(T inputData, bool isTest, bool forceIfDegraded)
{
    DataValidity tempValid = DataValidity::DATA_VALIDITY_INVALID;

    if (isTest)
    {
        tempValid = DataValidity::DATA_VALIDITY_TEST;

        _storedData = inputData;
        _validity = tempValid;
        _updateDeadline = _timeoutUS + std::chrono::steady_clock::now();
    }
    else if ((_rangeMax > _rangeMin) && (inputData > _rangeMax || inputData < _rangeMin))
    {
        tempValid = DataValidity::DATA_VALIDITY_DEGRADED;

        if (forceIfDegraded)
        {
            _storedData = inputData;
            _validity = tempValid;
            _updateDeadline = _timeoutUS + std::chrono::steady_clock::now();
        }
    }
    else
    {
        tempValid = DataValidity::DATA_VALIDITY_VALID;

        _storedData = inputData;
        _validity = tempValid;
        _updateDeadline = _timeoutUS + std::chrono::steady_clock::now();
    }
    return tempValid;
}

template DataValidity CheckedData<int>
::SetData(int inputData, bool isTest, bool forceIfDegraded);
template DataValidity CheckedData<double>
::SetData(double inputData, bool isTest, bool forceIfDegraded);

template <typename T>
DataValidity CheckedData<T>::GetData(
    T& outputData, bool forceIfTest, bool forceIfDegraded, bool forceIfInvalid)
{
    if (_validity != DataValidity::DATA_VALIDITY_TEST && _timeoutUS > _zeroCompare)
    {
        auto timestamp = std::chrono::steady_clock::now();
        if (timestamp > _updateDeadline)
        {
            _validity = DataValidity::DATA_VALIDITY_INVALID;
        }
    }

    switch (_validity)
    {
    case DataValidity::DATA_VALIDITY_VALID:
        outputData = _storedData;
        break;
    case DataValidity::DATA_VALIDITY_INVALID:
        if (forceIfInvalid)
        {
            outputData = _storedData;
        }
        break;
    case DataValidity::DATA_VALIDITY_DEGRADED:
        if (forceIfDegraded)
        {
            outputData = _storedData;
        }
        break;
    case DataValidity::DATA_VALIDITY_TEST:
        if (forceIfTest)
        {
            outputData = _storedData;
        }
        break;
    default:
        // Do nothing
        break;
    }

    return _validity;
}
template DataValidity CheckedData<int>
::GetData(int& outputData, bool forceIfTest, bool forceIfDegraded, bool forceIfInvalid);
template DataValidity CheckedData<double>
::GetData(double& outputData, bool forceIfTest, bool forceIfDegraded, bool forceIfInvalid);

} /* namespace frc */
