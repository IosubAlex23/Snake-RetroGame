/*
 * ADC.c
 *
 *  Created on: Mar 27, 2018
 */


#include "ADC.h"
#include "derivative.h"                 /* include peripheral declarations SKEAZ128M4 */


static tAdcCfg AdcCfgSet;
static tModuleState AdcModuleState = ADC_NOT_INIT;



tAdcCfg* Adc_GetCfgHandle( void )
{
    return &AdcCfgSet;
}



uint8_t  Adc_IsConversionComplete( void )
{
    return (uint8_t) ((ADC_SC1 & ADC_SC1_COCO_MASK)>>ADC_SC1_COCO_SHIFT);  /* Return value of Conversion Complete flag */
}



tAdcReturnCode Adc_Init( void )
{
    tAdcReturnCode retCode = (tAdcReturnCode) ADC_ERR_SUCCESS;

    if ( (tModuleState) ADC_NOT_INIT == AdcModuleState )
    {
        SIM_SCGC |= SIM_SCGC_ADC_MASK;      /* Enable bus clock to ADC module            */
        ADC_SC1 = 0x1F;                     /* Disable module (default state)            */
                                            /* AIEN = 0: Interrupts disabled             */
                                            /* ADCO = 0: Continuous conversions disabled */
                                            /* ADCH = 1F: Module disabled                */
        AdcModuleState = (tModuleState) ADC_INIT;
    }

    return retCode;
}



tAdcReturnCode Adc_ConfigAcquisition( tAdcCfg* pNewAdcCfg )
{
    tAdcReturnCode retCode = (tAdcReturnCode) ADC_ERR_SUCCESS;

    if( (tModuleState) ADC_NOT_INIT != AdcModuleState )
    {

    	switch(pNewAdcCfg->AdcResolution)
    	{
    	case (tAdcResolution) ADC_RES_8_BIT:
    		ADC_SC3 &= ~ADC_SC3_MODE_MASK ;       /* Clear any prior ADCH bits*/
    		ADC_SC3 |= ADC_SC3_MODE(0);
    			break;
    	case (tAdcResolution) ADC_RES_10_BIT:
    		ADC_SC3 &= ~ADC_SC3_MODE_MASK ;       /* Clear any prior ADCH bits*/
    		ADC_SC3 |= ADC_SC3_MODE(1);
    	    	break;
    	case (tAdcResolution) ADC_RES_12_BIT:
    		ADC_SC3 &= ~ADC_SC3_MODE_MASK ;       /* Clear any prior ADCH bits*/
    		ADC_SC3 |= ADC_SC3_MODE(2);
    	    	break;
    	default:
    		retCode = (tAdcReturnCode) ADC_ERR_BAD_CFG;
    	}
    	switch(pNewAdcCfg->AdcOpMode)
    	{
    	case (tAdcOpMode) ADC_OPMODE_SINGLESHOT:
    		if(pNewAdcCfg->ucSingleChnIdx > MAX_CHN_IDX )
    		{
    		retCode = (tAdcReturnCode) ADC_ERR_BAD_CFG;
    		}
    	}
    }
    else
    {
        retCode = (tAdcReturnCode) ADC_ERR_NOT_INIT;
    }

    return retCode;
}



tAdcReturnCode Adc_GetSingleResult( uint16_t* pStorage )
{
    tAdcReturnCode retCode = (tAdcReturnCode) ADC_ERR_SUCCESS;

    *pStorage = ADC_R;    /* Read ADC conversion result (clears COCO flag) */
    return retCode;
}



tAdcReturnCode Adc_GetFifoResult( uint16_t* pStorage, uint8_t ucNoChannels )
{
    tAdcReturnCode retCode = (tAdcReturnCode) ADC_ERR_SUCCESS;

    return retCode;
}



tAdcReturnCode Adc_StartSingleConversion( uint8_t ucChnIdx )
{
	tAdcReturnCode retCode = (tAdcReturnCode) ADC_ERR_SUCCESS;

	if( (tModuleState) ADC_NOT_INIT != AdcModuleState )
	    {
		    ADC_APCTL1 = 0u;
		    ADC_APCTL1 |= (1<<ucChnIdx);

			ADC_SC1 &= ~ADC_SC1_ADCH_MASK;       /* Clear any prior ADCH bits*/
			ADC_SC1 |= ADC_SC1_ADCH(ucChnIdx);
	    }
	else
	{
		retCode = (tAdcReturnCode) ADC_ERR_BAD_CFG;
	}

    return retCode;
}



tAdcReturnCode Adc_StartFifoConversion( void )
{
    tAdcReturnCode retCode = (tAdcReturnCode) ADC_ERR_SUCCESS;

    return retCode;
}
