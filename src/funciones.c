#include "../lib/conf.h"
#include "../lib/lib.h"
#include "../lib/avr_api.h"
#include <avr/interrupt.h>
#include <avr/io.h>

void f_inicio_mcu(void) {
    GpioInitStructure_AVR  voltaje_bat, leds, buzz;
    SystickInitStructure_AVR systick;
    ExternalInterruptInitStructure_AVR interrupcion;

    voltaje_bat.modo = avr_GPIO_mode_Input;
    voltaje_bat.port = VOLTAJE_BAT_PORT;
    voltaje_bat.pines = VOLTAJE_BAT_PIN;
    init_gpio(voltaje_bat);

    leds.modo = avr_GPIO_mode_Output;
    leds.port = LEDS_PORT;
    leds.pines = LEDS_PIN;
    init_gpio(leds);

    buzz.modo = avr_GPIO_mode_Output;
    buzz.port = BUZZ_PORT;
    buzz.pines = BUZZ_PIN;
    init_gpio(buzz);

    //config de las interrupcion externas
    interrupcion.interrupcion = avr_INT0;
    interrupcion.modo = avr_ext_int_lowlevel;
    interrupcion.avr_ext_interrupt_handler = interrupt_handler;
    init_extern_interrupt(interrupcion);



    //config del timer
 //    systick.timernumber = avr_TIM0;
 //    systick.time_ms = 2000;
 //    systick.avr_systick_handler = f_systick;
    //
    sei();

}

void f_interrupt_handler(void) {
    LEDS = 0;
    EIMSK &= ~(1 << 0);
}

void activar_indicador_correcto(void) {
    LEDS = 1;
}

char leer_bat(void) {
    char voltaje = VOLTAJE_BAT;
    return voltaje;
}

