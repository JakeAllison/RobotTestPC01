/*
 * DriveOutputData.h
 *
 *  Created on: Oct 24, 2018
 *      Author: Jake
 */

#ifndef SRC_OUTPUT_DRIVEOUTPUTDATA_H_
#define SRC_OUTPUT_DRIVEOUTPUTDATA_H_

#include <ThreadBases/ThreadDataBase.h>
#include <Defines.h>

namespace frc
{

class DriveOutputData : public ThreadDataBase
{
public:
    friend class DriveOutputTask;
    DriveOutputData();
    virtual ~DriveOutputData();
};

} /* namespace frc */

#endif /* SRC_OUTPUT_DRIVEOUTPUTDATA_H_ */
