/*
 * File:   newmain.c
 * Author: kyojeong
 *
 * Created on 2019?12?25?, ?? 7:28
 */
#pragma config OSC = INTIO67      // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = ON       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) not protected from table reads executed in other blocks)


#include <xc.h>
#define _XTAL_FREQ 1000000
void displaynum(int num);
void put(int num);


void initial()
{
   
    T2CON=0b00000111;//16 pre
    OSCCON=0b00110000;//500khz
   
    
    
    CCP1CON=0b00001100;

    put(78);

    TRISB=0b00000001;
    TRISC=0;
    TRISD=0;
    LATD=0b11111111;
    
    RCONbits.IPEN=1;
    INTCONbits.GIE=1;
    
   
    IPR1bits.TMR2IP=1;
    PIR1bits.TMR2IF=0;
    PIE1bits.TMR2IE=1;


}

void motor()
{
    PR2=155;
    TMR2=0;
    int i=15;
    int num=0;
    int k=0;
    while(1){
        displaynum(num);
       
       
        __delay_ms(100);
        
        if(PORTBbits.RB0==1) return;
        if(i==31){
            i=15;
            num=num+1;
        }
      
        
        if(i==23) {
            
            num=num+1;
        }
        if(num==10) num=0;
        put(i);
        i=i+1;
        
        
       
    }
    
    return;
}

void put(int num)
{
        
        if(num%2==1)
            CCP1CONbits.DC1B0=1;
        else 
            CCP1CONbits.DC1B0=0;
        
        if(num%4>=2)
            CCP1CONbits.DC1B1=1;
        else 
            CCP1CONbits.DC1B1=0;
        
        CCPR1L=num/4;
       
}


void displaynum(int num)
{
    if(num==0) LATD=0b10000001;
    if(num==1) LATD=0b11110011;
    if(num==2) LATD=0b01001001;
    if(num==3) LATD=0b01100001;
    if(num==4) LATD=0b00110011;
    if(num==5) LATD=0b00100101;
    if(num==6) LATD=0b00000101;
    if(num==7) LATD=0b11110001;
    if(num==8) LATD=0b00000001;
    if(num==9) LATD=0b00100001;
}


void main()
{
    initial();
    
    
    return;
}
    

void __interrupt (high_priority) Hi_ISR(void)
{
    PIR1bits.TMR2IF=0;
    return ;
}