/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

/* positions of a bit in state variable are mapped to each RGB color */
#define RED_BIT 1
#define GREEN_BIT 2
#define BLUE_BIT 4

unsigned int state;       // state is used to choose which colors get turned on
static bool volatile update_rgb_led_flag; // set by T2 interrupt,cleared by main

/*
void T2_Interrupt_Callback(uint32_t status, uintptr_t context)
{
    LED_RED_Toggle();
}
*/
/* Set the RGB LED on/off based on the value of state variable */
void update_rgb_led() {
    //RED
    if(state & RED_BIT)
        RGB_R_Clear();  //RGB LED's are active low
    else
        RGB_R_Set();            
    //GREEEN
    if(state & GREEN_BIT)
        RGB_G_Clear();
    else
        RGB_G_Set();            
    //BLUE
    if(state & BLUE_BIT)
        RGB_B_Clear();        
    else
        RGB_B_Set();
}

/* Handle the applications part of a T2 interrupt. Resetting the flag etc 
 * get done in TIMER_2_InterruptHandler() which is called by the ISR, which 
 * seems like overkill in this situation but helps organise code  ************/
void T2_Interrupt_Callback(uint32_t status, uintptr_t context)
{
    /* let main know T2 has timed out */
    update_rgb_led_flag = true;    
}


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );

    /* Initialize variables */
    update_rgb_led_flag = false;
    /* Start with RGB = white */
    state = 7;    
    update_rgb_led();
    
    /* Register T2 Callback and start T2 */
    TMR2_CallbackRegister(T2_Interrupt_Callback, NULL);
    TMR2_Start();    
        
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
        /* If T2 has timed out update RGB LED*/
        if (update_rgb_led_flag == true)
        {                        
            update_rgb_led();
            /* increment state so RGB led goes through the colors */
            state++;
            if(state>7)
                state=0;
            /* clear the flag from T2 timeout */
            update_rgb_led_flag = false;
            LED_R_Clear();
        }                
    }
    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

