 
#define F_CPU 3333333UL
#include <avr/io.h>
#include <avr/interrupt.h>
volatile int counter1 = 0;
volatile int counter2 = 0;



ISR(TCA0_LUNF_vect) {                
    TCA0.SPLIT.INTFLAGS = TCA_SPLIT_LUNF_bm;
    counter1 ++;
    if(counter1 > 10){
        counter1 = 0;
       PORTA.OUTTGL = PIN4_bm; 
    }
                 
}

ISR(TCA0_HUNF_vect) {                  
    TCA0.SPLIT.INTFLAGS = TCA_SPLIT_HUNF_bm; 
     counter2 ++;
    if(counter2 > 10){
        counter2 = 0;
       PORTA.OUTTGL = PIN5_bm; 
    }
}

int main(void) {
    // Outputs for demo
    PORTA.DIRSET = PIN4_bm | PIN5_bm;

    // 1) Put TCA0 into SPLIT mode
    TCA0.SPLIT.CTRLD = TCA_SPLIT_SPLITM_bm;

    // 2) Choose clock (here: /64 -> 4 MHz / 64 = 62_500 Hz)
    TCA0.SPLIT.CTRLA = TCA_SPLIT_CLKSEL_DIV1024_gc;  // don't enable yet

    // 3) Set independent periods (PER = desired_ticks - 1, 8-bit)
    //    f = f_clk / (prescaler * (PER+1))
    TCA0.SPLIT.LPER = 255;   
    TCA0.SPLIT.HPER = 100;  

    // 4) Enable interrupts for each half you use
    TCA0.SPLIT.INTCTRL = TCA_SPLIT_LUNF_bm | TCA_SPLIT_HUNF_bm;

    // 5) Start the timer
    TCA0.SPLIT.CTRLA |= TCA_SPLIT_ENABLE_bm;

    sei();
    while (1) { }
}
