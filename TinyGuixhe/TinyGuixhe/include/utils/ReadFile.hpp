
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Eigen>

namespace utils{

  using namespace std;

  typedef Eigen::MatrixXf Matrix;
  typedef Eigen::RowVectorXd RowVector;
  //typedef Eigen::VectorXd ColVector;
  typedef float Scalar;
  
  class ReadFile{    

  private:
    string _filename;
    // vector<RowVector*> _data;
    string readFileIntoString(const string& path);
    
  public:
    ReadFile(string filename);    
    void readCSV(vector<RowVector*> &);    

  };
  
}
