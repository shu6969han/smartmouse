
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
		case 0:	//USB无连接

            printf("USB无连接!\r\n");
			break;
		case 1:	//USB键盘
	
            printf("USB Connected-USB KeyBoard\r\n");

			break;
		case 2:	//USB鼠标

             printf("USB Connected-USB han USB Mouse\r\n");

			break; 		
		case 3:	//不支持的USB设备
			
             printf("USB Connected-USB Unknow Device\r\n");
			break; 	 
	} 
}  

//HID重新连接
void USBH_HID_Reconnect(void)
{
	//关闭之前的连接
	USBH_DeInit(&USB_OTG_Core_dev,&USB_Host);	//复位USB HOST
	USB_OTG_StopHost(&USB_OTG_Core_dev);		//停止USBhost
	if(USB_Host.usr_cb->DeviceDisconnected)		//存在,才禁止
	{
		USB_Host.usr_cb->DeviceDisconnected(); 	//关闭USB连接
		USBH_DeInit(&USB_OTG_Core_dev, &USB_Host);
		USB_Host.usr_cb->DeInit();
		USB_Host.class_cb->DeInit(&USB_OTG_Core_dev,&USB_Host.device_prop);
	}
	USB_OTG_DisableGlobalInt(&USB_OTG_Core_dev);//关闭所有中断
	//重新复位USB
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS,ENABLE);//USB OTG FS 复位
	delay_ms(5);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS,DISABLE);	//复位结束  

	memset(&USB_OTG_Core_dev,0,sizeof(USB_OTG_CORE_HANDLE));
	memset(&USB_Host,0,sizeof(USB_Host));
	//重新连接USB HID设备
	USBH_Init(&USB_OTG_Core_dev,USB_OTG_FS_CORE_ID,&USB_Host,&HID_cb,&USR_Callbacks);  
}



int main(void)
{        
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	LED_Init();					//初始化LED  


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
        
		if(bDeviceState==1)//连接建立了
		{ 
			if(USBH_Check_HIDCommDead(&USB_OTG_Core_dev,&HID_Machine))//检测USB HID通信,是否还正常? 
			{ 	    
				USBH_HID_Reconnect();//重连
				printf("USBH_HID_Reconnect1!\r\n");	
				
			}				
			
		}else	//连接未建立的时候,检测
		{
			if(USBH_Check_EnumeDead(&USB_Host))	//检测USB HOST 枚举是否死机了?死机了,则重新初始化 
			{ 	    
				USBH_HID_Reconnect();//重连
				
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




