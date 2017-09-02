
#include "delay.h"  
#include "usart.h"   
#include "led.h"   
#include "string.h"

#include "usbd_hid_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_conf.h"  

#include "usbh_usr.h" 

//#define _HOST_MODE	

USB_OTG_CORE_HANDLE USB_OTG_dev;
extern vu8 usb_device_is_configured; 

USBH_HOST  USB_Host;
USB_OTG_CORE_HANDLE  USB_OTG_Core_dev;
extern HID_Machine_TypeDef HID_Machine;

u8 HOSTDataReady=0;

extern signed char POS_B,POS_X,POS_Y,POS_Z; 
void send_report(void)
{
	uint8_t report_buffer[9] = {0};	
	uint8_t sendstatus=1;
  report_buffer[0] = 0x02;
  report_buffer[1] = POS_B;
  report_buffer[2] = POS_X;
// report_buffer[2] = 1;
  report_buffer[3] = POS_Y;
  report_buffer[4] = POS_Z;

	sendstatus=USBD_HID_SendReport(&USB_OTG_dev, report_buffer, 9);
	 printf("USB sendstatus:%d\r\n",sendstatus);
}

void HIDUser_send_report(void)
{
	uint8_t report_buffer[8] = {0};	
	uint8_t sendstatus=1;

  report_buffer[0] = 0x00;
  report_buffer[1] = 0x02;
  report_buffer[2] = 0x03;
  report_buffer[3] = 0x04;
  report_buffer[4] = 0x05;
  report_buffer[5] = 0x06;
  report_buffer[6] = 0x07;
  report_buffer[7] = 0x08;


	sendstatus=USBD_HID_User_SendReport(&USB_OTG_dev, report_buffer,8);
	 printf("USB sendstatus:%d\r\n",sendstatus);
}

void USBH_Msg_Show(u8 msgx)
{

	switch(msgx)
	{
		case 0:	//USB������

            printf("USB������!\r\n");
			break;
		case 1:	//USB����
	
            printf("USB Connected-USB KeyBoard\r\n");

			break;
		case 2:	//USB���

             printf("USB Connected-USB han USB Mouse\r\n");

			break; 		
		case 3:	//��֧�ֵ�USB�豸
			
             printf("USB Connected-USB Unknow Device\r\n");
			break; 	 
	} 
}  

//HID��������
void USBH_HID_Reconnect(void)
{
	//�ر�֮ǰ������
	USBH_DeInit(&USB_OTG_Core_dev,&USB_Host);	//��λUSB HOST
	USB_OTG_StopHost(&USB_OTG_Core_dev);		//ֹͣUSBhost
	if(USB_Host.usr_cb->DeviceDisconnected)		//����,�Ž�ֹ
	{
		USB_Host.usr_cb->DeviceDisconnected(); 	//�ر�USB����
		USBH_DeInit(&USB_OTG_Core_dev, &USB_Host);
		USB_Host.usr_cb->DeInit();
		USB_Host.class_cb->DeInit(&USB_OTG_Core_dev,&USB_Host.device_prop);
	}
	USB_OTG_DisableGlobalInt(&USB_OTG_Core_dev);//�ر������ж�
	//���¸�λUSB
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS,ENABLE);//USB OTG FS ��λ
	delay_ms(5);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS,DISABLE);	//��λ����  

	memset(&USB_OTG_Core_dev,0,sizeof(USB_OTG_CORE_HANDLE));
	memset(&USB_Host,0,sizeof(USB_Host));
	//��������USB HID�豸
	USBH_Init(&USB_OTG_Core_dev,USB_OTG_FS_CORE_ID,&USB_Host,&HID_cb,&USR_Callbacks);  
}



int main(void)
{        
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED  


	printf("Hello USB Mouse!\r\n");
  
	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_HID_cb, &USR_cb);
	
	#ifdef _HOST_MODE	
	USBH_Init(&USB_OTG_Core_dev,USB_OTG_HS_CORE_ID,&USB_Host,&HID_cb,&USR_Callbacks); 
	#endif	
//	delay_ms(1800);
	
	while (1)
	{	
     //Slave
		if (usb_device_is_configured && HOSTDataReady==1)
		{
			HOSTDataReady=0;
			send_report();
		//	printf("USB Mouse send_report!\r\n");
		}
	 if (usb_device_is_configured)
		{
		//		printf("usb_device_is_configured ee!\r\n");
	//	  HIDUser_send_report();
			send_report();
		}
		
	#ifdef _HOST_MODE	
		//Host
		USBH_Process(&USB_OTG_Core_dev, &USB_Host);
        
		if(bDeviceState==1)//���ӽ�����
		{ 
			if(USBH_Check_HIDCommDead(&USB_OTG_Core_dev,&HID_Machine))//���USB HIDͨ��,�Ƿ�����? 
			{ 	    
				USBH_HID_Reconnect();//����
				printf("USBH_HID_Reconnect1!\r\n");	
				
			}				
			
		}else	//����δ������ʱ��,���
		{
			if(USBH_Check_EnumeDead(&USB_Host))	//���USB HOST ö���Ƿ�������?������,�����³�ʼ�� 
			{ 	    
				USBH_HID_Reconnect();//����
				
				printf("USBH_HID_Reconnect2!\r\n");
			}			
		}
	#endif	
		
		
		//led
		#ifdef _VCCGND
		LED0 = ~LED0;
		#else
		LED0 = ~LED0;
		LED1 = ~LED1;
		#endif
	delay_ms(100);
			printf("System Running!\r\n");	
	}		
}




