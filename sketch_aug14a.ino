#include <Event.h>
#include <Timer.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <DS1302.h>

char timerString[ 9 ] = "::::::::" ;
uint8_t i = 0 ;
bool flag = false ;

const int kCePin   = P1_5;  // Chip Enable
const int kIoPin   = P2_6;  // Input/Output
const int kSclkPin = P2_7;  // Serial Clock

DS1302 rtc(kCePin, kIoPin, kSclkPin);
Timer t1 ;
void flagChange() {
  digitalWrite( P1_4, flag ) ;
  flag = !flag ;
} // flagChange()

void printTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();
  sprintf( timerString, "%02d:%02d:%02d", t.hr, t.min, t.sec);
}

void setup()
{
  // put your setup code here, to run once:
  
  pinMode( P1_0, OUTPUT ) ;
  pinMode( P1_1, OUTPUT ) ;
  pinMode( P1_2, OUTPUT ) ;
  pinMode( P1_3, OUTPUT ) ;
  pinMode( P1_4, OUTPUT ) ;
  pinMode( P1_6, OUTPUT ) ;
  pinMode( P1_7, OUTPUT ) ;
  pinMode( P2_3, OUTPUT ) ;
  pinMode( P2_4, OUTPUT ) ;
  pinMode( P2_5, OUTPUT ) ;
  pinMode( P2_6, OUTPUT ) ;
  pinMode( P2_7, OUTPUT ) ;
  pinMode( P1_5, OUTPUT ) ;
  
  digitalWrite( P1_0, LOW ) ;
  digitalWrite( P1_1, LOW ) ;
  digitalWrite( P1_2, LOW ) ;
  digitalWrite( P1_3, LOW ) ;
  digitalWrite( P1_6, LOW ) ;
  digitalWrite( P1_7, LOW ) ;
  digitalWrite( P2_3, LOW ) ;
  digitalWrite( P2_4, LOW ) ;
  digitalWrite( P2_5, LOW ) ;
  digitalWrite( P1_4, LOW ) ;
  
  rtc.writeProtect(false);
  rtc.halt(false);
  
  Time t(2016, 8, 17, 1, 3, 0, Time::kWednesday);
  // t1.every( 60, flagChange ) ;
  // Set the time and date on the chip.
  // rtc.time(t);
  
}

void loop()
{
  t1.update() ;
  uint8_t pinFix[ 8 ] = { 1,2,3,4,5,6,7,0 } ;
  printTime() ;
  for ( int i = 0 ; i < 8 ; ++ i ) {
    digitalWrite( P2_5, pinFix[ i ] & 0x04 ) ;
    digitalWrite( P2_4, pinFix[ i ] & 0x02 ) ;
    digitalWrite( P2_3, pinFix[ i ] & 0x01 ) ;  
    
    switch ( timerString[ i ] ) {
      case '0' :
        digitalWrite( P1_3, LOW ) ;
        digitalWrite( P1_2, LOW ) ;
        digitalWrite( P1_1, LOW ) ;
        digitalWrite( P1_0, LOW ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case '1' :
        digitalWrite( P1_3, LOW ) ;
        digitalWrite( P1_2, LOW ) ;
        digitalWrite( P1_1, LOW ) ;
        digitalWrite( P1_0, HIGH ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case '2' :
        digitalWrite( P1_3, LOW ) ;
        digitalWrite( P1_2, LOW ) ;
        digitalWrite( P1_1, HIGH ) ;
        digitalWrite( P1_0, LOW ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case '3' :
        digitalWrite( P1_3, LOW ) ;
        digitalWrite( P1_2, LOW ) ;
        digitalWrite( P1_1, HIGH ) ;
        digitalWrite( P1_0, HIGH ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case '4' :
        digitalWrite( P1_3, LOW ) ;
        digitalWrite( P1_2, HIGH ) ;
        digitalWrite( P1_1, LOW ) ;
        digitalWrite( P1_0, LOW ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case '5' :
        digitalWrite( P1_3, LOW ) ;
        digitalWrite( P1_2, HIGH ) ;
        digitalWrite( P1_1, LOW ) ;
        digitalWrite( P1_0, HIGH ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case '6' :
        digitalWrite( P1_3, LOW ) ;
        digitalWrite( P1_2, HIGH ) ;
        digitalWrite( P1_1, HIGH ) ;
        digitalWrite( P1_0, LOW ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case '7' :
        digitalWrite( P1_3, LOW ) ;
        digitalWrite( P1_2, HIGH ) ;
        digitalWrite( P1_1, HIGH ) ;
        digitalWrite( P1_0, HIGH ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case '8' :
        digitalWrite( P1_3, HIGH ) ;
        digitalWrite( P1_2, LOW ) ;
        digitalWrite( P1_1, LOW ) ;
        digitalWrite( P1_0, LOW ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case '9' :
        digitalWrite( P1_3, HIGH ) ;
        digitalWrite( P1_2, LOW ) ;
        digitalWrite( P1_1, LOW ) ;
        digitalWrite( P1_0, HIGH ) ;
        digitalWrite( P1_6, LOW ) ;
        digitalWrite( P1_7, LOW ) ;
      break ;
      case ':' :
        digitalWrite( P1_3, HIGH ) ;
        digitalWrite( P1_2, HIGH ) ;
        digitalWrite( P1_1, HIGH ) ;
        digitalWrite( P1_0, HIGH ) ;
        digitalWrite( P1_6, flag ) ;
        digitalWrite( P1_7, !flag ) ;
      break ;
    } // switch
    
    delayMicroseconds( 1000 ) ;
  } // for
}
