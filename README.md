
# Zephyr + nRF52 PCA10040

## Overview

This example project give a simple template for constructing a 'SPI Slave' device.
This allows the PCA10040 board to appear to a 'SPI Master' system (PC, RasPi, etc.) as a SPI device. 

From this start, you can add your own unique command/response sequences.

Be forewarned, this is a rather complex project to setup and run. That being said, it is also an interesting project in that it allows complex functionality to be exposed via an SPI interface.  Sensor hubs and communications protocol engines are two ideas which come to mind.


## Requirements

This project is built with Zephyr Version 2.1.99.

This project requires elements not included in the Nordic PCA10040 kit which must be provided by the user:

* Host computer or system to act as SPI Master.
* Software on host to initiate SPI transactions.
* Cables to connect host to PCA1004 board P3 header.
* Logic analyzer or other SPI transaction protocol tracing facility. (optional, but really useful)
* 1x4 0.1" header, or longer, to connect Logic Analyzer to PCA10040's empty holes for J3  (optional)


## Hardware Setup

The first setup item is to defeat the PCA10040 on-board LED and button devices.  This is easily accomplished by jumpering between header P5 Pin 6 (DETECT) and one of the ground pins

Probably the easiest way to test is with a PC-based SPI interface adapter.
In this case the Total Phase "Aardvark I2C/SPI" adapter with the "Control Center" program for Linux running on Ubuntu 18.04 was used.

Alternatively, you can use a Raspberry-Pi to act as the SPI Master. This document will not describe the setup for this, but it is well-documented on the internet: google's your friend.

As the PCA10040 support the Segger J-Link debugger software, it is assumed that will be use here as well.  The Segger RTT (Logging over J-Link) is also configured in the prj.conf, but not used in this particular example.


```
	Signal  GPIO    Header
    SCK     P0.18   P3-18
    MOSI    P0.17   P3-17 
    MISO    P0.16   P3-16 
    CS      P0.15   P3-15 
```

## Building and Running

The build method follows that described in the Zephyr on-line pages.
The easiest way to configure the build is to use the "configure.sh" script (for Linux & OS-X).

To run, first download the firmware to the PCA10040. This project was developed using the Ozone debugger from Segger, but gdb may also be used.

The firmware will initialize and post a SPI read in anticipation of an incoming request: this will wait indefinitely until either an request arrives over the SPI bus or the firmware is halted in the debugger.

On the host side, start whatever program you have to generate a SPI transaction (request).  As mentioned before, this project was developed using the USB-based Aardvark 12C/SPI adapter connect a Ubuntu 18.04 host.  The host sends a 16-bit request which contains 0x1234.  The firmware will respond with a 16-bit reply of 0x5678.  The firmware then reposts a SPI Read, thereby repeating the request/response cycle.


## Sample Output


