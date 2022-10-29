#ifndef HELPERS_HPP
#define HELPERS_HPP

#include "particle.hpp"

struct InitialConditions {
  double phi;
  double theta;
  double p_module;
  double px;
  double py;
  double pz;
};

InitialConditions GenerateParticleImpulse();
Particle GenerateParticle(double px = 0, double py = 0, double pz = 0);

#endif