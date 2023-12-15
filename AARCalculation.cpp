#include <iostream>
#include <vector>
#include <algorithm>

/* Need Rmt and Rit from other group
Rit = [,,]   // vector of vectors
Rmt = [, ,]   // vector
*/

// type definition
typedef vector<double> Vector;
typedef vector<Vector> Matrix;


Matrix ARit(Matrix & Rit,Vector & Rmt) {
  Matrix V;
  int M = Rit[0].size();
  int t = Rit.size();
  for (int col = 0; col<M; col++) {
    double A_Rit;
    Vector V1;
    for (int row = 0; row < t; row++) {
      A_Rit = Rit[row][col] - Rmt[row];
      V1.push_back(ARit);
      }
    V.push_back(V1);
  }
  return V;
}

Vector AARt (){
  Vector V;
  int M = ARit[0].size();
  int t = ARit.size();
  for (int row = 0; row<t; row++) {
    double AA_Rt;
    AA_Rt = std::accumulate(V.begin(), V.end(), 0.0/M);
    V.push_back(AA_Rt);
  }
  return V;
}