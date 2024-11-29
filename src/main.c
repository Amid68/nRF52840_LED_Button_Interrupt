/*
 * @file main.c
 * @brief Button interrupt example for the nRF52840 DK.
 *
 * This file contains the source code for a sample application that demonstrates 
 * how to use the GPIO driver to configure a button as an input and an LED as an output. 
 * The application will toggle the LED state when the button is pressed.
 * 
 * @author Ameed Othman
 * @date 2024-11-29
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 10*60*1000

#define SW0_NODE DT_ALIAS(sw0)
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void button_pressed(const struct device *dev, struct gpio_callback * cb, uint32_t pins) {
        gpio_pin_toggle_dt(&led);
}

static struct gpio_callback button_cb_data;

int main(void)
{
	int ret;

	if (!device_is_ready(led.port)) {
		return -1;
	}

	if (!device_is_ready(button.port)) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return -1;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		return -1;
	}

        ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
        gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
        gpio_add_callback(button.port, &button_cb_data);

	while (1) {
		k_msleep(SLEEP_TIME_MS);
	}
}
