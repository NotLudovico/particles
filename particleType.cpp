#include "particleType.hpp"

#include <iostream>
const char* ParticleType::GetName() const { return name_; }
const double ParticleType::GetMass() const { return mass_; }
const int ParticleType::GetCharge() const { return charge_; }
void ParticleType::Print() const {
  std::cout << "NAME: " << name_ << '\n';
  std::cout << "MASS: " << mass_ << '\n';
  std::cout << "CHARGE: " << charge_ << '\n';
}