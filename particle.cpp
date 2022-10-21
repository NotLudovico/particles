#include "particle.hpp"

#include <cmath>
#include <iostream>

#include "particleType.hpp"
#include "resonanceType.hpp"

std::vector<ParticleType*> Particle::table_(1, nullptr);

Particle::Particle(char* name, double px, double py, double pz)
    : px_{px}, py_{py}, pz_{pz} {
  index_ = Particle::FindParticle(name);
}

int Particle::FindParticle(char* name) {
  for (int i = 0; i < Particle::table_.size(); i++) {
    if (table_[i]->GetName() == name) return i;
  }

  std::cout << "\n ** PARTICLE NOT FOUND ** \n";
  return -1;
}

int Particle::FindParticleTest(char* name) {
  return Particle::FindParticle(name);
}

void Particle::AddParticleType(char* name, double mass, int charge,
                               double width) {
  if (table_.size() >= 11) return;

  ParticleType* new_particle;
  if (width > 0)
    new_particle = new ResonanceType{name, mass, charge, width};
  else
    new_particle = new ParticleType{name, mass, charge};

  if (table_[0] == nullptr)
    table_[0] = new_particle;
  else
    table_.push_back(new_particle);
}

void Particle::SetIndex(int index) { index_ = index; };

void Particle::PrintTable() {
  std::cout << "TABLE:\n";
  for (size_t i = 0; i < table_.size(); i++) {
    table_[i]->Print();
    std::cout << '\n';
  }
}

void Particle::Print() const {
  std::cout << "INDEX: " << index_ << '\n';
  std::cout << "Px: " << px_ << '\n';
  std::cout << "Py: " << py_ << '\n';
  std::cout << "Pz: " << pz_ << '\n';
}

double Particle::GetPx() const { return px_; }
double Particle::GetPy() const { return py_; }
double Particle::GetPz() const { return pz_; }

void Particle::SetP(double px, double py, double pz) {
  px_ = px;
  py_ = py;
  pz_ = pz;
}

double Particle::GetMass() const { return table_[index_]->GetMass(); }
double Particle::GetPNorm() const {
  return GetPx() * GetPx() + GetPy() * GetPy() + GetPz() * GetPz();
}
double Particle::GetTotalEnergy() const {
  return std::sqrt(GetMass() * GetMass() + GetPNorm() * GetPNorm());
}
double Particle::InvMass(Particle& other) const {
  return std::sqrt(pow((GetTotalEnergy() + other.GetTotalEnergy()), 2) -
                   (pow((GetPx() - other.GetPx()), 2) +
                    pow((GetPy() - other.GetPy()), 2) +
                    pow((GetPz() - other.GetPz()), 2)));
}
