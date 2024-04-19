#include "MCP_DAC.h"
#include <Nextion.h>


MCP4922 dac;
MCP4922 dac2;
int dacRed = 4095;
int dacGreen = 4095;
int dacBlue = 4095;
int max = 4095;
int min = 730;


NexButton upRed = NexButton(1, 4, "dec_red");
NexButton dnRed = NexButton(1, 3, "inc_red");
NexButton upGreen = NexButton(2, 4, "dec_green");
NexButton dnGreen = NexButton(2, 3, "inc_green");
NexButton upBlue = NexButton(3, 4, "dec_blue");
NexButton dnBlue = NexButton(3, 3, "inc_blue");

void upRedCallback(void *ptr) {
  if (dacRed <= 4095) {
    dacRed = dacRed + 10;
    dac.write(dacRed, 0);
  } else {
    dac.write(dacRed, 0);
  }
}

void dnRedCallback(void *ptr) {
  if (dacRed >= 740) {
    dacRed = dacRed - 10;
    dac.write(dacRed, 0);
  } else {
    dac.write(dacRed, 0);
  }
}

void upGreenCallback(void *ptr) {
  if (dacGreen <= 4095) {
    dacGreen = dacGreen + 10;
    dac.write(dacGreen, 1);
  } else {
    dac.write(dacGreen, 1);
  }
}

void dnGreenCallback(void *ptr) {
  if (dacGreen >= 740) {
    dacGreen = dacGreen - 10;
    dac.write(dacGreen, 1);
  } else {
    dac.write(dacGreen, 1);
  }
}

void upBlueCallback(void *ptr) {
  if (dacBlue <= 4095) {
    dacBlue = dacBlue + 10;
    dac2.write(dacBlue, 0);
    Serial.println(dacBlue);
  } else {
    dac2.write(dacBlue, 0);
  }
}

void dnBlueCallback(void *ptr) {
  if (dacBlue >= 740) {
    dacBlue = dacBlue - 10;
    dac2.write(dacBlue, 0);
    Serial.println(dacBlue);


  } else {
    dac2.write(dacBlue, 0);
  }
}


NexTouch *nex_listen_list[] = {
  &upRed,
  &upGreen,
  &upBlue,
  &dnRed,
  &dnGreen,
  &dnBlue,
  NULL
};

float Red_Voltage = 0;
float Green_Voltage = 0;
float Blue_Voltage = 0;


void setup() {
  pinMode(A15, INPUT);
  pinMode(A14, INPUT);
  pinMode(A13, INPUT);
  SPI.begin();
  dac.begin(45);
  dac2.begin(43);
  Serial.begin(9600);
  Serial2.begin(9600);
  nexInit();
  upRed.attachPush(upRedCallback, &upRed);
  dac.write(4095, 0);
  dac.write(4095, 1);
  dac2.write(4095, 0);


  dnRed.attachPush(dnRedCallback, &dnRed);
  upGreen.attachPush(upGreenCallback, &upGreen);
  dnGreen.attachPush(dnGreenCallback, &dnGreen);
  upBlue.attachPush(upBlueCallback, &upBlue);
  dnBlue.attachPush(dnBlueCallback, &dnBlue);

  Serial2.print("cle 5,255");  //Send instruction to clear the waveform
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}



void loop() {
  nexLoop(nex_listen_list);

  Red_Voltage = analogRead(A15) * (500.0 / 1023.0);
  Green_Voltage = analogRead(A14) * (500.0 / 1023.0);
  Blue_Voltage = analogRead(A13) * (500.0 / 1023.0);
  value_to_red(int(Red_Voltage) / 10);
  value_to_green(int(Green_Voltage) / 10);
  value_to_blue(int(Blue_Voltage) / 10);


  Serial2.print("red_voltage.val=");
  Serial2.print(int(Red_Voltage));
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  Serial2.print("green_voltage.val=");
  Serial2.print(int(Green_Voltage));
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  Serial2.print("blue_voltage.val=");
  Serial2.print(int(Blue_Voltage));
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  Serial2.print("red_item.val=");
  Serial2.print(int(Red_Voltage));
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  Serial2.print("green_item.val=");
  Serial2.print(int(Green_Voltage));
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  Serial2.print("blue_item.val=");
  Serial2.print(int(Blue_Voltage));
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}
void value_to_red(int val_red) {
  String Tosend = "add ";
  Tosend += 1;
  Tosend += ",";
  Tosend += 0;
  Tosend += ",";
  Tosend += val_red;
  Serial2.print(Tosend);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}

void value_to_green(int val_green) {
  String Tosend = "add ";
  Tosend += 5;
  Tosend += ",";
  Tosend += 0;
  Tosend += ",";
  Tosend += val_green;
  Serial2.print(Tosend);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}

void value_to_blue(int val_blue) {
  String Tosend = "add ";
  Tosend += 6;
  Tosend += ",";
  Tosend += 0;
  Tosend += ",";
  Tosend += val_blue;
  Serial2.print(Tosend);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}

void varSend(String name, int val) {
  Serial2.print(name = ".val=");
  Serial2.print(val);
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}