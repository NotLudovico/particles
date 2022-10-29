#ifndef RESONANCETYPE_HPP
#define RESONANCETYPE_HPP

#include <string>

#include "particleType.hpp"

class ResonanceType : public ParticleType {
 private:
  const double width_;

 public:
  ResonanceType(std::string name, double mass, int charge, double width)
      : ParticleType{name, mass, charge}, width_{width} {}
  double GetWidth() const override;
  void Print() const override;
};

#endif