#include <16f877a.h>
#fuses  hs

#USE DELAY(CLOCK=20M)
#USE RS232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

#define ledblue        pin_b0
#define ledpink        pin_b1
#define lcd_enable_pin pin_e2
#define lcd_rw_pin     pin_e1
#define lcd_rs_pin     pin_e0
#define lcd_data4      pin_d4
#define lcd_data5      pin_d5
#define lcd_data6      pin_d6
#define lcd_data7      pin_d7
#include <lcd.c>

int8 tam,tocdo;
int  ttdc;  
void kt_captocdo()
{
   if ((tam >=30) && (tam<35)) tocdo=1;
   else if ((tam >=35) && (tam <40)) tocdo=2;
   else if ((tam >=40) && (tam <45)) tocdo=3;
   else if (tam >=45) tocdo=4;
   else if (tam <30) tocdo =0;
}

void main()
{
   set_tris_b(0x03);
   port_b_pullups(true);
   lcd_init();
   lcd_gotoxy(1,1);
   printf(lcd_putc, "MOTOR");
   while (true)
   {
      kt_captocdo();
      lcd_gotoxy(16,1);
      printf(lcd_putc, "%U",tocdo);
      if (kbhit() == 1)
      {
         tam = getc();
         if (tam>=30) 
         {           
            output_high(ledpink);
            output_low(ledblue);
            lcd_gotoxy(1,2);
            printf(lcd_putc, "HOT");              
            lcd_gotoxy(6,2);
            printf(lcd_putc,"%U",tam);  
            lcd_gotoxy(13,2);
            printf(lcd_putc, "    ");
         }
         else 
         {
            output_low(ledpink);
            output_high(ledblue);
            lcd_gotoxy(1,2);
            printf(lcd_putc, "   ");              
            lcd_gotoxy(6,2);
            printf(lcd_putc,"%U",tam);  
            lcd_gotoxy(13,2);
            printf(lcd_putc,"COLD");
         }        
      }
   }
}
