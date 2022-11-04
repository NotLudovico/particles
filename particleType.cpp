#include "particleType.hpp"

#include <iostream>
#include <string>

ParticleType::ParticleType(std::string name, double mass, int charge)
    : name_(name), mass_(mass), charge_(charge) {}
const std::string ParticleType::GetName() const { return name_; }
double ParticleType::GetMass() const { return mass_; }
int ParticleType::GetCharge() const { return charge_; }
void ParticleType::Print() const {
  std::cout << "NAME: " << name_ << '\n';
  std::cout << "MASS: " << mass_ << '\n';
  std::cout << "CHARGE: " << charge_ << '\n';
}

double ParticleType::GetWidth() const { return 0; }