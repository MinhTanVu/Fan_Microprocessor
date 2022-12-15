#include <16f877a.h>
#fuses  hs
#device ADC = 10
#DEFINE ENABLE     PIN_C7
#USE DELAY(CLOCK=20M)
#USE RS232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)

int8 temp,nhietdo,tocdo;
int16 value;
int  ttdc;
void kt_captocdo()
{
   if ((temp >=30) && (temp<35)) tocdo=1;
   else if ((temp >=35) && (temp<40)) tocdo=2;
   else if ((temp >=40) && (temp<45)) tocdo=3;
   else if (temp >=45) tocdo=4;
   else if (temp <30) tocdo =0;
}

void main()
{
   setup_adc(adc_clock_internal);
   setup_adc_ports(an0);
   set_adc_channel(0);
   delay_ms(20);
   OUTPUT_LOW(PIN_C3);//CHO PHEP DONG CO CHAY THUAN 
   SETUP_CCP1(CCP_PWM);//DAT CAU HINH CCP1 LA CHAN OUT PWM{DUNG KY THUAT PWM)
   SETUP_TIMER_2(T2_DIV_BY_16,249,1);//THIET LAP CHU KY XUNG PWM=0.8S, CHU KY TIMER 2PR2=249; HE SO CHIA PVTMR2 =16;
   SET_TIMER2(0);//DAT GIA TRI TIMER2
   OUTPUT_HIGH(ENABLE);//CHO PHEP L298   
   VALUE=0;
   TTDC=0;
   TOCDO=0;
   while (true)
   {
       temp = read_adc()/2.046;
       delay_ms(20);
       nhietdo = temp;     
       PUTC(nhietdo);//truyen gia tri nhiet do
       if (nhietdo >= 30) ttdc =1;
       if (ttdc ==1)
       {
       kt_captocdo();
       }
       value = tocdo*250; 
       set_pwm1_duty(value);
   }
}
