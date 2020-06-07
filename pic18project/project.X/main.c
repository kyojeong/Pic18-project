#pragma config OSC = INTIO67    // Oscillator Selection bits (Internal oscillator block, port function on RA6 and RA7)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown Out Reset Voltage bits (Minimum setting)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 1000000
int check = 0;
void put(int num);
void init(){
    TRISC = 0x00;
    PORTC = 0xff;
    TRISA = 0x00;
    PORTA = 0x10;
    TRISD = 0x00;
    LATD = 0x00;
    
    T2CONbits.TMR2ON = 1;
    OSCCON=0b00110000;//500khz
   
    
    TMR2=0;
    CCP1CON=0b00001100;

    put(0);

    TRISB=0b00000001;
    TRISC=0;
    TRISD=0;
    
    RCONbits.IPEN=1;
    INTCONbits.GIE=1;
    
   
    IPR1bits.TMR2IP=1;
    PIR1bits.TMR2IF=0;
    PIE1bits.TMR2IE=1;
}
void put(int num)
{
        
        if(num&&0b00000001==1)
            CCP1CONbits.DC1B0=1;
        else 
            CCP1CONbits.DC1B0=0;
        
        if(INDF0&&0b00000010==2)
            CCP1CONbits.DC1B1=1;
        else 
            CCP1CONbits.DC1B1=0;
        
        CCPR1L=num;
        CCPR1L>>1;
        STATUSbits.C=0;
        CCPR1L>>1;
        STATUSbits.C=0;
}
void music(int k)
{
    int num;
    if(k==0) {
        __delay_ms(300);
        return;
    }
    if(k==1)PR2=238;//do
    if(k==2)PR2=212;//do
    if(k==3)PR2=189;//do
    if(k==4)PR2=178;//do
    if(k==5)PR2=158;//do
    if(k==6)PR2=141;//do
    if(k==7)PR2=125;//do
    if(k==8)PR2=120;//do
    
        num=PR2/2;
        TMR2=0;
        put(num);
    __delay_ms(300);
        num=0;
        TMR2=0;
        put(num);
    return;
}
void star()
{
    __delay_ms(250);
    LATD = 0b00000001;
    music(1);
    LATD = 0b00000001;
    music(1);
    LATD = 0b00010000;
    music(5);
    LATD = 0b00010000;
    music(5);
    LATD = 0b00100000;
    music(6);
    LATD = 0b00100000;
    music(6);
    LATD = 0b00010000;
    music(5);
    LATD = 0b11111111;
    music(0);
    LATD = 0b00001000;
    music(4);
    LATD = 0b00001000;
    music(4);
    LATD = 0b00000100;
    music(3);
    LATD = 0b00000100;
    music(3);
    LATD = 0b00000010;
    music(2);
    LATD = 0b00000010;
    music(2);
    LATD = 0b00000001;
    music(1);
    LATD = 0b11111111;
    music(0);
    LATD = 0b00010000;
    music(5);
    LATD = 0b00010000;
    music(5);
    LATD = 0b00001000;
    music(4);
    LATD = 0b00001000;
    music(4);
    LATD = 0b00000100;
    music(3);
    LATD = 0b00000100;
    music(3);
    LATD = 0b00000010;
    music(2);
    LATD = 0b11111111;
    music(0);
    LATD = 0b00010000;
    music(5);
    LATD = 0b00010000;
    music(5);
    LATD = 0b00001000;
    music(4);
    LATD = 0b00001000;
    music(4);
    LATD = 0b00000100;
    music(3);
    LATD = 0b00000100;
    music(3);
    LATD = 0b00000010;
    music(2);
    LATD = 0b11111111;
    music(0);
    LATD = 0b00000001;
    music(1);
    LATD = 0b00000001;
    music(1);
    LATD = 0b00010000;
    music(5);
    LATD = 0b00010000;
    music(5);
    LATD = 0b00100000;
    music(6);
    LATD = 0b00100000;
    music(6);
    LATD = 0b00010000;
    music(5);
    LATD = 0b11111111;
    music(0);
    LATD = 0b00001000;
    music(4);
    LATD = 0b00001000;
    music(4);
    LATD = 0b00000100;
    music(3);
    LATD = 0b00000100;
    music(3);
    LATD = 0b00000010;
    music(2);
    LATD = 0b00000010;
    music(2);
    LATD = 0b00000001;
    music(1);
    LATD = 0b11111111;
    __delay_ms(250);
    return;
}
//void family(){
//    music(1);
//    music(2);
//    music(3);
//    __delay_ms(300);
//    music(4);
//    music(4);
//    __delay_ms(300);
//    music(5);
//    music(5);
//    __delay_ms(300);
//    music(3);
//    music(5);
//    __delay_ms(300);
//    music(4);
//    __delay_ms(300);
//    music(3);
//    music(4);
//    music(2);
//    music(2);
//    music(3);
//    __delay_ms(300);
//    music(1);
//    music(2);
//    music(3);
//    __delay_ms(300);
//    music(4);
//    music(4);
//    __delay_ms(300);
//    music(5);
//    music(5);
//    __delay_ms(300);
//    music(3);
//    music(5);
//    __delay_ms(300);
//    music(4);
//    __delay_ms(300);
//    music(3);
//    music(4);
//    music(2);
//    music(1);
//    __delay_ms(300);
//    music(0);
//    music(5);
//    music(0);
//    music(8);
//    music(0);
//    music(0);
//    music(7);
//    music(6);
//    music(0);
//    music(5);
//    music(5);
//    music(0);
//    music(3);
//    music(0);
//    music(5);
//    music(0);
//    music(4);
//    music(0);
//    music(3);
//    music(4);
//    music(2);
//    music(2);
//    music(3);
//    music(0);
//    music(4);
//    music(0);
//    music(8);
//    music(0);
//    music(0);
//    music(7);
//    music(6);
//    music(0);
//    music(5);
//    music(5);
//    music(0);
//    music(3);
//    music(0);
//    music(5);
//    music(0);
//    music(4);
//    music(0);
//    music(3);
//    music(4);
//    music(0);
//    music(2);
//    music(1);
//    return;
//    
//}
void light(){
    if((PORTCbits.RC0 == 0) && (PORTCbits.RC4 == 0)){
        LATD = 0b00000001;
        music(1);
    }
    else if((PORTCbits.RC0 == 0) && (PORTCbits.RC5 == 0)){
        LATD = 0b00000010;
        music(2);
    }
    else if((PORTCbits.RC0 == 0) && (PORTCbits.RC6 == 0)){
        LATD = 0b00000100;
        music(3);
    }
    else if((PORTCbits.RC1 == 0) && (PORTCbits.RC4 == 0)){
        LATD = 0b00001000;
        music(4);
    }
    else if((PORTCbits.RC1 == 0) && (PORTCbits.RC5 == 0)){
        LATD = 0b00010000;
        music(5);
    }
    else if((PORTCbits.RC1 == 0) && (PORTCbits.RC6 == 0)){
        LATD = 0b00100000;
        music(6);
    }
    else if((PORTAbits.RA4 == 0) && (PORTCbits.RC4 == 0)){
        LATD = 0b01000000;
        music(7);
    }
    else if((PORTAbits.RA4 == 0) && (PORTCbits.RC5 == 0)){
        LATD = 0b10000000;
        music(8);
    }
    else if((PORTAbits.RA4 == 0) && (PORTCbits.RC6 == 0)){
        LATD = 0b11111111;
        
            star();
            
     }
    else LATD = 0x00;
    PORTC = 0xff;
    PORTA = 0x10;
    LATD = 0x00;
}
void __interrupt (high_priority) Hi_ISR(void)
{
    PIR1bits.TMR2IF=0;
    return ;
}

void main(void) {
    init();
    while(1){
        light();
    }
    return;
}
