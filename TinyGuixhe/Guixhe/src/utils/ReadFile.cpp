#include <utils/ReadFile.hpp>

namespace utils{

  using namespace std;

  
  ReadFile::ReadFile(string filename){
    _filename = filename;
    
  }

  void ReadFile::readCSV(vector<RowVector*> & data)
  {
    data.clear();
    std::ifstream file(_filename);
    std::string line, word;
    
    // determine number of columns in file
    getline(file, line, '\n');
    std::stringstream ss(line);
    std::vector<Scalar> parsed_vec;
    
    while (getline(ss, word, ',')) {
      //cout << word << endl;
      parsed_vec.push_back(Scalar(std::stof(&word[0])));
    }
    
    unsigned int cols = parsed_vec.size();
    
    data.push_back(new RowVector(cols));
    for (unsigned int i = 0; i < cols; i++) {
      data.back()->coeffRef(1, i) = parsed_vec[i];
    }
    
    // read the file
    if (file.is_open()) {
      while (getline(file, line, '\n')) {
        std::stringstream ss(line);
        //cout << line << endl;
        data.push_back(new RowVector(1, cols));
        unsigned int i = 0;
        while (getline(ss, word, ',')) {
          data.back()->coeffRef(i) = Scalar(std::stof(&word[0]));
          
          i++;
        }
      }
    }
    
    // cout << data.size() << endl;
    
  }
  
  
  string ReadFile::readFileIntoString(const string& path) {
    auto ss = ostringstream{};
    ifstream input_file(path);
    if (!input_file.is_open()) {
      cerr << "Could not open the file - '"
           << path << "'" << endl;
      exit(EXIT_FAILURE);
    }
    ss << input_file.rdbuf();
    return ss.str();
  }
  
  
}
