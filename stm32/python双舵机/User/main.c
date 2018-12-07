
#include "stm32f4xx.h"
#include "./servo/bsp_servo.h"
#include "./usart/bsp_usart.h"
#include "stdio.h"

void Servo_1(double Angel_1);
void Servo_2(double Angle_2);
static double Angle_2 = 90, Angle_1 = 90;

int main(void) 
{
	int cmd=0;
  /*初始化串口*/
  USARTx_Config( 115200 );
	///printf("串口初始化完成\n");
	
  /* 初始化舵机 */
	Servo_Config(); 
  ///printf("舵机初始化完成\n");
  while(1)
  {
		scanf("%d", & cmd);
		if (cmd == 1 && Angle_1 <= 179)
		{	
			Angle_1 += 1;
			Servo_1(Angle_1);
			///printf("一号舵机%d°\n",Angle_1);
		}
		else if (cmd == 2 && Angle_1 >= 1)
		{
			Angle_1 -= 1;
			Servo_1(Angle_1);
			///printf("一号舵机%d°\n",Angle_1);
		}
		else if (cmd == 3 && Angle_2 <= 94)
		{
			Angle_2 += 0.5;
			Servo_2(Angle_2);
			///printf("二号舵机%d°\n",Angle_2);
		}
		else if (cmd == 4 && Angle_2 >= 11)
		{
			Angle_2 -= 0.5;
			Servo_2(Angle_2);
			///printf("二号舵机%d°\n",Angle_2);
		}	
  }

}

void Servo_1(double Angle_1)
{
	u16 Load_1;
	Load_1 = (u16)(( Angle_1+45 )*100/9.0);
	TIM_SetCompare1(TIM5,Load_1); 	
}
void Servo_2(double Angle_2)
{
	u16 Load_2;
	Load_2 = (u16)(( Angle_2+45 )*100/9.0);
	TIM_SetCompare1(TIM2,Load_2); 	
}
