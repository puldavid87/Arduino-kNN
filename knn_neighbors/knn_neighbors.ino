//#include "knn.h"
float test[5]={6.2,2.9,4.3,1.3,2}; //6,2  2,9 4,3 1,3
unsigned long start;
unsigned long elapsed;
const int cols =5;
const int raws = 120;
uint8_t respuesta;
void setup() {
 Serial.begin(9600);
}

void loop() {
  start = micros();
//  respuesta=knn(3,3,5,120,&test[0]);
  Serial.println(respuesta);
   elapsed = micros() - start;
    Serial.print(elapsed / 10000.0);
    Serial.print("us per operation, ");
    Serial.print((10000.0 * 1000000.0) / elapsed);
    Serial.println(" per second");
}


 
