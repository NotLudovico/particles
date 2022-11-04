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
  TCanvas* c1 = new TCanvas("c1", "Data About Generated Particles", 2000, 2000);
  TCanvas* c2 = new TCanvas("c2", "Data Analysis", 2000, 2000);

  c1->Divide(3, 3);
  c2->Divide(3, 2);

  TH1F* particleDistribution = new TH1F("pd", "Particle Distribution", 7, 0, 7);
  TH1F* phiDistribution =
      new TH1F("phi", "Phi Angle Distribution", 1000, 0, 2 * M_PI);
  TH1F* thetaDistribution =
      new TH1F("theta", "Theta Angle Distribution", 1000, 0, M_PI);
  TH1F* impulseDistribution =
      new TH1F("impulse", "Impulse Distribution", 1000, 0, 4);
  TH1F* traverseImpulseDistribution =
      new TH1F("traverse", "Traverse Impulse Distribution", 1000, 0, 4);
  TH1F* energyDistribution =
      new TH1F("energy", "Energy Distribution", 1000, 0, 2);
  TH1F* invMassOppositeCharge = new TH1F(
      "invmassoc", "Mass invariant of opposite charge particles", 1000, 0, 4);
  TH1F* invMassSameCharge = new TH1F(
      "invmasssc", "Mass invariant of opposite charge particles", 1000, 0, 4);
  TH1F* invMassKaonPlus =
      new TH1F("invmasskp", "Mass invariant of Kaon+/Pion+", 1000, 0, 4);
  TH1F* invMassKaonMinus =
      new TH1F("invmasskm", "Mass invariant of Kaon-/Pion-", 1000, 0, 4);
  TH1F* invMassDaughters = new TH1F(
      "invmassdau", "Mass invariant of daughters of decay", 1000, 0, 4);

  int max_particles = 100;
  // Simulating Events
  std::vector<Particle> eventParticles;
  std::vector<Particle> daughters;

  for (size_t i = 0; i < 1E5; i++) {
    eventParticles.clear();

    for (size_t j = 0; j != max_particles; j++) {
      InitialConditions impulseProperties = GenerateParticleImpulse();
      auto [phi, theta, p_module, px, py, pz] = impulseProperties;

      Particle particle = GenerateParticle(px, py, pz);

      phiDistribution->Fill(phi);
      thetaDistribution->Fill(theta);
      impulseDistribution->Fill(p_module);
      traverseImpulseDistribution->Fill(sqrt(pow(px, 2) + pow(py, 2)));
      energyDistribution->Fill(particle.GetEnergy());

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

        daughters.push_back(p);
        daughters.push_back(k);

        particleDistribution->Fill(6);
      } else {
        particleDistribution->Fill(
            Particle::FindParticleTest(particle.GetName()));
        eventParticles.push_back(particle);
      }
    }

    // Data Analysis
    for (size_t j = 0; j != eventParticles.size(); j++) {
      for (size_t k = 0; k != eventParticles.size(); k++) {
        if (k != j) {
          double invMass = eventParticles[j].InvMass(eventParticles[k]);
          if (eventParticles[j].GetCharge() == eventParticles[k].GetCharge()) {
            invMassSameCharge->Fill(invMass);
          } else {
            invMassOppositeCharge->Fill(invMass);
          }

          if (eventParticles[j].GetName() == "Pion+" &&
              eventParticles[k].GetName() == "Kaon+") {
            invMassKaonPlus->Fill(invMass);
          } else if (eventParticles[j].GetName() == "Pion-" &&
                     eventParticles[k].GetName() == "Kaon-") {
            invMassKaonMinus->Fill(invMass);
          }
        }
      }
    }

    // Analizing Daughters
    for (size_t j = 0; j != daughters.size(); j++) {
      for (size_t k = 0; k != daughters.size(); k++) {
        if (j != k) {
          invMassDaughters->Fill(daughters[j].InvMass(daughters[k]));
        }
      }
    }
  }

  std::cout << "TEST";
  c1->cd(1);
  particleDistribution->Draw();
  c1->cd(2);
  phiDistribution->Draw();
  c1->cd(3);
  thetaDistribution->Draw();
  c1->cd(4);
  impulseDistribution->Draw();
  c1->cd(5);
  traverseImpulseDistribution->Draw();
  c1->cd(6);
  energyDistribution->Draw();

  c2->cd(1);
  invMassOppositeCharge->Draw();
  c2->cd(2);
  invMassSameCharge->Draw();
  c2->cd(3);
  invMassKaonPlus->Draw();
  c2->cd(4);
  invMassKaonMinus->Draw();
  c2->cd(5);
  invMassDaughters->Draw();
  return 0;
}