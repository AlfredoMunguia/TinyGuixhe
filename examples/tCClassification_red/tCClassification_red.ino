#include <iostream>
#include <time.h>
#include <ctime>
#include "Classification.h" // library Tinyguixhe
#include "NeuralNetwork.h"  // library Tinyguixhe

//NeuralNetwork net;  //uses Neuralnetwork.h as net
const char* pnamefile = "C:Users/alfredo.munguia.INFOTEC/Documents/Arduino/ANNC1/tCClassification/data/params.txt";  //define path tranin red
float x,y, pred;
//const char* openfile;
bool openfile=true;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("paso 1 ");
   //net.setParameters(vector<RowVectorXT*> b, vector<MatrixXXT*> W){
  // openfile = net.load(pnamefile);      // Read param to the text file
}

void loop() {
    x=0.1; // red zone
   y=0.9;
   
  // x=0.3; //yellow zone
  // y=0.2;
if (openfile == true){
      Serial.print("clasificar (");
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.println(") en la iA");      

      clasification(x,y);   //Classification.h uses Neuralnetwork.h
      Serial.print("Prediction: (");
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      if(x==1 && y== 0)      Serial.println(")class Red Zone");
      else if (x==0 && y== 1)      Serial.println(")class yellow Zone");
}else Serial.println("File txt cant't open" );
 // Serial.println(openfile);
  delay(3000);
}
