#include <cmath>
#include <iostream>
#include <vector>

#include "TH1F.h"
#include "TRandom.h"
#include "particle.hpp"
#include "particleType.hpp"
#include "resonanceType.hpp"

int Main() {
  Particle::AddParticleType("Pion-", 0.13957, -1);
  Particle::AddParticleType("Kaon+", 0.49367, 1);
  Particle::AddParticleType("Kaon-", 0.49367, -1);
  Particle::AddParticleType("Proton+", 0.93827, 1);
  Particle::AddParticleType("Proton-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);

  Particle::PrintTable();

  gRandom->SetSeed();

  std::vector<Particle> eventParticles;

  TH1F* particleDistribution = new TH1F("pd", "Particle Distribution", 6, 0, 6);

  for (size_t i = 0; i < 1E5; i++) {
    eventParticles.clear();

    for (size_t j = 0; j != 100; j++) {
      double x = gRandom->Rndm();
      double phi = 2 * M_PI * gRandom->Rndm();
      double theta = M_PI * gRandom->Rndm();
      double impulse = gRandom->Exp(1);

      double px = impulse * cos(theta) * sin(phi);
      double py = impulse * sin(theta) * sin(phi);
      double pz = impulse * cos(phi);

      char* name = "";
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

      if (name == "K*") {
        Particle resonance = Particle("K*", px, py, pz);

        double probability = gRandom->Rndm();

        Particle p = Particle("Pion+");
        Particle k = Particle("Kaon-");

        if (probability > 0.5) {
          p.SetIndex("Pion-");
          k.SetIndex("Kaon+");
        }

        // resonance.Decay2body(p, k);
        // eventParticles.push_back(p);
        // eventParticles.push_back(k);

        particleDistribution->Fill(p.GetIndex());
        particleDistribution->Fill(k.GetIndex());
      } else {
        particleDistribution->Fill(index);
        // eventParticles.push_back(Particle(name, px, py, pz));
      }
    }
  }

  particleDistribution->Draw();
}