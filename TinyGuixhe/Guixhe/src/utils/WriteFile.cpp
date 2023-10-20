//#include <utils/WriteFile.hpp>


//namespace utils{
template <typename T>
WriteFile<T>::WriteFile(string filename){
  _filename = filename;
}


// void WriteFile::genData()
//   {
//     std::ofstream file1(_filename + "-in");
//     std::ofstream file2(_filename + "-out");

//     for (uint r = 0; r < 1000; r++) {
//       float x = rand() / float(RAND_MAX);
//       float y = rand() / float(RAND_MAX);
//       file1 << x << ", " << y << std::endl;
//       file2 << 2 * x + 10 + y << std::endl;
//     }
//     file1.close();
//     file2.close();
//   }


// void WriteFile::eigentoData(MatrixXf& src, char* pathAndName)
// {
//   ofstream fichier(pathAndName, ios::out | ios::trunc);  
//   if(fichier)  // si l'ouverture a réussi
//     {   
//       // instructions
//       fichier << "Here is the matrix src:\n" << src << "\n";
//       fichier.close();  // on referme le fichier
//     }
//   else  // sinon
//     {
//       cerr << "Erreur à l'ouverture !" << endl;
//         }
// }

template <typename T>
void WriteFile<T>::write(Matrix<T,Dynamic,Dynamic>& X_test, Matrix<T,Dynamic,Dynamic>& Y_test){
  
  std::ofstream file(_filename);
  Matrix<T,Dynamic,Dynamic> x_test = X_test.transpose();
  Matrix<T,Dynamic,Dynamic> y_test = Y_test.transpose();
  Matrix<T,Dynamic,Dynamic> mToSave(x_test.rows(),x_test.cols()+y_test.cols());

  mToSave << x_test,y_test;
  file << mToSave << endl;
  file.close();
}

template <typename T>
void WriteFile<T>::write(Matrix<T,Dynamic,Dynamic>& X_test, Matrix<T,Dynamic,Dynamic>& Y_test, string filename){
  
  std::ofstream file(filename);
  Matrix<T,Dynamic,Dynamic> x_test = X_test.transpose();
  Matrix<T,Dynamic,Dynamic> y_test = Y_test.transpose();
  Matrix<T,Dynamic,Dynamic> mToSave(x_test.rows(),x_test.cols()+y_test.cols());

  mToSave << x_test,y_test;
  file << mToSave << endl;
  file.close();
}





  
//}
