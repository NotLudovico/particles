#include "helpers.hpp"

#include <cmath>
#include <string>
#include <vector>

#include "TH1F.h"
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

void AnalizeData(std::vector<Particle> const& particles, TH1F* totalInvMass,
                 TH1F* invMassOppositeCharge, TH1F* invMassSameCharge,
                 TH1F* invMassKPOpposite, TH1F* invMassKPSame) {
  for (size_t i = 0; i < particles.size() - 1; i++) {
    for (size_t j = i + 1; j < particles.size(); j++) {
      double invMass = particles[j].InvMass(particles[i]);
      const auto first = particles[j];
      const auto second = particles[i];

      totalInvMass->Fill(invMass);

      // If same charge
      if (first.GetCharge() * second.GetCharge() > 0) {
        invMassSameCharge->Fill(invMass);

        if ((first.GetType() == "Pion" && second.GetType() == "Kaon") ||
            (first.GetType() == "Kaon" && second.GetType() == "Pion"))
          invMassKPSame->Fill(invMass);
      } else {
        invMassOppositeCharge->Fill(invMass);

        if ((first.GetType() == "Pion" && second.GetType() == "Kaon") ||
            (first.GetType() == "Kaon" && second.GetType() == "Pion"))
          invMassKPOpposite->Fill(invMass);
      }
    }
  }
}