#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <vector>

#include "TH1F.h"
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
void AnalizeData(std::vector<Particle> const& particles, TH1F* totalInvMass,
                 TH1F* invMassOppositeCharge, TH1F* invMassSameCharge,
                 TH1F* invMassKPOpposite, TH1F* invMassKPSame);
#endif