
#include <xc.h>
int main(void) {
    /* Replace with your application code */
    uint16_t counter = 0;
   PORTA_DIRSET = PIN4_bm;
   
   
   TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
   
   TCA0.SINGLE.PER = 3333;//periode FOR ONE MILISECOND
   
   TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm; //interrupt SETTING
   
   TCA0.SINGLE.CTRLA = TCA_SINGLE_ENABLE_bm;//start
    
    while (1) {
        
        //POLING METHOD 
        if(TCA0.SINGLE.INTFLAGS & TCA_SINGLE_OVF_bm){
           TCA0.SINGLE.INTFLAGS |= TCA_SINGLE_OVF_bm;
           counter ++;
           if(counter >= 1000){
               counter = 0;
              PORTA_OUTTGL = PIN4_bm ;
        }
        
    }
   
}//END OF WHILE(1)
}//END OF MAIN()
