#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int main(void)
{

    //Creamos las variables necesarias
    uint8_t LED = 2;
    uint8_t modo = 0;
    uint8_t status = 0;
    uint8_t status_p = 0;
    uint8_t semaforo = 0;
    uint8_t a = 0;
    uint8_t b = 0;

    //Configuracion del reloj a utilizar, en este caso se utiliza el de /4
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //Se activa el puerto F

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //Se confguran como salida los LEDS

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4); //Config de entrada para boton de la tiva
        //Configurar tipo de entrada
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    while(1)
    {
        //Se utiliza lo siguiente para generar un antirrebote en el boton y unicamente cuando lo presione (flanco +) realiza la accion
        status_p = status;
        status = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
        if (status == 0 && status_p!=0){
            semaforo = 1;
            modo = 0;
        }


        //Se aumenta continuamente el contador modo hasta llegqar a 4, se utiliza en el switch
        if (modo<=4){
            modo++;
        }
        else {

        }
        if (semaforo == 1){
            //Se hace un switch de modo en donde cada modo es un modo del semaforo
        switch (modo){
        case 1: //Verde -- 8
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);
            SysCtlDelay(10000000);
            break;
        case 2:  //Verde Parpadeante -- 8 y 0
            a=0;
            while (a<5){ //Prpadea 5 veces, por lo que 5 veces se apaga y se enciente con un delay de por medio
                a++;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
                SysCtlDelay(1000000);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);
                SysCtlDelay(1000000);
            }

            break;
        case 3: //Amarillo -- rojo+verde=2+8=10
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 10);
            SysCtlDelay(10000000);
            break;
        case 4: //Rojo -- 2
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
            SysCtlDelay(10000000);
            break;
        default: //Finalmente se queda apagado
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        }
        }
    }
}

//Rutina de delay hecha a "mano"

void RutinaDelay(tiempo){
    for (b=0; b<tiempo; b++){

    }
}
