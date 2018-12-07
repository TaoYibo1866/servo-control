
#include "./servo/bsp_servo.h"


static void TIM5_GPIO_Config(void) 
{
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOH, ENABLE); 
		
	
		/*BREATH_LED1*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
		GPIO_PinAFConfig(GPIOH,GPIO_PinSource10,GPIO_AF_TIM5);
		GPIO_Init(GPIOH, &GPIO_InitStructure);	    
}
static void TIM2_GPIO_Config(void) 
{
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_AHB1PeriphClockCmd ( RCC_AHB1Periph_GPIOA, ENABLE); 
		
	
		/*BREATH_LED1*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2);
		GPIO_Init(GPIOA, &GPIO_InitStructure);	    
}

static void TIM5_Mode_Config(u16 per , u8 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); 

	
  TIM_TimeBaseStructure.TIM_Period = (per-1);      					//����ʱ����0������ TIM_Period+1 ��Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = (psc-1);	    			//����Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);	
	
	
	/*PWMģʽ����*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
  TIM_OCInitStructure.TIM_Pulse = Init_Pulse_1;	  												//���ó�ʼPWM������Ϊ0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ LED����
  
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);	 //ʹ��ͨ��
  
	/*ʹ��ͨ������*/
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM5, ENABLE);			//ʹ��TIM���ؼĴ���ARR

	// �����������ж�
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
	
	TIM_CtrlPWMOutputs(TIM5,ENABLE);
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM5, ENABLE);	
}

static void TIM2_Mode_Config(u16 per , u8 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 

	
  TIM_TimeBaseStructure.TIM_Period = (per-1);      					//����ʱ����0������ TIM_Period+1 ��Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = (psc-1);	    			//����Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	
	
	
	/*PWMģʽ����*/
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ�����
  TIM_OCInitStructure.TIM_Pulse = Init_Pulse_2;	  												//���ó�ʼPWM������Ϊ0	
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�͵�ƽ LED����
  
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��
  
	/*ʹ��ͨ������*/
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);			//ʹ��TIM���ؼĴ���ARR

	// �����������ж�
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM2, ENABLE);	
}

void Servo_Config(void)
{

	TIM5_GPIO_Config();
	TIM2_GPIO_Config();
	
	TIM5_Mode_Config(20000 ,90);
	TIM2_Mode_Config(20000 ,90);
		
}

/*********************************************END OF FILE**********************/
