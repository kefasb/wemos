/*
 * EmptyData.h
 *
 * Author: Piotr Borkowski
 *
 * A type of {@link PmsData} indicating that the {@link PmsData} is empty or not usable.
 *
 */

#ifndef PMS3003_EMPTYDATA_H_
#define PMS3003_EMPTYDATA_H_

#include "PmsData.h"

class EmptyData: public PmsData {
public:
    EmptyData();
    virtual ~EmptyData();
};

#endif /* PMS3003_EMPTYDATA_H_ */
