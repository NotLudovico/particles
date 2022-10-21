#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include "particleType.hpp"

class ResonanceType : public ParticleType {
 private:
  const double width_;

 public:
  ResonanceType(char* name, double mass, int charge, double width)
      : ParticleType{name, mass, charge}, width_{width} {}
  const double GetWidth() const;
  void Print() const;
};

#endif