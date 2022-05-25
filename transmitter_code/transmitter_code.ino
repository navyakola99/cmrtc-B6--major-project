#include <VirtualWire.h>
char *controller;
int pushButton = 8;
int BUZZER = 6;
void setup() {
Serial.begin(9600);
//vw_set_ptt_inverted(true); //
vw_set_tx_pin(12);
vw_setup(4000);// speed of data transfer Kbps
delay(100);

 pinMode(pushButton, INPUT_PULLUP);
pinMode(BUZZER,OUTPUT);
digitalWrite(BUZZER,HIGH);
delay(500);
digitalWrite(BUZZER,LOW);
}
void loop() {
int buttonState = digitalRead(pushButton);
Serial.println(buttonState);
delay(1);
if (buttonState == 1)
{
controller="1" ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone
}
else
{
digitalWrite(BUZZER,HIGH);
delay(500);
digitalWrite(BUZZER,LOW);
controller="0" ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone }
}
}
