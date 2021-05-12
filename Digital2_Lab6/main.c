#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int main(void)
{

    uint8_t LED = 2;
    uint8_t modo = 0;
    uint8_t status = 0;
    uint8_t status_p = 0;
    uint8_t semaforo = 0;
    uint8_t a = 0;
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
        //Configurar tipo de entrada
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    while(1)
    {
        // Turn on the LED
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, LED);
        // Delay for a bit

        // Cycle through Red, Green and Blue LEDs
        status_p = status;
        status = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
        if (status == 0 && status_p!=0){
            semaforo = 1;
            modo = 0;
        }
        else {
            //semaforo = 0;
        }

        if (modo<=4){
            modo++;
        }
        else {

        }
        if (semaforo == 1){
        switch (modo){
        case 1:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);
            SysCtlDelay(10000000);
            break;
        case 2:
            a=0;
            while (a<5){
                a++;
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
                SysCtlDelay(1000000);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);
                SysCtlDelay(1000000);
            }

            break;
        case 3:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 10);
            SysCtlDelay(10000000);
            break;
        case 4:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
            SysCtlDelay(10000000);
            break;
        default:
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        }
        }
    }
}
