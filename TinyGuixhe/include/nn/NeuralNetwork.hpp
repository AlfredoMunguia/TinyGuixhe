#include <ArduinoEigen.h>
#include <ArduinoEigenDense.h>
#include <ArduinoEigenSparse.h>
//#include <iostream> 
//#include <string> 
#include <fstream> 


using namespace Eigen;


#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H


#define LEARNING_RATE   0.01


class NeuralNetwork {

    typedef Matrix<float, 1, Dynamic> RowVectorXT;
    typedef Matrix<float, Dynamic, Dynamic> MatrixXXT;

public:


    enum Activation { TANH, SIGMOID } mActivation;
    // network learning rate
    float mLearningRate;
    // network layers architecture (input-hidden-output) 
    std::vector<int> mArchitecture;

    // network layers vectors
    std::vector<RowVectorXT*> mNeurons;
    std::vector<RowVectorXT*> mErrors;
    std::vector<MatrixXXT*> mWeights;

    // network layers vectors
    std::vector<RowVectorXT*> _a;
    std::vector<RowVectorXT*> _z;

    RowVectorXT _error;

    // neurons' output errors    
    // std::vector<RowVectorXT*> _delta;
    std::vector<RowVectorXT*> _b;
    std::vector<RowVectorXT*> mbias;

    // connections' weights
    std::vector<MatrixXXT*> _W;
    std::vector<MatrixXXT*> _D;
    std::vector<MatrixXXT*> __B;

    MatrixXXT _Lambda;

    RowVectorXT _input;
    RowVectorXT _output;
    RowVectorXT _errors;

    int         _nTrain;
    int         _nCTrain;
    int         _nInput;
    int         _nOutput;

    // confusion matrix
    //MatrixXXT* mConfusion;   ///AMM

    // constructors
    NeuralNetwork() {};

    


    void init(std::vector<int> architecture, float learningRate = LEARNING_RATE) {
        mArchitecture = architecture;
        mLearningRate = learningRate;
        //mActivation   = activation;


        mNeurons.clear();
        mErrors.clear();
        mWeights.clear();
        mbias.clear();

        _a.clear();
        // _delta.clear();
        _b.clear();
        _W.clear();
        _D.clear();

        int nL = architecture[architecture.size() - 1];
        _nInput = architecture[0];
        _nOutput = nL;

        for (unsigned int i = 0; i < architecture.size(); i++) {
            _a.push_back(new RowVectorXT(architecture[i]));
            _z.push_back(new RowVectorXT(architecture[i]));

            if (i < architecture.size() - 1) {

                _b.push_back(new RowVectorXT(architecture[i + 1]));
                _W.push_back(new MatrixXXT(architecture[i], architecture[i + 1]));

                _D.push_back(new MatrixXXT(architecture[i + 1], architecture[i + 1]));
                __B.push_back(new MatrixXXT(architecture[i + 1], nL));

                // initialize weights and bias
                _W.back()->setRandom();
                _b.back()->setRandom();
                mWeights = _W;
                mbias = _b;
            }
        }
    }

 void setParameters(std::vector<int> architecture, float learningRate,std::vector<RowVectorXT*>& b, std::vector<MatrixXXT*>& W){
        init(architecture, learningRate);
        _b = b;
        _W = W;
     }

    void forward(RowVectorXT& input) {

        // set first layer input
        *_a.front() = input;

        // propagate forward (vector multiplication)
        for (int i = 1; i < mArchitecture.size(); i++) {
            // *_a[i] = *_a[i-1] * *_W[i-1]  + *_b[i-1];
            *_z[i] = *_a[i - 1] * *_W[i - 1] + *_b[i - 1];

            //apply activation function
            for (int col = 0; col < mArchitecture[i]; col++) {
                _a[i]->coeffRef(col) = activation(_z[i]->coeffRef(col));
                _D[i - 1]->coeffRef(col, col) = activationDerivative(_z[i]->coeffRef(col));
            }
        }
    }

    float activation(float x) {
        if (mActivation == TANH)
            return tanh(x);
        if (mActivation == SIGMOID)
            return 1.0 / (1.0 + exp(-x));
        return 0;
    }


