/*
 * Copyright (c) 2022 Lars Øvergård
 *
 * Copyright (c) 2020 Circuit Dojo LLC
 * SPDX-License-Identifier: Apache-2.0
 */

 #include <init.h>
 #include <drivers/gpio.h>
 
 #define GPIO0 DT_LABEL(DT_NODELABEL(gpio0))
 #define HPWR_PIN 28
 #define SUSP_PIN 27
 #define FSEL_PIN 29
 #define STBY_PIN 26
 #define PGOOD_PIN 31
 #define PBSTAT_PIN 30
 
 
 static int board_arduboard_nrf9160_charger_init(const struct device *dev)
 {
	 ARG_UNUSED(dev);
 
	 /* Get the device binding */
	 const struct device *gpio = device_get_binding(GPIO0);
	 if (gpio == NULL) {
		 return -ENODEV;
	 }
 
	 /* Configure pin as output and set it high. 
		This will enable the 500mA draw from USB (High) */
	 gpio_pin_configure(gpio, HPWR_PIN, GPIO_OUTPUT_HIGH);
 
	 /* This will keep the charger on, when connected to a source with
	 a higher voltage, then the battery. (Low) */
	 gpio_pin_configure(gpio, SUSP_PIN, GPIO_OUTPUT_LOW);
 
	 /* This will set the buck switching frequency to 1.125MHz (Low) */
	 gpio_pin_configure(gpio, FSEL_PIN, GPIO_OUTPUT_LOW);
 
	 /* This will set the part in a very low quiescent current mode (High) */
	 gpio_pin_configure(gpio, STBY_PIN, GPIO_OUTPUT_LOW);
 
	 /* This pin indicates that all enabled buck regulators have been in 
	 use for atleast 230ms. (Disabled) */
	 gpio_pin_configure(gpio, PGOOD_PIN, GPIO_DISCONNECTED);
 
	 /* This pin can be used to interrupt the microprocessor (Disabled) */
	 gpio_pin_configure(gpio, PBSTAT_PIN, GPIO_DISCONNECTED);
 
	 return 0;
 }
 
 // Should be disabled for low power (CMake)
 /* Needs to be done after GPIO driver init */
 SYS_INIT(board_arduboard_nrf9160_charger_init, POST_KERNEL,
	  CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);
 