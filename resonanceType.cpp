#include "resonanceType.hpp"

#include <iostream>

double ResonanceType::GetWidth() const { return width_; }
void ResonanceType::Print() const {
  ParticleType::Print();
  std::cout << "WIDTH: " << width_ << '\n';
}