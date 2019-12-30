/*
 * Copyright (c) 2019 - Callender-Consulting. LLC
 * 
 */
#include <zephyr.h>
#include <sys/printk.h>

#include "spi_slave.h"


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void spi_slave_thread(void * id, void * unused1, void * unused2)
{
    printk("%s\n", __func__);

    spi_slave_init();

    while (1) { /* spin */}
}

K_THREAD_DEFINE(spi_slave_id, STACKSIZE, spi_slave_thread, 
                NULL, NULL, NULL, PRIORITY, 0, K_NO_WAIT);
