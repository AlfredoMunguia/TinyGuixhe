#include <Eigen/Eigen>


template<typename T>
typedef Eigen::Matrix<T,Dynamic,1> RowVectorXT;

typedef  NeuralNetwork<float> NeuralNetworkf;
typedef  NeuralNetwork<int> NeuralNetworki;
