#include "helpers.hpp"

#include <cmath>
#include <string>
#include <vector>

#include "TF1.h"
#include "TRandom.h"

InitialConditions GenerateParticleImpulse() {
  InitialConditions cond;

  cond.phi = 2 * M_PI * gRandom->Rndm();
  cond.theta = M_PI * gRandom->Rndm();
  cond.p_module = gRandom->Exp(1);
  cond.px = cond.p_module * cos(cond.phi) * sin(cond.theta);
  cond.py = cond.p_module * sin(cond.theta) * sin(cond.phi);
  cond.pz = cond.p_module * cos(cond.theta);

  return cond;
}

Particle GenerateParticle(double px, double py, double pz) {
  double x = gRandom->Rndm();

  std::string name;

  if (x <= 0.4)
    name = "Pion+";
  else if (x <= 0.8)
    name = "Pion-";
  else if (x <= 0.85)
    name = "Kaon+";
  else if (x <= 0.9)
    name = "Kaon-";
  else if (x <= 0.945)
    name = "Proton+";
  else if (x <= 0.99)
    name = "Proton-";
  else
    name = "K*";

  return Particle(name, px, py, pz);
}

void AnalizeData(std::vector<Particle> const& particles, TH1F* totalInvMass,
                 TH1F* invMassOppositeCharge, TH1F* invMassSameCharge,
                 TH1F* invMassKPOpposite, TH1F* invMassKPSame) {
  for (size_t i = 0; i < particles.size() - 1; i++) {
    for (size_t j = i + 1; j < particles.size(); j++) {
      double invMass = particles[j].InvMass(particles[i]);

      const auto first = particles[j];
      const std::string first_type =
          first.GetName().substr(0, first.GetName().size() - 1);
      const auto second = particles[i];
      const std::string second_type =
          second.GetName().substr(0, second.GetName().size() - 1);

      totalInvMass->Fill(invMass);

      // If same charge
      if (first.GetCharge() * second.GetCharge() > 0) {
        invMassSameCharge->Fill(invMass);

        if ((first_type == "Pion" && second_type == "Kaon") ||
            (first_type == "Kaon" && second_type == "Pion"))
          invMassKPSame->Fill(invMass);

      } else if (first.GetCharge() * second.GetCharge() <
                 0) {  // Opposite charge
        invMassOppositeCharge->Fill(invMass);

        if ((first_type == "Pion" && second_type == "Kaon") ||
            (first_type == "Kaon" && second_type == "Pion"))
          invMassKPOpposite->Fill(invMass);
      }
    }
  }
}