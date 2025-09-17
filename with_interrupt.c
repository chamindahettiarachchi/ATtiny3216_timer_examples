#include <xc.h>
#include <avr/interrupt.h>
//#include <avr/iotn3216.h>
volatile uint16_t counter = 0;
int main(void) {
     
   PORTA_DIRSET = PIN4_bm; //output for the LED
   
   TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
   TCA0.SINGLE.PER = 3333;//periode FOR ONE MILISECOND
   TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm; //interrupt SETTING
   TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm;//start
   sei();//global interrupt on
    
    while (1) {
}
}

ISR(TCA0_OVF_vect ){
     TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm;
     counter++;
     if(counter >1000){
        PORTA_OUTTGL = PIN4_bm ;//blinking an LED every one second
        counter = 0;
     }
    
}
