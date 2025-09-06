#include "stdint.h"

struct PortPin
{
    volatile uint8_t* port;
    uint8_t pin;
};

PortPin pinMap(int digitalPin)
{
    static volatile uint8_t* ports[] = {
        &PORTE, &PORTE, &PORTE, &PORTE, &PORTG, &PORTE, &PORTH, &PORTH,
        &PORTH, &PORTH, &PORTB, &PORTB, &PORTB, &PORTB, &PORTJ, &PORTJ,
        &PORTH, &PORTH, &PORTD, &PORTD, &PORTK, &PORTK, &PORTA, &PORTA,
        &PORTA, &PORTA, &PORTA, &PORTA, &PORTA, &PORTA, &PORTC, &PORTC,
        &PORTC, &PORTC, &PORTC, &PORTC, &PORTC, &PORTC, &PORTD, &PORTG,
        &PORTG, &PORTG, &PORTL, &PORTL, &PORTL, &PORTL, &PORTL, &PORTL,
        &PORTL, &PORTL, &PORTB, &PORTB, &PORTB, &PORTB
    };
    static const uint8_t pinNumbers[] = {
        0, 1, 4, 5, 6, 3, 3, 4,
        5, 6, 4, 5, 6, 7, 1, 0,
        1, 0, 3, 2, 1, 0, 0, 1,
        2, 3, 4, 5, 6, 7, 7, 6,
        5, 4, 3, 2, 1, 0, 7, 2,
        1, 0, 7, 6, 5, 4, 3, 2,
        1, 0, 3, 2, 1, 0
    };

    if (digitalPin < 0 || digitalPin >= 53)
    {
        return {nullptr, 0};                      // Invalid pin
    }

    return {ports[digitalPin], pinNumbers[digitalPin]};
}

void writePin(int digitalPin, bool value)
{
    PortPin portPin = pinMap(digitalPin);
    if (portPin.port != nullptr)
    {
        *(portPin.port - 1) |= (1 << portPin.pin); // Set as output

        if (value)
        {
            *(portPin.port) |= (1 << portPin.pin); // Set the pin high
        }
        else
        {
            *(portPin.port) &= ~(1 << portPin.pin); // Set the pin low
        }
    }
}