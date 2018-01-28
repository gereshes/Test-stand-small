//This script allows the Arduino to read off the analog measurements from
//the load cell, convert it to digital counts, and write it to the computer. 
//This script is part of UB SEDS small test stand program
//
// Ari Rubinsztejn
// ari@gereshes.com
// www.gereshes.com


//Initializing variables

String toPrint;
int readout;
int readout1;
int readout2;
void setup() {
  Serial.begin(115200); //starts serial communication  at baud rate of 115200
}

void loop() {

  
   readout=analogRead(0);//Reads out the value of the sensor

   toPrint=round(micros()/100); //Records the current time

   toPrint+=',';
   toPrint+=readout;//Combines the current readout with the measurement.
   
   Serial.println(toPrint); //Prints the timestamped measurement to the serial line

}
