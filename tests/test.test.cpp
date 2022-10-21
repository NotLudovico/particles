#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../particle.hpp"
#include "../particleType.hpp"
#include "../resonanceType.hpp"
#include "doctest.h"

TEST_CASE("Testing Getters") {
  ParticleType p1 = ParticleType("P+", 10, 3);
  ResonanceType p2 = ResonanceType("K*", 1, 2, 3);

  std::cout << "PRINTING P1 (P+,10,3):\n";
  p1.Print();

  std::cout << "PRINTING P2 (K*,1,2,3):\n";
  p2.Print();

  CHECK("P+" == p1.GetName());
  CHECK(10 == p1.GetMass());
  CHECK(3 == p1.GetCharge());

  CHECK("K*" == p2.GetName());
  CHECK(1 == p2.GetMass());
  CHECK(2 == p2.GetCharge());
  CHECK(3 == p2.GetWidth());
}

TEST_CASE("Testing Particle Type") {
  Particle::AddParticleType("P+", 1, 2);
  Particle::AddParticleType("K*", 1, 2, 3);
  Particle::AddParticleType("K*", 1, 2, 3);

  CHECK(Particle::FindParticleTest("P+") == 0);
  CHECK(Particle::FindParticleTest("K*") == 1);
  CHECK(Particle::FindParticleTest("P-") == -1);

  Particle::PrintTable();
}
