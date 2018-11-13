/*
 * types.h
 *
 *  Created on: 20 mar. 2018
 *      Author: Alex
 */

#include "derivative.h"

#ifndef TYPES_H_
#define TYPES_H_

#define PIN_MODE_IN 0
#define PIN_MODE_OUT 1

#define UINT8_LS_HALF(x) (x & 0x0F)
#define UINT8_MS_HALF(x) (x >> 0x4u)

typedef unsigned char bool;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long int uint32;

typedef signed char int8;
typedef short int int16;
typedef long int int32;

typedef enum
{
	OPERATION_SUCCESS = 0u, OPERATION_ERROR = 1u
} tOperationResultType;

typedef enum
{
	STD_LOW = 0u,
	STD_HIGH,
} tPinLevelType;

#endif /* TYPES_H_ */
