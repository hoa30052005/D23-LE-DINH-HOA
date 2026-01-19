
#include "GPIO.h"
#include "stm32f10x.h"                  // Device header



int main(){
	configGPIO(GPIOA);
	while(1){
	Blink_Led(GPIOA);
	
	}
}