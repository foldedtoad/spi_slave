cmake_minimum_required(VERSION 3.13.1)

set(BOARD nrf52_pca10040)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(spi_master)

target_sources(app PRIVATE main.c)
target_sources(app PRIVATE spi_master.c)

target_include_directories(app PRIVATE ./)
