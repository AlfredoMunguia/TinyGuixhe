#include <ArduinoEigen.h>
#include <ArduinoEigenDense.h>
#include <ArduinoEigenSparse.h>
#include "TinyGuixhe/include/nn/NeuralNetwork.hpp"


	namespace nn {

		typedef Eigen::Matrix<float, Dynamic, 1> RowVectorXT;

		NeuralNetwork<float> NeuralNetworkf;
		NeuralNetwork<int> NeuralNetworki;
	}