#include <Nextion.h>

//mapping the values sent by the nextion to variables
NexButton upRed = NexButton(1, 4, "dec_red");
NexButton dnRed = NexButton(1, 3, "inc_red");

//action that will happen when the red increase button is pressed

void upRedCallback(void *ptr) {
  if (dacRed <= 4095) {
    dacRed = dacRed + 10;
    dac.write(dacRed, 0);
  } else {
    dac.write(dacRed, 0);
  }
}

//action that will happen when the red decrease button is pressed

void dnRedCallback(void *ptr) {
  if (dacRed >= 740) {
    dacRed = dacRed - 10;
    dac.write(dacRed, 0);
  } else {
    dac.write(dacRed, 0);
  }
}

//touch event listener
//it will act when a touch event occurs
NexTouch *nex_listen_list[] = {
  &upRed,
  &dnRed,
  NULL
};



void setup() {
 //initialising TTL interface and display communication
  Serial.begin(9600);
  Serial2.begin(9600);
  nexInit();
  upRed.attachPush(upRedCallback, &upRed);
  dnRed.attachPush(dnRedCallback, &dnRed);
}



void loop() {
  nexLoop(nex_listen_list);
  //reading voltage values and scaling it
  Red_Voltage = analogRead(A15) * (500.0 / 1023.0);
  value_to_red(int(Red_Voltage) / 10);
//sending voltage values to graph and textbox
  Serial2.print("red_voltage.val=");
  Serial2.print(int(Red_Voltage));
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  Serial2.print("red_item.val=");
  Serial2.print(int(Red_Voltage));
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
