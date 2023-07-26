#include <Arduino.h>
#include <IRremote.h>

#define IR_RECEIVE_PIN 26
#define IR_SEND_PIN 25

#define IR_SAMSUNG_ADDRESS 0x707
#define IR_SAMSUNG_COMMAND_VOL_UP 0x7
#define IR_SAMSUNG_COMMAND_VOL_DOWN 0xB
#define IR_SAMSUNG_COMMAND_MUTE 0xF
#define IR_SAMSUNG_COMMAND_RED 0x6C
#define IR_SAMSUNG_COMMAND_GREEN 0x14
#define IR_SAMSUNG_COMMAND_YELLOW 0x15
#define IR_SAMSUNG_COMMAND_BLUE 0x16

#define IR_DENON_ADDRESS 0x6
#define IR_DENON_COMMAND_POWER 0xA
#define IR_DENON_COMMAND_VOL_UP 0xB2
#define IR_DENON_COMMAND_VOL_DOWN 0x32
#define IR_DENON_COMMAND_AUX 0xDA
#define IR_DENON_COMMAND_TUNER 0x9A
#define IR_DENON_COMMAND_CD 0x5A
#define IR_DENON_COMMAND_TAPE 0x1A


void setup() {
  Serial.begin(115200);

  IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
    printf("DEVICE:");

    if (IrReceiver.decodedIRData.address == IR_SAMSUNG_ADDRESS) {
      printf("SAMSUNG:");

      switch (IrReceiver.decodedIRData.command) {
        case IR_SAMSUNG_COMMAND_VOL_UP:
          IrSender.sendDenon(IR_DENON_ADDRESS, IR_DENON_COMMAND_VOL_UP, 0);
          printf("VOL_UP");
          break;

        case IR_SAMSUNG_COMMAND_VOL_DOWN:
          IrSender.sendDenon(IR_DENON_ADDRESS, IR_DENON_COMMAND_VOL_DOWN, 0);
          printf("VOL_DOWN");
          break;

        case IR_SAMSUNG_COMMAND_BLUE:
          IrSender.sendDenon(IR_DENON_ADDRESS, IR_DENON_COMMAND_POWER, 0);
          printf("POWER");
          delay(500UL);
          break;

        case IR_SAMSUNG_COMMAND_MUTE: 
          IrSender.sendDenon(IR_DENON_ADDRESS, IR_DENON_COMMAND_POWER, 0);
          printf("MUTE");
          delay(500UL);
          break;

        case IR_SAMSUNG_COMMAND_RED:
          IrSender.sendDenon(IR_DENON_ADDRESS, IR_DENON_COMMAND_AUX, 0);
          printf("RED");
          delay(500UL);
          break;

        case IR_SAMSUNG_COMMAND_GREEN:
          IrSender.sendDenon(IR_DENON_ADDRESS, IR_DENON_COMMAND_TUNER, 0);
          printf("GREEN");
          delay(500UL);
          break;

        case IR_SAMSUNG_COMMAND_YELLOW:
          IrSender.sendDenon(IR_DENON_ADDRESS, IR_DENON_COMMAND_CD, 0);
          printf("YELLOW");
          break;

        default:
          printf("NOT_FOUND:%02X", IrReceiver.decodedIRData.command);
          break;
      }
    } else {
      printf("NOT_FOUND:%04X", IrReceiver.decodedIRData.address);
    }

    printf("\n");

    IrReceiver.resume();
  }

  delay(10UL);
}
