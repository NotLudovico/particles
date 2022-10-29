#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

#include <string>

class ParticleType {
 private:
  const std::string name_;
  const double mass_;
  const int charge_;

 public:
  ParticleType(std::string name, double mass, int charge)
      : name_{name}, mass_{mass}, charge_{charge} {}

  const std::string GetName() const;
  double GetMass() const;
  int GetCharge() const;
  virtual double GetWidth() const;
  virtual void Print() const;
};

#endif