    float activationDerivative(float x) {
        if (mActivation == TANH)
            return 1 - tanh(x) * tanh(x);
        if (mActivation == SIGMOID)
            return (1.0 / (1.0 + exp(-x))) * (1.0 - (1.0 / (1.0 + exp(-x))));
        // x * (1.0 - x);
        return 0;
    }

    void eval(RowVectorXT& input, RowVectorXT& output) {
        forward(input);
        output = *_a.back();
    }

    void eval(MatrixXXT& input, MatrixXXT& output) {

        RowVectorXT inputByLayer(mArchitecture[0]);
        RowVectorXT outputByLayer(mArchitecture[mArchitecture.size() - 1]);

        output.resize(mArchitecture[mArchitecture.size() - 1], input.cols());

        for (int j = 0; j < input.cols(); ++j) {

            for (int i = 0; i < input.rows(); ++i) {
                inputByLayer.coeffRef(i) = input(i, j);
            }

            forward(inputByLayer);
            outputByLayer = *_a.back();

            for (int i = 0; i < output.rows(); ++i) {
                output(i, j) = outputByLayer.coeffRef(i);
            }
        }
    }

  bool load(const char* filename) {
        mArchitecture.clear();
        std::ifstream file;
      file.open(filename);
        if (!file.is_open())
            return false;
         std::string line, name, value;
          if (!getline(file, line, '\n'))
                return false;
           std::stringstream lr(line);

        // read learning rate
        getline(lr, name, ':');
        if (name != "learningRate")
            return false;
        if (!getline(lr, value, '\n'))
            return false;
       mLearningRate = atof(value.c_str());

        // read topoplogy
        getline(file, line, '\n');
        std::stringstream ss(line);
        getline(ss, name, ':');
        if (name != "architecture")
            return false;
        while (getline(ss, value, ','))
            mArchitecture.push_back(atoi(value.c_str()));

        // read activation
        getline(file, line, '\n');
        std::stringstream sss(line);
        getline(sss, name, ':');
        if (name != "activation")
            return false;
        if (!getline(sss, value, '\n'))
            return false;
        mActivation = (Activation)atoi(value.c_str());

        // initialize using read architecture
        init(mArchitecture, mLearningRate);

        // read weights

        getline(file, line, '\n');
        std::stringstream we(line);
        getline(we, name, ':');
        if (!(name.compare("weights") == 0))
            return false;

      std::string matrix;
        for (int i = 0; i < mArchitecture.size()-1; i++)
            if (getline(file, matrix, ',')) {
                std::stringstream ss(matrix);
                int row = 0;
                while (getline(ss, value, '\n'))
                    if (!value.empty()) {
                        std::stringstream wordd(value);
                        int col = 0;
                        while (getline(wordd, value, ' '))
                            if (!value.empty())
                                //mWeights[i]->coeffRef(row, col++) = atof(value.c_str());
                                _W[i]->coeffRef(row, col++) = atof(value.c_str());
                        row++;
                    }
            }
        
        
        // read bias 
        getline(file, line, '\n');
        getline(file, line, ' ');
        std::stringstream bi(line);
        getline(bi, name, ':');
        if (name != "bias")
            return false;
        if (!(name.compare("bias") == 0))
            return false;

        std::string vector;
        for (int i = 0; i < mArchitecture.size(); i++)
            if (getline(file, vector, ',')) {
                std::stringstream ss(vector);
                int row = 0;
                while (getline(ss, value, '\n'))
                    // read bias
                    if ((!value.empty())) {
                        std::stringstream wordd(value);
                        int col = 0;
                        while (getline(wordd, value, ' '))
                            if (!value.empty())
                                //mbias[i]->coeffRef(row, col++) = atof(value.c_str());
                                _b[i]->coeffRef(row, col++) = atof(value.c_str());
                        row++;
                    }
            }         

        file.close();

       /* cout << endl << "Sesgos:" << _b.size() << endl;
        for (int i = 0; i < _b.size(); i++) {
            cout << *_b[i] << endl;
        }


        cout << endl << "Weights:" << _W.size() << endl;
        for (int i = 0; i < _W.size(); i++) {
            cout << *_W[i] << endl;
        }*/
        return true;
    }

};

#endif

