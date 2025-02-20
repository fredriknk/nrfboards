# Copyright (c) 2019 Nordic Semiconductor ASA.
# SPDX-License-Identifier: Apache-2.0

if(CONFIG_BOARD_ARDUFOX_NRF9160)
  zephyr_library()
  # Include this file, if a faster charge time is wanted
  if(CONFIG_REGULATOR)
    zephyr_library_sources(regulator.c)
  endif()
endif()
