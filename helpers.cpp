#include "helpers.hpp"

#include <cmath>
#include <string>

#include "TRandom.h"

InitialConditions GenerateParticleImpulse() {
  InitialConditions cond;

  cond.phi = 2 * M_PI * gRandom->Rndm();
  cond.theta = M_PI * gRandom->Rndm();
  cond.p_module = gRandom->Exp(1);
  cond.px = cond.p_module * cos(cond.theta) * sin(cond.phi);
  cond.py = cond.p_module * sin(cond.theta) * sin(cond.phi);
  cond.pz = cond.p_module * cos(cond.phi);

  return cond;
}

Particle GenerateParticle(double px, double py, double pz) {
  double x = gRandom->Rndm();

  std::string name;
  int index = 0;

  if (x <= 0.4) {
    name = "Pion+";
  } else if (x <= 0.8) {
    name = "Pion-";
    index = 1;
  } else if (x <= 0.85) {
    name = "Kaon+";
    index = 2;
  } else if (x <= 0.9) {
    name = "Kaon-";
    index = 3;
  } else if (x <= 0.945) {
    name = "Proton+";
    index = 4;
  } else if (x <= 0.99) {
    name = "Proton-";
    index = 5;
  } else {
    name = "K*";
  }

  return Particle(name, px, py, pz);
}