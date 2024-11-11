#include <stdbool.h>
#include <stm8s.h>
#include "main.h"
#include "milis.h"


void init_leds(void) {      // inicializace pinů
    GPIO_Init(GPIOB, GPIO_PIN_3, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
}


void set_led(uint8_t led) {                      // Funkce pro nastavení LEDEK podle proměnné
    switch (led) {                                      // provede case x podle hodnoty argumentu "led"
        case 1: 
            GPIO_WriteHigh(GPIOB, GPIO_PIN_5);          // rožne pin5
            GPIO_WriteLow(GPIOB, GPIO_PIN_3);           //zhasne 3 
            GPIO_WriteLow(GPIOB, GPIO_PIN_4);            //zhasne 4 
            break;                                      // ukončení casu
        case 2:
            GPIO_WriteHigh(GPIOB, GPIO_PIN_4);
            GPIO_WriteLow(GPIOB, GPIO_PIN_5);
            GPIO_WriteLow(GPIOB, GPIO_PIN_3);
            break;
        case 3:
            GPIO_WriteHigh(GPIOB, GPIO_PIN_3);
            GPIO_WriteLow(GPIOB, GPIO_PIN_5);
            GPIO_WriteLow(GPIOB, GPIO_PIN_4);
            break;
        default:                                     // pro ošetření dalších stavů tj. kdyby led nebylo 1,2 nebo 3 provede se deafualt
            break;
    }
}

void init(void) {
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);               // nastavení hodin na 16 MHz
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);         // inicializace tlačítka
    init_leds();                                                // inicializace LED
    init_milis();                                                // inicializace časovače
}

int main(void) {

    init();                 // inicializace systémů

    uint8_t btnState;
    uint8_t lastBtnState;     // definice proměnných
    uint8_t ledIndex;       


    while (1) {             // nekonečná smyčka
        btnState = GPIO_ReadInputPin(BTN_PORT, BTN_PIN);

        if (lastBtnState == 0 && btnState == 1) {  //reakce na zmáčnutí tlačítka (když projede while tak se změní hodnota, if se změní až btnstate skočí z 1 na 0)
            ledIndex++;               // do indexu přičte 1
            if (ledIndex > 3) {    //když je index větší jak 3 nastaví se na 1
                ledIndex = 1;
            }
        }

        set_led(ledIndex);              // provede se case podle ledIndexu
        lastBtnState = btnState;            // uložení stavu tlačítka pro příští cyklus
    }
}
