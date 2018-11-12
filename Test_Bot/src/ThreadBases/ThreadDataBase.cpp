/*
 * ThreadDataBase.cpp
 *
 *  Created on: Oct 23, 2018
 *      Author: Jake
 */

#include <ThreadBases/ThreadDataBase.h>
#include <iostream>

#ifdef FOR_ROBOT
#include <SmartDashboard/SmartDashboard.h>
#endif

namespace frc
{

ThreadDataBase::ThreadDataBase()
{
    // TODO Auto-generated constructor stub
}

ThreadDataBase::~ThreadDataBase()
{
    // TODO Auto-generated destructor stub
}

/**
 * Adds new key for type int.
 * Returns true if the DataKey was successfully created.
 * Returns false if the DataKey already exists.
 * @param NewKey String that is used to identify the desired data.
 * @param InitData Data being retrieved.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::AddKey<int>(std::string NewKey, int initData)
{
    bool success = _intData.AddKey(NewKey, initData);
    return success;
}

/**
 * Adds new key for type double.
 * Returns true if the DataKey was successfully created.
 * Returns false if the DataKey already exists.
 * @param NewKey String that is used to identify the desired data.
 * @param InitData Data being retrieved.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::AddKey<double>(std::string NewKey, double initData)
{
    bool success = _doubleData.AddKey(NewKey, initData);
    return success;
}

/**
 * Adds new key for type int.
 * Returns true if the DataKey was successfully created.
 * Returns false if the DataKey already exists.
 * @param NewKey String that is used to identify the desired data.
 * @param InitData Data being retrieved.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::AddSafeKey<int>(
    std::string NewKey, int initData, int Min, int Max, unsigned int TimeoutUS)
{
    bool success = _intDataSafe.AddKey(NewKey, initData, Min, Max, TimeoutUS);
    return success;
}

/**
 * Adds new key for type double.
 * Returns true if the DataKey was successfully created.
 * Returns false if the DataKey already exists.
 * @param NewKey String that is used to identify the desired data.
 * @param InitData Data being retrieved.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::AddSafeKey<double>(
    std::string NewKey, double initData, double Min, double Max, unsigned int TimeoutUS)
{
    bool success = _doubleDataSafe.AddKey(NewKey, initData, Min, Max, TimeoutUS);
    return success;
}

/**
 * Removes key for int data types.
 * Returns true if the DataKey was successfully removed.
 * Returns false if the DataKey doesn't exist.
 * @param RemovedKey String that is used to identify the desired data.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::RemoveKey<int>(std::string RemovedKey)
{
    bool success = _intData.RemoveKey(RemovedKey);
    return success;
}

/**
 * Removes key for double data types.
 * Returns true if the DataKey was successfully removed.
 * Returns false if the DataKey doesn't exist.
 * @param RemovedKey String that is used to identify the desired data.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::RemoveKey<double>(std::string RemovedKey)
{
    bool success = _doubleData.RemoveKey(RemovedKey);
    return success;
}

/**
 * Removes key for safe int data types.
 * Returns true if the DataKey was successfully removed.
 * Returns false if the DataKey doesn't exist.
 * @param RemovedKey String that is used to identify the desired data.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::RemoveSafeKey<int>(std::string RemovedKey)
{
    bool success = _intDataSafe.RemoveKey(RemovedKey);
    return success;
}

/**
 * Removes key for safe double data types.
 * Returns true if the DataKey was successfully removed.
 * Returns false if the DataKey doesn't exist.
 * @param RemovedKey String that is used to identify the desired data.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::RemoveSafeKey<double>(std::string RemovedKey)
{
    bool success = _doubleDataSafe.RemoveKey(RemovedKey);
    return success;
}

/**
 * Gets data of type int.
 * Returns true if the DataKey exists for the output type.
 * Returns false otherwise.
 * @param DataKey String that is used to identify the desired data.
 * @param OutputData Data being retrieved.
 * @param ContextMessage Optional string for debugging.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::GetData<int>(std::string DataKey, int& OutputData, std::string ContextMessage)
{
    bool success = _intData.GetData(DataKey, OutputData, ContextMessage);
    return success;
}

/**
 * Gets data of type double.
 * Returns true if the DataKey exists for the output type.
 * Returns false otherwise.
 * @param DataKey String that is used to identify the desired data.
 * @param OutputData Data being retrieved.
 * @param ContextMessage Optional string for debugging.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::GetData<double>(std::string DataKey, double& OutputData, std::string ContextMessage)
{
    bool success = _doubleData.GetData(DataKey, OutputData, ContextMessage);
    return success;
}

/**
 * Gets data of type int.
 * Returns true if the DataKey exists for the output type.
 * Returns false otherwise.
 * @param DataKey String that is used to identify the desired data.
 * @param OutputData Data being retrieved.
 * @param ContextMessage Optional string for debugging.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::GetSafeData<int>(std::string DataKey, int& OutputData, std::string ContextMessage, bool forceIfTest, bool forceIfDegraded, bool forceIfInvalid)
{
    bool success = _intDataSafe.GetData(DataKey, OutputData, ContextMessage, forceIfTest, forceIfDegraded, forceIfInvalid);
    return success;
}

/**
 * Gets data of type double.
 * Returns true if the DataKey exists for the output type.
 * Returns false otherwise.
 * @param DataKey String that is used to identify the desired data.
 * @param OutputData Data being retrieved.
 * @param ContextMessage Optional string for debugging.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::GetSafeData<double>(std::string DataKey, double& OutputData, std::string ContextMessage, bool forceIfTest, bool forceIfDegraded, bool forceIfInvalid)
{
    bool success = _doubleDataSafe.GetData(DataKey, OutputData, ContextMessage, forceIfTest, forceIfDegraded, forceIfInvalid);
    return success;
}

/**
 * Sets data of type int.
 * Returns true if the DataKey exists for the output type.
 * Returns false otherwise.
 * @param DataKey String that is used to identify the desired data.
 * @param Data being written.
 * @param ContextMessage Optional string for debugging.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::SetData<int>(std::string DataKey, int InputData, std::string ContextMessage)
{
    bool success = _intData.SetData(DataKey, InputData, ContextMessage);
    return success;
}

/**
 * Sets data of type double.
 * Returns true if the DataKey exists for the output type.
 * Returns false otherwise.
 * @param DataKey String that is used to identify the desired data.
 * @param Data being written.
 * @param ContextMessage Optional string for debugging.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::SetData<double>(std::string DataKey, double InputData, std::string ContextMessage)
{
    bool success = _doubleData.SetData(DataKey, InputData, ContextMessage);
    return success;
}

/**
 * Sets data of type int.
 * Returns true if the DataKey exists for the output type.
 * Returns false otherwise.
 * @param DataKey String that is used to identify the desired data.
 * @param Data being written.
 * @param ContextMessage Optional string for debugging.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::SetSafeData<int>(std::string DataKey, int InputData, std::string ContextMessage, bool isTest, bool forceIfDegraded)
{
    bool success = _intDataSafe.SetData(DataKey, InputData, ContextMessage, isTest, forceIfDegraded);
    return success;
}

/**
 * Sets data of type double.
 * Returns true if the DataKey exists for the output type.
 * Returns false otherwise.
 * @param DataKey String that is used to identify the desired data.
 * @param Data being written.
 * @param ContextMessage Optional string for debugging.
 * @return success Returns success as true or false.
 */
template<>
bool ThreadDataBase::SetSafeData<double>(std::string DataKey, double InputData, std::string ContextMessage, bool isTest, bool forceIfDegraded)
{
    bool success = _doubleDataSafe.SetData(DataKey, InputData, ContextMessage, isTest, forceIfDegraded);
    return success;
}

void ThreadDataBase::PrintData()
{
    _intData.PrintData();
    _doubleData.PrintData();
    _intDataSafe.PrintData();
    _doubleDataSafe.PrintData();
}

#ifdef FOR_ROBOT
void ThreadDataBase::SendToSmartDashboard()
{
    _intData.PrintData();
    _doubleData.PrintData();
    _intDataSafe.PrintData();
    _doubleDataSafe.PrintData();
}
#endif
/*
 void ThreadTaskBase::MakeAServiceRequest(bool Blocking, unsigned int MaxBlockTimeUS) {
 std::unique_lock<std::mutex> lck(mtxNotifier);
 
 //----------------------------------------------------------
 serviceGuard.lock();
 
 //-------- Set your request variable below here ------------
 
 serviceGuard.unlock();
 //----------------------------------------------------------
 
 if (Blocking) {
 if (MaxBlockTimeUS > 0) {
 conditionWait.wait_for(lck, std::chrono::microseconds(MaxBlockTimeUS));
 } else {
 conditionWait.wait(lck);
 }
 }
 }
 */
} /* namespace frc */
