// main.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <nn/NeuralNetwork.hpp>
#include <fterm/FTerm.hpp>
#include <fterm/lst/LSTerm.hpp>
#include <domain/Rectangle.hpp>
#include <utils/WriteFile.hpp>
#include <utils/GNUplot.hpp>
#include <time.h>
#include <ctime>

using namespace nn;
using namespace domain;
using namespace utils;
using namespace fterm;


int nTrain = 10;
int nCTrain  = 3;

typedef Matrix<float,Dynamic,Dynamic> MatrixXXf;

MatrixXXf X_train(2,nTrain),Y_train(2,nTrain);
MatrixXXf *X_ctrain,*Y_ctrain;

template <typename T>
void getTrainData(int);

double diffclock(clock_t clock1,clock_t clock2)
{
  double diffticks=clock1-clock2;
  double diffms=(diffticks*10)/CLOCKS_PER_SEC;
  return diffms;
}

template<typename T>
double unary(T x) {
  return x > .55 ? 1 : x < .54 ? 0 : x;
}

template <typename T>
void train(FTerm<T>* loss, int nMaxIter= 1000, T tol = 1e-2) {
  
  T error ;
  int i=0;
  clock_t begin = clock();

  cout << "-----Start training---------" << endl;
  
  do {
        
    getTrainData<float>(nCTrain);    
    loss[0].setTrainData(X_ctrain,Y_ctrain);
    
    loss[0].train();
    error = loss[0].cost();
    if(i%1000 == 0)
      cout << "Iteration " << i << "  Error: " << error  << endl;
    
    i++;
  }while(i < nMaxIter);
  
  cout << "-------Finish training---------" << endl;
  

  clock_t end = clock();
  //cout << "Sum: " << sum << " Time elapsed: " << double(diffclock(end,begin)) << " ms" << endl;
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  cout << "Train elapased time " <<  elapsed_secs << "sec." << endl;
}

template<typename T>
void test(NeuralNetwork<T>& net,  Matrix<float,Dynamic,Dynamic> &X_test, Matrix<float,Dynamic,Dynamic> &Y_test) {
  
  int n,m;
  
  net.eval(X_test,Y_test);
  n = Y_test.rows();
  m = Y_test.cols();
  
  for(int i=0; i < n; i++)
    for(int j=0; j < m; j++)
      Y_test(i,j) = unary<float>(Y_test(i,j));
}


int main() {

  int nMaxIter = 50000;
  float tol = 1e-3;
  int nEval = 50;
  float a   = 0;
  float b   = 1;
  float c   = 0;
  float d   = 1;
  
  //plotter 
  GNUplot plotter;  
  string pnamefile = "./data/prediction_data.txt";
  string lnamefile = "./data/learning_data.txt";
  string s;
  
  //Problem Domain
  Rectangle <float> rectangle(a,b,c,d,nEval);



  // MatrixXXf X_train(2,10),Y_train(2,10);
  MatrixXXf X_test,Y_test,Z_test;
  
  WriteFile<float> writter;
  
  X_train << 0.1,0.3,0.1,0.6,0.4,0.6,0.5,0.9,0.4,0.7,0.1,0.4,0.5,0.9,0.2,0.3,0.6,0.2,0.4,0.6;
  Y_train << 1.0,1.0,1.0,1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0,1.0,1.0,1.0,1.0;

  
  vector<int> architecture = {2, 2, 3, 2};
  NeuralNetwork<float> net(architecture,0.05, NeuralNetwork<float>::Activation::TANH);

  FTerm<float>* loss [1];  
  FTerm<float>* lsterm = new LSTerm<float>(&net,nCTrain);  
  //FTerm<float>* lsterm = new LSTerm<float>(&X_train,&Y_train,&net);  

  loss[0] = lsterm;
   
  train<float>(*loss,nMaxIter,tol);

  

  rectangle.uniformSampleFromInner(X_test);
  test<float>(net,X_test,Y_test);

  writter.write(X_train,Y_train,lnamefile);
  writter.write(X_test,Y_test,pnamefile);
  
  // net.save("./data/params.txt");  


  // // cout << endl << "Neurons:" << endl;
  // // for(int i = 0; i < net.mNeurons.size(); i++)
  // //   cout <
  // // *net.mNeurons[i] << endl;
  // // cout << endl << "Weights:" << endl;
  // // for (int i = 0; i < net.mWeights.size(); i++)
  // //   cout << *net.mWeights[i] << endl;
  


  s = "set title "+string("\"")+"Clasification Zones"+string("\"")+";"+ "set palette model RGB defined "+ string("(")+"0"+string(" ")+ string("\"")+"red"+string("\"")+string(",")+"1"+string(" ")+string("\"")+"blue"+string("\"")+string(")") + ";" + "plot "+ string("\'")+ pnamefile+string("\'")+" using 1:2:3 with points pt 2 palette  notitle,"+ string("\'")+ lnamefile+string("\'")+" using 1:2:3 with points pt 7 ps 1 palette title "+string("\"")+"train data"+string("\"");
  
  plotter(s.c_str());
  int pause = cin.get();

    

  return 0;
}


template <typename T>
void getTrainData(int nCTrain){
  
  int nTrain  = X_train.cols();
  int min     = 0;
  int max     = nTrain-1;

  int num;
  int j;
  bool find;
  vector<int> v(nCTrain);

  
  for(int i=0; i < nCTrain; i++){
    do{
      num   = rand() * (1.0 / RAND_MAX) * (max-min+1) + min;
      find = false;

      for(j=0; j < i; j++)
        if(num == v[j]){ 
          find = true;
          break;
        }      
    } while(find);
    
    v[i] = num;
    // v[i] = 3;
  }


  if(X_ctrain != 0 && Y_ctrain != 0 ){
    delete X_ctrain;
    delete Y_ctrain;
    
    X_ctrain = 0;
    Y_ctrain = 0;

  }
    
  X_ctrain = new Matrix<T,Dynamic,Dynamic> ((X_train)(Eigen::placeholders::all,v));
  Y_ctrain = new Matrix<T,Dynamic,Dynamic> ((Y_train)(Eigen::placeholders::all,v));

  // cout << "------" << endl;
  //cout << *X_ctrain << endl;
  // cout << *Y_ctrain << endl;
  // cout << "----" << endl;
  
}

