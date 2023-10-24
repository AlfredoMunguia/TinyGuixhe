//#include <iostream>
#include "TinyGuixhe.h"
//#include "NeuralNetwork.h"
//#include <time.h>
//#include <ctime>


typedef Matrix<float,Dynamic,Dynamic> MatrixXXf;
typedef Matrix<float,1,Dynamic> RowVectorXT;
typedef Matrix<float,Dynamic,Dynamic> MatrixXXT;

void clasification(Matrix<float,1,Dynamic> &X_test, Matrix<float,1,Dynamic> &Y_test);
double unary(float x);

RowVectorXT Y_test, X_test;
//nn::NeuralNetwork<float> net;
NeuralNetwork net;
std::vector<int> architecture = { 2, 2, 3, 2};
std::vector<RowVectorXT*> b;
std::vector<MatrixXXT*> W;


  
void clasification(float& x, float& y) {
net.init(architecture,0.05); //Inicializa NeuralNetwork net(architecture,0.05);

  b = net._b;
  W = net._W;
//bias:3
   (*b[0])[1] = 0.365587;
   (*b[0])[0] = 0.179793;
  
  (*b[1])[0] = 0.426743;
  (*b[1])[1] = -1.34388;
  (*b[1])[2] = 1.62985;

  (*b[2])[0] = 1.39232;
  (*b[2])[1] = -0.991048;

//Weights:3
  (*W[0])(0,0) = -5.84514;
  (*W[0])(0,1) =  1.01519;
  (*W[0])(1,0) = 3.32361;
  (*W[0])(1,1) = -0.173842;   

  (*W[1])(0,0) = -2.84239;
  (*W[1])(0,1) = 3.98398;
  (*W[1])(0,2) = -5.78766;
  (*W[1])(1,0) = 0.85121;
  (*W[1])(1,1) = -0.40241;
  (*W[1])(1,2) = 1.49339;
 
  (*W[2])(0,0) = -2.52311;
  (*W[2])(0,1) = 1.3152;
  (*W[2])(1,0) = 3.51839;
  (*W[2])(1,1) = -3.80507;
  (*W[2])(2,0) = -4.76408;
  (*W[2])(2,1) = 5.31671;
   //net.setParameters(architecture, 0.05,net.Activation::TANH, &b, &W);
    net.setParameters(architecture, 0.05, b, W);

   X_test.resize(2);
 
  X_test(0) = x;
  X_test(1) = y; 
   int n,m;
    
    net.eval(X_test,Y_test);
    n = Y_test.rows();
    m = Y_test.cols();
    
    for(int i=0; i < n; i++)
      for(int j=0; j < m; j++)
        Y_test(i,j) = unary( Y_test(i,j));
  

  x=Y_test(0);
  y=Y_test(1); 

}


double unary(float x) {
  return x > .55 ? 1 : x < .54 ? 0 : x;
}
