/*! --------------------------------------------------------------------------
 *  @file    spi_master.c
 *  @brief   Support for slave-mode SPI communications.
 *
 * @attention
 *
 * Copyright 2019 (c) Callender-Consulting, LLC
 *
 * All rights reserved.
 *
 * @author Robin Callender
 */
#include <string.h>
#include <errno.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <spi.h>

#include "spi_master.h"


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
int spi_master_write(struct device * spi, 
                     struct spi_config * spi_cfg,
                     u16_t * data)
{
    struct spi_buf bufs = {
            .buf = data,
            .len = 2
    };
    struct spi_buf_set tx = {
        .buffers = &bufs
    };

    tx.count = 1;

    return spi_write(spi, spi_cfg, &tx);
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
int spi_master_read(struct device * spi, 
                    struct spi_config * spi_cfg,
                    u16_t * data)
{
    struct spi_buf bufs = {
            .buf = data,
            .len = 2
    };
    struct spi_buf_set rx = {
        .buffers = &bufs
    };

    rx.count = 1;

    return spi_read(spi, spi_cfg, &rx);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void spi_master_init(void)
{
    struct device * spi;
    struct spi_config spi_cfg;
    struct spi_cs_control cs_ctrl;

    u16_t tx_data = 0x1234;
    u16_t rx_data = 0;

    printk("SPI Master example application\n");

    printk("rx_data buffer at %p\n", &rx_data);

    spi = device_get_binding(DT_INST_0_NORDIC_NRF_SPI_LABEL);
    if (!spi) {
        printk("Could not find SPI driver\n");
        return;
    }

    cs_ctrl.gpio_dev = device_get_binding(DT_ALIAS_SPI_0_CS_GPIOS_CONTROLLER);
    cs_ctrl.gpio_pin = DT_ALIAS_SPI_0_CS_GPIOS_PIN;
    cs_ctrl.delay = 0;

    /*
     *  SPI controller configuration structure for the nRF52 series.
     *
     *  param frequency is the bus frequency in hertz
     *  param operation is a bit field with the following parts:
     *
     *     operational mode  [ 0 ]       - master or slave.
     *     mode              [ 1 : 3 ]   - Polarity, phase and loop mode.
     *     transfer          [ 4 ]       - LSB or MSB first.
     *     word_size         [ 5 : 10 ]  - Size of a data frame in bits.
     *     lines             [ 11 : 12 ] - MISO lines: Single/Dual/Quad/Octal.
     *     cs_hold           [ 13 ]      - Hold on the CS line if possible.
     *     lock_on           [ 14 ]      - Keep resource locked for the caller.
     *     cs_active_high    [ 15 ]      - Active high CS logic.
     *
     *  param master is the master number from 0 to host controller master limit.
     *  param cs is a valid pointer on a struct spi_cs_control is CS line is
     *        emulated through a gpio line, or NULL otherwise.
     */

    /* Note: Implicid Mode-0; e.g. CPOL=0, CPHA=0 -- the only mode supported */
    /* Note: The nRF52 series doesn't support CS pin configuration */

    memset(&spi_cfg, 0, sizeof(spi_cfg));

    spi_cfg.operation = SPI_WORD_SET(8) | SPI_OP_MODE_MASTER 
    //                    | SPI_MODE_CPOL | SPI_MODE_CPHA 
                        | SPI_LINES_SINGLE; 
    spi_cfg.frequency = 1000000;
    spi_cfg.cs = &cs_ctrl;

    printk("%s: master config @ %p:"
            " wordsize(%u), mode(%u/%u/%u)\n", __func__, &spi_cfg,
            SPI_WORD_SIZE_GET(spi_cfg.operation),
            (SPI_MODE_GET(spi_cfg.operation) & SPI_MODE_CPOL) ? 1 : 0,
            (SPI_MODE_GET(spi_cfg.operation) & SPI_MODE_CPHA) ? 1 : 0,
            (SPI_MODE_GET(spi_cfg.operation) & SPI_MODE_LOOP) ? 1 : 0);

    while (1)  { //for (int i=0; i < 2; i++) {

        spi_master_write(spi, &spi_cfg, &tx_data);

        printk("Sent: 0x%02X\n", tx_data);

        spi_master_read(spi, &spi_cfg, &rx_data);

        printk("Received: 0x%02X\n", rx_data);

        printk("Response is %s\n",  (rx_data == 0x5678) ? "correct" : "incorrect");

        k_sleep(K_SECONDS(2));
    }
    printk("done\n");
}
