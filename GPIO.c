
```
#include "gpio.h"


void configGPIO(GPIO_TypeDef* GPIOx){     // cấu hình cho GPIO mình muốn
	  
	   if (GPIOx == GPIOA) RCC->APB2ENR |= 0x04;    // cấp xung clock 
    else if (GPIOx == GPIOB) RCC->APB2ENR |= 0x08;  
    else if (GPIOx == GPIOC) RCC->APB2ENR |= 0x10;
  
	 

        GPIOx->CRL =0x11111111;           //cấp mode speed cho các 0-7 

			 GPIOx->CRH  =0x11111111;     //cấp mode speed cho các 8-15
		
	}
	
   	
	
	


	void delay(int time){            
		int i,j;
		for(i=0;i<time;i++){
			for(j=0;j<0x2aff;j++);
	}
}


 void Blink_Led(GPIO_TypeDef* GPIOx){
	int mang[9]={0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF};
	  int i;
	 for(i=0;i<9;i++){
		  GPIOx->ODR = mang[i];
		 delay(100);
	 }
	 
	 
 }
```



