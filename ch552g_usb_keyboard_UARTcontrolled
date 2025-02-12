#ifndef USER_USB_RAM
#error "Require USB RAM. Go Tools > USB Setting and pick the 2nd option in the dropdown list"
#endif

//lib include
#include "src/neo/neo.h"
#include "src/userUsbHidKeyboardMouse/USBHIDKeyboardMouse.h"

//app include
#include "src/auto_mode.h"
#include "src/buttons.h"
#include "src/encoder.h"
#include "src/keyboard.h"
#include "src/led.h"
#include "src/util.h"

// Button (Mechnical, left to right)
#define PIN_BTN_1 11
#define PIN_BTN_2 17
#define PIN_BTN_3 16 
#define PIN_BTN_ENC 33

#define ENCODER_A 31
#define ENCODER_B 30



void CH554UART1Alter() 
{
    PIN_FUNC |= bUART1_PIN_X;
    PIN_FUNC |= bUART0_PIN_X;
}
 uint8_t UART1RcvByte( )
{
    while(U1RI == 0);                 
    U1RI = 0;
    return SBUF1
    ;
}
uint8_t  UART0RcvByte( )
{
    while(RI == 0);                    
    RI = 0;
    return SBUF;
}

void UART0SendByte(uint8_t SendDat)
{
        SBUF = SendDat;               
        while(TI ==0);
        TI = 0;
}

void	UARTSetup()
{
    uint32_t x;
    uint8_t x2;
    SM1 = 1;
    PCON = SMOD;
    x = 10 * 16000000 / 38400 / 16;                                      // 16000000 = SYS_FREQ | 38400 BAUDRATE   | If you change the main frequency, be careful not to overflow the value of x
    x2 = x % 10;
    x /= 10;
    if ( x2 >= 5 ) x ++;                                                       //rounding
    TMOD = TMOD & ~ bT1_GATE & ~ bT1_CT & ~ MASK_T1_MOD | bT1_M1;              //0X20, Timer1 as 8-bit auto-reload timer
    T2MOD = T2MOD | bTMR_CLK | bT1_CLK;                                        //Timer1 clock selection
    TH1 = 256-x;
    TR1 = 1;                                                                   //Start timer 1
    TI = 1;
    REN = 1;                                                                   //Serial 0 receive enable
}
void	UART1Setup()
{
    U1SM0 = 0;                         
    U1SMOD = 1;                        
    U1REN = 1;                          
    // should correct for rounding in SBAUD1 calculation  
    SBAUD1 = 256 - 16000000/16/38400;   /////16000000 = SYS_FREQ | 38400 BAUDRATE  
}

void UART1SendByte(uint8_t SendDat)
{
        SBUF1 = SendDat;               
        while(U1TI ==0);
        U1TI = 0;
}
// ===================================================================================
// Main section
// ============================================================================
// Initialize pins
void setup()
{

    CH554UART1Alter(); ///ALT PINs FOR UART | RXD0/TXD0 selects P1.2/P1.3 | RXD1/TXD1 selects P3.4/P3.2 
    UARTSetup(); //// INIT UART0
    UART1Setup(); ////INIT UART1

  // Initialize neopixels
    NEO_init();
    delay(10);
    NEO_clearAll();

  // Go in bootloader more if connected with encoder button pressed
  if (!digitalRead(PIN_BTN_ENC))
  {
    NEO_writeHue(0, NEO_CYAN, NEO_BRIGHT_KEYS); // set led1 to cyan
    NEO_writeHue(1, NEO_BLUE, NEO_BRIGHT_KEYS); // set led2 to blue
    NEO_writeHue(2, NEO_MAG, NEO_BRIGHT_KEYS); //  set led3 to magenta
    NEO_update();                              // update pixels
    BOOT_now();     // jump to bootloader
  }

  buttons_setup(PIN_BTN_1, PIN_BTN_2, PIN_BTN_3, PIN_BTN_ENC);
  keyboard_setup();
  encoder_setup(ENCODER_A, ENCODER_B);
  led_set_mode(LED_FIX);
  USBInit();

}


//Main loop, read buttons
void loop() {

      if (U1RI) {
      char receivedChar = (char)UART1RcvByte(); ////UART1 to rec. commands
      U1RI = 0;                              
      if (receivedChar == '1') {
        Keyboard_press(KEY_TAB);
        delay(10); //a quick capslock press is not recognized on mac
        Keyboard_release(KEY_TAB);    }
      if (receivedChar == '2') {  
        Keyboard_press(KEY_RETURN);  
        delay(10);  
        Keyboard_release(KEY_RETURN);  }
      if (receivedChar == '3') {  
        Keyboard_press(KEY_ESC);  
        delay(10);  
        Keyboard_release(KEY_ESC);    }
       }  

  //task update
  buttons_update();
  //auto_update();    ////
  encoder_update();
  //led_update();

  //debouncing
  delay(5); 
}
