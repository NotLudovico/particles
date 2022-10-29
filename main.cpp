#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TH1F.h"
#include "TRandom.h"
#include "helpers.hpp"
#include "particle.hpp"
#include "particleType.hpp"
#include "resonanceType.hpp"

int Main() {
  Particle::AddParticleType("Pion+", 0.13957, 1);
  Particle::AddParticleType("Pion-", 0.13957, -1);
  Particle::AddParticleType("Kaon+", 0.49367, 1);
  Particle::AddParticleType("Kaon-", 0.49367, -1);
  Particle::AddParticleType("Proton+", 0.93827, 1);
  Particle::AddParticleType("Proton-", 0.93827, -1);
  Particle::AddParticleType("K*", 0.89166, 0, 0.050);

  gRandom->SetSeed();
  TCanvas* c1 = new TCanvas("Data About Generated Particles", "c1", 1000, 1000);
  TCanvas* c2 = new TCanvas("Data Analysis", "c2", 1000, 1000);

  c1->Divide(2, 2);

  TH1F* particleDistribution = new TH1F("pd", "Particle Distribution", 7, 0, 7);
  TH1F* phiDistribution =
      new TH1F("phi", "Phi Angle Distribution", 1000, 0, 2 * M_PI);
  TH1F* thetaDistribution =
      new TH1F("theta", "Theta Angle Distribution", 1000, 0, M_PI);
  TH1F* impulseDistribution =
      new TH1F("impulse", "Impulse Distribution", 1000, 0, 4);

  // Simulating Events
  std::vector<Particle> eventParticles;
  for (size_t i = 0; i < 1E5; i++) {
    eventParticles.clear();

    for (size_t j = 0; j != 100; j++) {
      InitialConditions impulseProperties = GenerateParticleImpulse();
      auto [phi, theta, p_module, px, py, pz] = impulseProperties;

      phiDistribution->Fill(phi);
      thetaDistribution->Fill(theta);
      impulseDistribution->Fill(p_module);

      Particle particle = GenerateParticle(px, py, pz);

      if (particle.GetName() == "K*") {
        double probability = gRandom->Rndm();

        Particle p = Particle("Pion+");
        Particle k = Particle("Kaon-");

        if (probability > 0.5) {
          p.SetIndex("Pion-");
          k.SetIndex("Kaon+");
        }

        eventParticles.push_back(particle);

        particle.Decay2body(p, k);

        eventParticles.push_back(p);
        eventParticles.push_back(k);

        particleDistribution->Fill(6);
      } else {
        particleDistribution->Fill(
            Particle::FindParticleTest(particle.GetName()));
        eventParticles.push_back(particle);
      }
    }
  }

  c1->cd(1);
  particleDistribution->Draw();
  c1->cd(2);
  phiDistribution->Draw();
  c1->cd(3);
  thetaDistribution->Draw();
  c1->cd(4);
  impulseDistribution->Draw();

  return 0;
}