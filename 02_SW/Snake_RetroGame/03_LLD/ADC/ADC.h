/*
 * ADC.h
 *
 *  Created on: Mar 27, 2018
 */

#ifndef ADC_H_
#define ADC_H_

#include <cstdint>

#define MAX_FIFO_SIZE  (8u)
#define MAX_CHN_IDX    (15u)


typedef enum
{
    ADC_ERR_SUCCESS = 0u,
    ADC_ERR_BAD_CFG,
    ADC_ERR_NOT_INIT,
    ADC_ERR_MAX_CODE
} tAdcReturnCode;

typedef enum
{
    ADC_OPMODE_SINGLESHOT = 0u,
    ADC_OPMODE_FIFO,
    ADC_MAX_OPMODE
} tAdcOpMode;

typedef enum
{
    ADC_RES_8_BIT = 0u,
    ADC_RES_10_BIT,
    ADC_RES_12_BIT,
    ADC_MAX_RES
} tAdcResolution;


typedef enum
{
    ADC_NOT_INIT,
    ADC_INIT,
    ADC_MAX_STATE
} tModuleState;


typedef struct
{
    tAdcOpMode      AdcOpMode;
    tAdcResolution  AdcResolution;
    uint8_t         ucSingleChnIdx;
    uint8_t         ucFifoDepth;
    uint8_t         aucFifoChnSelection[MAX_FIFO_SIZE];

} tAdcCfg;



/* Driver API */
tAdcReturnCode Adc_Init( void );
tAdcReturnCode Adc_ConfigAcquisition( tAdcCfg* pNewAdcCfg );
tAdcReturnCode Adc_GetSingleResult( uint16_t* pStorage );
tAdcReturnCode Adc_GetFifoResult( uint16_t* pStorage, uint8_t ucNoChannels );
tAdcReturnCode Adc_StartSingleConversion( uint8_t ucChnIdx );
tAdcReturnCode Adc_StartFifoConversion( void );
uint8_t        Adc_IsConversionComplete( void );
tAdcCfg*       Adc_GetCfgHandle( void );


#endif /* ADC_H_ */
