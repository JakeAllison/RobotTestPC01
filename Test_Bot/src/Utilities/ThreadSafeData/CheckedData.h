/*
 * CheckedData.h
 *
 *  Created on: Nov 8, 2018
 *      Author: Jake
 */

#ifndef SRC_UTILITIES_THREADSAFEDATA_CHECKEDDATA_H_
#define SRC_UTILITIES_THREADSAFEDATA_CHECKEDDATA_H_

#include <chrono>
#include <Defines.h>

namespace frc {
enum DataValidity {
    DATA_VALIDITY_VALID,
    DATA_VALIDITY_INVALID,
    DATA_VALIDITY_DEGRADED,
    DATA_VALIDITY_TEST
};

template <typename T>
class CheckedData {
public:
    CheckedData();
    CheckedData(T initData = 0, T rangeMin = 0, T rangeMax = 0, unsigned int timeoutUS = 0);
    virtual ~CheckedData();

    bool SetRange(T rangeMin, T rangeMax);
    bool SetTimeoutUS(unsigned int timeoutUS);
    DataValidity SetData(T inputData, bool isTest = false, bool forceIfDegraded = false);
    DataValidity GetData(T& outputData, bool forceIfTest = true, bool forceIfDegraded = true,
                         bool forceIfInvalid = true);
private:
    const std::chrono::steady_clock::duration _zeroCompare;
    std::chrono::steady_clock::time_point _updateDeadline;
    std::chrono::steady_clock::duration _timeoutUS;

    DataValidity _validity;
    T _rangeMin, _rangeMax;
    T _storedData;
};

} /* namespace frc */

#include <Utilities/ThreadSafeData/CheckedData.cpp>

#endif /* SRC_UTILITIES_THREADSAFEDATA_CHECKEDDATA_H_ */
