#ifndef PARTICLETYPE_HPP
#define PARTICLETYPE_HPP

class ParticleType {
 private:
  const char* name_;
  const double mass_;
  const int charge_;

 public:
  ParticleType(char* name, double mass, int charge)
      : name_{name}, mass_{mass}, charge_{charge} {}

  const char* GetName() const;
  double GetMass() const;
  int GetCharge() const;
  virtual double GetWidth() const;
  virtual void Print() const;
};

#endif