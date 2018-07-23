#include <application.h>

// LED instance
bc_led_t led;

// Button instance
bc_button_t button;
uint16_t event_count = 0;

// Lora modem instance
bc_cmwx1zzabz_t lora;

void transmit_button_task(void *param)
{
    (void) param;

    if (!bc_cmwx1zzabz_is_ready(&lora))
    {
        bc_scheduler_plan_current_now();
        return;
    }

    bc_scheduler_unregister(bc_scheduler_get_current_task_id());

    bc_cmwx1zzabz_send_message(&lora, &event_count, sizeof(event_count));
}

void button_event_handler(bc_button_t *self, bc_button_event_t event, void *event_param)
{
    if (event == BC_BUTTON_EVENT_PRESS)
    {
        event_count++;

        bc_scheduler_register(transmit_button_task, NULL, 0);
    }
}

void lora_event_handler(bc_cmwx1zzabz_t *self, bc_cmwx1zzabz_event_t event, void *event_param)
{
    (void) event_param;

    if (event == BC_CMWX1ZZABZ_EVENT_JOIN_SUCCESS)
    {
        bc_led_set_mode(&led, BC_LED_MODE_OFF);
    }
    else if (event == BC_CMWX1ZZABZ_EVENT_ERROR)
    {
        bc_led_set_mode(&led, BC_LED_MODE_BLINK);
    }
    else if (event == BC_CMWX1ZZABZ_EVENT_JOIN_ERROR)
    {
        bc_led_set_mode(&led, BC_LED_MODE_BLINK);
    }
    else if (event == BC_CMWX1ZZABZ_EVENT_SEND_MESSAGE_START)
    {
        bc_led_set_mode(&led, BC_LED_MODE_ON);
    }
    else if (event == BC_CMWX1ZZABZ_EVENT_SEND_MESSAGE_DONE)
    {
        bc_led_set_mode(&led, BC_LED_MODE_OFF);
    }
    else if (event == BC_CMWX1ZZABZ_EVENT_MESSAGE_RECEIVED)
    {
        bc_led_pulse(&led, 800);
    }
}

void application_init(void)
{
    // Initialize LED
    bc_led_init(&led, BC_GPIO_LED, false, false);

    bc_module_battery_init();

    // Initialize button
    bc_button_init(&button, BC_GPIO_BUTTON, BC_GPIO_PULL_DOWN, false);
    bc_button_set_event_handler(&button, button_event_handler, NULL);

    // Initialize LoRa
    bc_cmwx1zzabz_init(&lora, BC_UART_UART1);
    bc_cmwx1zzabz_set_event_handler(&lora, lora_event_handler, NULL);

    bc_cmwx1zzabz_set_band(&lora, BC_CMWX1ZZABZ_CONFIG_BAND_EU868);
    bc_cmwx1zzabz_set_class(&lora, BC_CMWX1ZZABZ_CONFIG_CLASS_A);
    bc_cmwx1zzabz_set_mode(&lora, BC_CMWX1ZZABZ_CONFIG_MODE_OTAA);

    bc_cmwx1zzabz_join(&lora);

    bc_led_set_mode(&led, BC_LED_MODE_ON);
}
