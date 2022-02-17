#include "knn.h" 
float test_in[5]={6.2,2.9,4.3,1.3,2};
int y_pred;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  split_set(0.3);
  accurancy_knn(5);
  y_pred=classifier(3,&test_in[0]);
  Serial.println(y_pred);
  delay(1000);
}
