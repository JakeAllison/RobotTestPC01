/*
 * UserInputData.h
 *
 *  Created on: Oct 24, 2018
 *      Author: Jake
 */

#ifndef SRC_USERINPUTDATA_H_
#define SRC_USERINPUTDATA_H_

#include <ThreadBases/ThreadDataBase.h>
#include <Defines.h>

namespace frc
{

class UserInputData : public ThreadDataBase
{
public:
    friend class UserInputTask;
    UserInputData();
    virtual ~UserInputData();
};

} /* namespace frc */

#endif /* SRC_USERINPUTDATA_H_ */
