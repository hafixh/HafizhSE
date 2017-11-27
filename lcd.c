/*
 * lcd.c
 *
 *  Created on: Nov 11, 2017
 *      Author: lenovo
 */
#include "stm32f1xx_hal.h"
#include "device.h"
#include "lcd.h"
void enable()
{
	HAL_GPIO_WritePin(GPIOB,EN_Pin,GPIO_PIN_SET);//set en
	HAL_Delay(3);   // minimal 2ms don't follow databook ;((450ns)<--
	HAL_GPIO_WritePin(GPIOB,EN_Pin,GPIO_PIN_RESET);//clear en
}
void lcd_init()
{
	HAL_GPIO_WritePin(GPIOB,EN_Pin,GPIO_PIN_RESET);
	HAL_Delay(20);
	 //step1
	PORT(0x30);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
	HAL_Delay(5);
	 // step2
	PORT(0x30);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
	HAL_Delay(1);
	// step3
	PORT(0x30);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
	//next init
	PORT(0x20);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
	PORT(0x20);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
	PORT(0x80);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
	PORT(0x00);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();// display on
	PORT(0xE0);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
	PORT(0x00);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable(); // entry mode address inc and cursor shift right
	PORT(0x60);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
	PORT(0x00);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable(); // display clear
	PORT(0x10);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable(); // display clear
}
void lcd_clear(void)
{
	PORT(0x00);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable(); // display clear
	PORT(0x10);
	HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable(); //
}
void lcd_gotoxy(char i,char j)
{
   unsigned char posisi,kar2;
   posisi=(i*0x40)+j;
   //posisi=(i>0?0x40+j:j);
   kar2= posisi & 0xF0;//0xF0
   PORT(kar2);
   HAL_GPIO_WritePin(GPIOB,D7_Pin,GPIO_PIN_SET);
   HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
   posisi= (posisi<<4)|(posisi>>4);     // swap temp
   kar2= posisi & 0xF0;//0xF0
   PORT(kar2);
   HAL_GPIO_WritePin(GPIOB,RS_Pin|RW_Pin,GPIO_PIN_RESET);enable();
}
void lcd_putchar(unsigned char kar)
{
 unsigned char kar2;
 //kar2=(kar|(PORT_LCD&0x0F))& (PORT_LCD|0xF0); //save control in bit 0-3
 //kar2= (kar & 0xF0) + (PORT_LCD &0x0F);
 //CLRBIT(kar2,EN);
 kar2=kar & 0xF0;
 PORT(kar2);HAL_GPIO_WritePin(GPIOB,RS_Pin,1);HAL_GPIO_WritePin(GPIOB,RW_Pin,0);enable(); //
 kar=(kar<<4|kar>>4);
 kar2 = kar & 0xF0;
 PORT(kar2);HAL_GPIO_WritePin(GPIOB,RS_Pin,1);HAL_GPIO_WritePin(GPIOB,RW_Pin,0);enable(); // display clear
}
void lcd_putstr(char *s)
{
	char i=0;
	char c;
	while((c=*(s+(i++)))!=0)
	   lcd_putchar(c);
}

