#include <iostream>
#include <armadillo>

using namespace arma;

colvec lm(mat X, colvec y) {
  // Compute the least squares solution to X * beta = y
  colvec beta = arma::solve(X, y);
  return beta;
}


int main() {

  mat X = randu(3, 3);
  colvec y = randu(3);
  colvec beta = lm(X, y);
  std::cout << beta << std::endl;
  
}