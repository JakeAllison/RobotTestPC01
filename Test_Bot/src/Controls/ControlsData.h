/*
 * ControlsData.h
 *
 *  Created on: Oct 23, 2018
 *      Author: Jake
 */

#ifndef SRC_CONTROLSDATA_H_
#define SRC_CONTROLSDATA_H_

#include <ThreadBases/ThreadDataBase.h>
#include <Defines.h>

namespace frc
{

class ControlsData : public ThreadDataBase
{
public:
    friend class ControlsTask;
    ControlsData();
    virtual ~ControlsData();
};

} /* namespace frc */

#endif /* SRC_CONTROLSDATA_H_ */
