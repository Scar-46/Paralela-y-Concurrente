// Copyright 2023 Fernando Arce Castillo <fernando.arcecastillo@ucr.ac.cr>

#include <cassert>
#include <cstdlib>
#include "GoldbachSolver.hpp"

void * GoldbachSolver::Goldbachmain(Celd & celd) {
  if (celd.getNum() < 0) {
    this->goldbach.goldbach_serie(celd.getNum()*-1, 0, celd.getGQueue());
  } else {
    this->goldbach.goldbach_serie(celd.getNum(), 1, celd.getGQueue());
  }
  return NULL;
}
