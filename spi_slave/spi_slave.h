/*
 *  spi_slave.h   Support for slave-mode SPI communications.
 *
 *  Copyright 2019 (c) Callender-Consulting, LLC
 */
#ifndef __SPI_SLAVE_H__
#define __SPI_SLAVE_H__

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define SPI_SLAVE_BUS_NAME     			DT_INST_0_NORDIC_NRF_SPIS_LABEL
#define SPI_SLAVE_GPIOS_NAME    		DT_ALIAS_GPIO_0_LABEL
#define SPI_SLAVE_GPIO_IRQ_PIN  		DT_ALIAS_SPI_0_CSN_PIN

#define STACKSIZE 1024
#define PRIORITY 99

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void spi_slave_init(void);

#endif  /* __SPI_SLAVE_H__ */