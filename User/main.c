#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_usart.h"
#include <stdio.h>
#include "bps_flash.h"

uint8_t a[4096]={0};
uint8_t b[4096]={0};
void delay_ms(int n)//��ʱ����
{
	int i;
	while (n--)
	{
		for(i=0;i<5520;i++);
	}
}



int main()
{
	uint16_t n=0;
	uint32_t i=0;
	uint32_t ID=0;
	USART_Config();
	printf("����һ��SPI����\n");
	SPI_FLASH_Init();
	ID=SPI_ReadID();//�����豸��FLASH��ID
	printf("ID= %x\n",ID);
	Sector_erase(0);//д������ǰ�������
	WaitnoBUSY();//�ȴ��������
	for(i=0;i<4096;i++)
	{
		if(i%128==0)
		{
			n=0;
		}
		b[i]=n;
		n++;
	}
	i=0;
	FLASH_WriteData(0,b,255);
	WaitnoBUSY();
	FLASH_ReadData(0,a,255);
	for(i=0;i<256;i++)
	{
		printf("%d ",a[i]);
		if(i==10)
		{
			printf("\n");
		}
	}
	printf("����");
		
	
	
	
//	USART_Sendbyte(USART1,0x64);
//	USART_Send_twobyte(USART1,0xff56);
//	USART_Sendarr(USART1,a,10);
//	USART_Sendstr(DEBUG_USARTx,"�Һ�������");
//	printf("���ڲ���");
//	putchar('p');
	
	
	
}


////���մ����жϺ���
//void DEBUG_USART_IRQHandler(void)
//{
//	uint8_t temp;
//	if((USART1->SR&0x20)==0x20)
//	{
//		temp=USART_ReceiveData(USART1);
//		USART_SendData(USART1,temp);
//		while (!USART_GetFlagStatus(USART1,USART_FLAG_TXE));
//	}
//}	



