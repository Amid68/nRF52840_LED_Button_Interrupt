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
#include "buttons.h"
#include "leds.h"

#define SLEEP_TIME_MS (10 * 60 * 1000)  // 10 minutes

void main(void)
{
    init_leds();
    init_buttons();

    while (1) {
        k_msleep(SLEEP_TIME_MS);
    }
}

