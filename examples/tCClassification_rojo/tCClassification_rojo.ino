#include <iostream>
#include <time.h>
#include <ctime>
#include "Classification.h"
//#include "NeuralNetwork.h"

//NeuralNetwork net;
const char* pnamefile = "C:Users/alfredo.munguia.INFOTEC/Documents/Arduino/ANNC1/tCClassification/data/params.txt";
float x,y, pred;
//const char* openfile;
bool openfile=true;

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("paso 1 ");

   //net.setParameters(vector<RowVectorXT*> b, vector<MatrixXXT*> W){
  // openfile = net.load(pnamefile); 
     // Lee paramatros desde archivo de text /**************/

  
}

void loop() {
    x=0.1; // zona Roja
   y=0.9;
   
  // x=0.3; //zona Amarilla
  // y=0.2;
if (openfile == true){
      Serial.print("clasificar (");
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      Serial.println(") en la iA");      

      clasification(x,y);   //uso de libreria NeuralNetwork.h
      Serial.print("Prediction: (");
      Serial.print(x);
      Serial.print(",");
      Serial.print(y);
      if(x==1 && y== 0)      Serial.println(")clase Zona Roja");
      else if (x==0 && y== 1)      Serial.println(")clase Zona Amarilla");
}else Serial.println("No se puede abrir el archivo txt" );
 // Serial.println(openfile);
  delay(3000);
}
