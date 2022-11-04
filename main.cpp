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

  c1->Divide(3, 2);
  c2->Divide(3, 3);

  // Particles attributes
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

  // Particles Analysis
  TH1F* totalInvMass = new TH1F("totalInv", "Total Mass Invariant", 1000, 0, 4);
  TH1F* invMassOppositeCharge = new TH1F(
      "invmassoc", "Mass invariant of opposite charge particles", 1000, 0, 4);
  TH1F* invMassSameCharge = new TH1F(
      "invmasssc", "Mass invariant of same charge particles", 1000, 0, 4);
  TH1F* invMassKPOpposite =
      new TH1F("invmasskp", "Mass invariant of Kaon/Pion with opposite charge",
               1000, 0, 4);
  TH1F* invMassKPSame = new TH1F(
      "invmasskpsame", "Mass invariant Kaon/Pion with same charge", 1000, 0, 4);

  TH1F* invMassDaughters = new TH1F(
      "invmassdau", "Mass invariant of daughters of decay", 1000, 0, 2);

  invMassOppositeCharge->Sumw2();
  invMassSameCharge->Sumw2();

  invMassKPOpposite->Sumw2();
  invMassKPSame->Sumw2();

  // Simulating Events
  std::vector<Particle> eventParticles;
  for (size_t i = 0; i < 1E4; i++) {
    eventParticles.clear();

    for (size_t j = 0; j != 100; j++) {
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

        invMassDaughters->Fill(p.InvMass(k));

        particleDistribution->Fill(6);
      } else {
        particleDistribution->Fill(
            Particle::FindParticleTest(particle.GetName()));
        eventParticles.push_back(particle);
      }
    }

    // Data Analysis
    AnalizeData(eventParticles, totalInvMass, invMassOppositeCharge,
                invMassSameCharge, invMassKPOpposite, invMassKPSame);
  }

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
  totalInvMass->Draw();
  c2->cd(2);
  invMassSameCharge->Draw();
  c2->cd(3);
  invMassKPOpposite->Draw();
  c2->cd(4);
  invMassKPSame->Draw();
  c2->cd(5);
  invMassDaughters->Draw();

  c2->cd(6);
  TH1F* firstSum = new TH1F(*invMassOppositeCharge);
  firstSum->Add(invMassOppositeCharge, invMassSameCharge, 1, -1);
  firstSum->SetTitle(
      "Mass invariant of all same charge particles minus all "
      "particles with opposite charge");
  firstSum->Draw();

  c2->cd(7);
  TH1F* secondSum = new TH1F(*invMassKPOpposite);
  secondSum->SetTitle(
      "Mass invariant of pk with opposite charge minus pk with same charge");
  secondSum->Add(invMassKPOpposite, invMassKPSame, 1, -1);
  secondSum->Draw();

  return 0;
}