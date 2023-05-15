#ifndef arduino_fun_h
#define arduino_fun_h
void delay(uint32_t ms);
typedef enum gpio
{
    output,
    input,
    input_pullup,
    input_pulldown
    /* data */
}mode;
void pinMode(uint32_t pin, mode val);
#endif
