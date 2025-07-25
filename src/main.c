#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>

#include <zephyr/kernel.h>
#include <zephyr/drivers/pwm.h>

#define STEP_NODE DT_ALIAS(stepper1)

const struct pwm_dt_spec pwm_dev = PWM_DT_SPEC_GET(STEP_NODE);
const struct gpio_dt_spec dir = GPIO_DT_SPEC_GET(STEP_NODE, dir_gpios);
const struct gpio_dt_spec limit_left = GPIO_DT_SPEC_GET_BY_IDX(STEP_NODE, limit_gpios,0);
const struct gpio_dt_spec limit_right = GPIO_DT_SPEC_GET_BY_IDX(STEP_NODE, limit_gpios,1);


int main(void)
{
    if (!device_is_ready(pwm_dev.dev)) {
        printk("Device not ready\n");
        return 0;
    }
    if (!device_is_ready(dir.port) || !device_is_ready(limit_left.port)){
		printk("GPIO not ready\n");
	};
    gpio_pin_configure_dt(&dir, GPIO_OUTPUT);
    gpio_pin_configure_dt(&limit_left, GPIO_INPUT);
    gpio_pin_configure_dt(&limit_right, GPIO_INPUT);
    
    /* 1 kHz (1000 μs period), 50% duty (500 μs) */
    gpio_pin_set_dt(&dir, 1);
    pwm_set_dt(&pwm_dev,PWM_USEC(1000), PWM_USEC(500));

    while(1) {

        int val_left = gpio_pin_get_dt(&limit_left);
        int val_right = gpio_pin_get_dt(&limit_right);
        if (val_left==1){
            gpio_pin_set_dt(&dir, 0);
            printk("limit_rleft_pressed__direction changed\n");}
        if (val_right==1){
            gpio_pin_set_dt(&dir, 1);
            printk("limit_right_pressed__direction changed\n");
        }
    }
    
    return 0;
}
