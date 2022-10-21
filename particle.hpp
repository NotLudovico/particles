#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>

#include "particleType.hpp"

class Particle {
  double px_;
  double py_;
  double pz_;
  int index_;
  static std::vector<ParticleType*> table_;
  static int FindParticle(char* name);

 public:
  Particle(char* name, double px = 0, double py = 0, double pz = 0);
  static void AddParticleType(char* name, double mass, int charge,
                              double width = 0);
  static int FindParticleTest(char* name);
  static void PrintTable();
  void SetIndex(int index);
  void Print() const;
  double GetPx() const;
  double GetPy() const;
  double GetPz() const;
  void SetP(double px = 0, double py = 0, double pz = 0);
  double GetPNorm() const;
  double GetMass() const;
  double GetTotalEnergy() const;
  double InvMass(Particle& other) const;
};

#endif