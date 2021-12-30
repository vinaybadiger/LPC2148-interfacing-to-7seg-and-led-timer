#include <lpc214x.h>

#define SIZE 10
int d1[SIZE]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 
int d2[SIZE]={0x003F0000, 0x00060000, 0x005B0000, 0x004F0000, 0x00660000, 0x006D0000, 0x007D0000, 0x00070000, 0x007F0000, 0x006F0000}; 

void pll();
void msecdelay(int x);



int main(void)
{
	int i = 0, j = 0;
	PINSEL0 = 0x00000000; 		
	PINSEL1 = 0x00000000; 		
	IO0DIR = 0x00FF00FF; 			
	
	while(1)
	{
					
			for(i=0;i<SIZE;i++) 
			{ 
				
				IO0SET = d1[i];
										
				for(j=0; j<SIZE; j++)
				{
						IO0PIN = (d1[i] | d2[j]);
						msecdelay(20);
						IO0PIN =  (d1[i] & 0x00FF0000);
				}
							
			}				
			
	}

	return 0;
}


void pll()
{
	PLL0CON = 0x01; 			
	PLL0CFG = 0x24;				
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	
	while(!(PLL0STAT&(1<<10)));	
	PLL0CON = 0x03;				
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
	VPBDIV = 0x01;		
}

void msecdelay(int x)
{
    T0CTCR=0x0;                               
    T0TCR=0x00;                 
    T0PR=59999;                 
    T0TCR=0x02;                 
    T0TCR=0x01;                 
    while(T0TC < x);           
    T0TCR=0x00;                 
    T0TC=0;                     

}
