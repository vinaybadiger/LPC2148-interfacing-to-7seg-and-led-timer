#include <lpc214x.h>

#define delay for(int z=0; z<50000; z++)

void init_ext_interrupt(void);
__irq void Ext_ISR(void);

int main (void)
{
	init_ext_interrupt(); // initialize the external interrupt
	IO0DIR = (IO0DIR | 0x0000000F);	/* Configure P0.0-P0.3 as output(used for controlling stepper motor) */
	while(1)
	{
			for(int i = 0; i<12; i++ )	/* Full step rotation in one direction */
			{
				IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
				delay;
				
				IO0PIN = ( (IO0PIN | 0x0000000C) & 0xFFFFFFFC );
				delay;
				
				IO0PIN = ( (IO0PIN | 0x00000004) & 0xFFFFFFF4 );
				delay;
				
				IO0PIN = ( (IO0PIN | 0x00000006) & 0xFFFFFFF6 );
				delay;
				
				IO0PIN = ( (IO0PIN | 0x00000002) & 0xFFFFFFF2 );
				delay;
				
				IO0PIN = ( (IO0PIN | 0x00000003) & 0xFFFFFFF3 );
				delay;
				
				IO0PIN = ( (IO0PIN | 0x00000001) & 0xFFFFFFF1 );
				delay;
				
				IO0PIN = ( (IO0PIN | 0x00000009) & 0xFFFFFFF9 );
				delay;		
			}
			IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
			delay;
			delay;
	
	}
}

void init_ext_interrupt() //Initialize Interrupt
{
			EXTMODE = 0x4; //Edge sensitive mode on EINT2
			EXTPOLAR &= ~(0x4); //Falling Edge Sensitive
			PINSEL0 = 0x80000000; //Select Pin function P0.15 as EINT2
			/* initialize the interrupt vector */
			VICIntSelect &= ~ (1<<16); // EINT2 selected as IRQ 16
			VICVectAddr5 = (unsigned int)Ext_ISR; // address of the ISR
			VICVectCntl5 = (1<<5) | 16; //
			VICIntEnable = (1<<16); // EINT2 interrupt enabled
			EXTINT &= ~(0x4);
}

__irq void Ext_ISR(void) // Interrupt Service Routine-ISR
{
			
	
		
			IO0PIN = ( (IO0PIN | 0x00000000) & 0xFFFFFFFF );
			EXTINT |= 0x4; //clear interrupt
			while(1) ;
			VICVectAddr = 0; // End of interrupt execution
}


/*
#include <lpc214x.h>
#include <stdint.h>

void delay_ms(uint16_t j)
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    // loop to generate 1 milisecond delay with Cclk = 60MHz 
	}
}

int main (void)
{
	IO0DIR = (IO0DIR | 0x0000000F);	// Configure P0.0-P0.3 as output(used for controlling stepper motor) 
	while(1)
	{
			for( uint8_t i = 0; i<12; i++ )	//Full step rotation in one direction 
			{
				IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x0000000C) & 0xFFFFFFFC );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x00000004) & 0xFFFFFFF4 );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x00000006) & 0xFFFFFFF6 );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x00000002) & 0xFFFFFFF2 );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x00000003) & 0xFFFFFFF3 );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x00000001) & 0xFFFFFFF1 );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x00000009) & 0xFFFFFFF9 );
				delay_ms(100);		
			}
			IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
			delay_ms(100);
			delay_ms(2000);
			for( uint8_t j = 0; j<12; j++ )	// Half-step rotation in opposite direction 
			{
				IO0PIN = ( (IO0PIN | 0x00000001) & 0xFFFFFFF1 );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x00000002) & 0xFFFFFFF2 );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x00000004) & 0xFFFFFFF4 );
				delay_ms(100);
				
				IO0PIN = ( (IO0PIN | 0x00000008) & 0xFFFFFFF8 );
				delay_ms(100);
			}
			IO0PIN = ( (IO0PIN | 0x00000001) & 0xFFFFFFF1 );
			delay_ms(100);
			delay_ms(2000);
	}
} */

