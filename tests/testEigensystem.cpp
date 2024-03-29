#include "Matrix.h"
#include "Spline.h"
#include "Reparametrization.h"
#include "testMatrices.h"

#include <fmt/format.h>
#include <fstream>

void testEigensystem(const Matrix& matA) {
  std::cout << "Matrix A:\n" << matA;
  realSymmetricEigenSolver solver(matA);
  tuple<Matrix, Matrix> eigen = solver.solve();
  const Matrix& Lambda = std::get<0>(eigen);
  const Matrix& Q = std::get<1>(eigen);
  std::cout << "Eigenvalues:\n" << Lambda;
  std::cout << "Eigenvectors:\n" << Q;
  const Matrix tmp = Q * Lambda * Q.transpose();
  std::cout << "Q*Λ*Q'\n" << tmp;
  std::cout << "RMSE = " << Matrix::rootMeanSquareError(tmp, matA) << std::endl;
}

void testEigensystem2() {
  const Matrix tmp1 = Matrix::rand(10);
  Matrix matA = tmp1 * tmp1.transpose();
  for (size_t i = 0; i < 10; ++i) {
    matA(i, i) = 0.0;
  }
  std::cout << "Matrix A:\n" << matA;
  realSymmetricEigenSolver solver(matA);
  tuple<Matrix, Matrix> eigen = solver.solve();
  const Matrix& Lambda = std::get<0>(eigen);
  const Matrix& Q = std::get<1>(eigen);
  std::cout << "Eigenvalues:\n" << Lambda;
  std::cout << "Eigenvectors:\n" << Q;
  const Matrix tmp = Q * Lambda * Q.transpose();
  std::cout << "Q*Λ*Q'\n" << tmp;
  std::cout << "RMSE = " << Matrix::rootMeanSquareError(tmp, matA) << std::endl;
}

int main() {
  testEigensystem(TEST::matA);
  testEigensystem2();
  return 0;
}
