#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <string>
#include <vector>

#include "particleType.hpp"

class Particle {
  double px_;
  double py_;
  double pz_;
  int index_;
  static std::vector<ParticleType*> table_;
  static int FindParticle(std::string name);
  void Boost(double bx, double by, double bz);

 public:
  Particle(std::string name, double px = 0, double py = 0, double pz = 0);
  static void AddParticleType(std::string name, double mass, int charge,
                              double width = 0);
  static int FindParticleTest(std::string name);
  static void PrintTable();
  void SetIndex(int index);
  void SetIndex(std::string name);
  int GetIndex();
  std::string GetName() const;
  int GetCharge() const;
  void Print() const;
  double GetPx() const;
  double GetPy() const;
  double GetPz() const;
  void SetP(double px = 0, double py = 0, double pz = 0);
  double GetPNorm() const;
  double GetMass() const;
  double GetEnergy() const;
  double InvMass(Particle const& other) const;
  int Decay2body(Particle& dau1, Particle& dau2) const;
};

#endif