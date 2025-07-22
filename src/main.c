#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>

#define STEP_NODE DT_ALIAS(stepper1)

const struct pwm_dt_spec pwm_dev = PWM_DT_SPEC_GET(STEP_NODE);
const struct gpio_dt_spec dir = GPIO_DT_SPEC_GET(STEP_NODE, dir_gpios);

int main(void)
{
    if (!device_is_ready(pwm_dev.dev)) {
        printk("Device not ready\n");
        return 0;
    }
    if (!device_is_ready(dir.port) ) {
		printk("GPIO not ready\n");
	};
    gpio_pin_configure_dt(&dir, GPIO_OUTPUT);

    printk("Starting PWM on TIM3 CH1...\n");
    
    /* 1 kHz (1000 μs period), 50% duty (500 μs) */
    gpio_pin_set_dt(&dir, 1);
    pwm_set_dt(&pwm_dev,PWM_USEC(1000), PWM_USEC(300));


    return 0;
}
