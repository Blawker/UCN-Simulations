/* Conversion tool for simple calculus
Author: Thomas Guilbaud
Created: 07 July 2020
*/

#include <iostream>
#include <cmath>

const double e = 1.602176634e-19; // J
const double c = 299792458; // m/s

double velocityToKineticEnergy(double m, double v) {
  return(0.5*m*v*v); // J
}

double velocityToMomentum(double m, double v) {
  return(m*v); // kg.m/s
}

double velocityToLorentzFactor(double v) {
  return(1/sqrt(1-v*v/(c*c)));
}

double lorentzFactorToVelocity(double gamma) {
  return(c*sqrt(1-1/(gamma*gamma)));
}

double kineticEnergyToVelocity(double m, double ke) {
  return(sqrt(2*ke/m)); // m/s
}

double restEnergyToRestMass(double ke) {
  return(ke/(c*c)); // kg
}

double energyMomentumRelation(double p, double m_rest) {
  return(sqrt((p*p*c*c) + (m_rest*m_rest*c*c*c*c)));
}

double massEnergyRelation(double m) {
  return(m*c*c); // J
}

double massRelToLorentzFactor(double m_rel, double m_rest) {
  return(m_rel/m_rest);
}

double jouleTo_eV(double joule) {
  return(joule/e); // eV
}

double eV_ToJoule(double eV) {
  return(eV*e); // J
}

int main(int argc, char* argv[]) {
  if (argc != 1) {
    std::cout << "Usage: " << argv[0] << std::endl;
  }

  const double neutronMass = 1.6749e-27; // kg
  const double protonMass = 1.6726e-27; // kg
  const double electronMass = 9.1094e-31; // kg

  int particle = 0; // 1: electron, 2: neutron, 3: proton
  int variable = 0;
  int isRelativistic;
  double mass_rest = 0.0;
  double mass_rel = 0.0;
  double lorentz_factor = 1.0;
  double velocity = 0.0;
  double totalEnergy_J = 0.0;
  double totalEnergy_eV = 0.0;
  double restEnergy_J = 0.0;
  double restEnergy_eV = 0.0;
  double kineticEnergy_J = 0.0;
  double kineticEnergy_eV = 0.0;
  double momentum = 0.0;

  std::cout << std::endl
            << "1: electron        2: neutron        3: proton" << std::endl
            << "Select the particle: ";
  std::cin >> particle;

  if (particle == 1) mass_rest = electronMass;
  else if (particle == 2) mass_rest = neutronMass;
  else if (particle == 3) mass_rest = protonMass;

  std::cout << "Relativitic particle (0: false / 1: true): ";
  std::cin >> isRelativistic;

  if (isRelativistic == 1) {
    std::cout << std::endl
              << "1: Velocity        2: Momentum       3: Kinetic Energy (J)" << std::endl
              << "4: Rest Mass       5: Relative Mass  6: Kinetic Energy (eV)" << std::endl
              << "7: Lorentz Factor" << std::endl
              << "Select the variable to convert: ";
    std::cin >> variable;

    if (variable == 1) { // velocity
      std::cout << std::endl
                << "Enter the value in m/s: ";
      std::cin >> velocity;
      lorentz_factor = velocityToLorentzFactor(velocity);
      mass_rel = lorentz_factor*mass_rest;
      restEnergy_J = massEnergyRelation(mass_rest);
      momentum = velocityToMomentum(mass_rel, velocity);
      totalEnergy_J = massEnergyRelation(mass_rel);//energyMomentumRelation(momentum, mass_rest);
      kineticEnergy_J = totalEnergy_J - restEnergy_J;
      restEnergy_eV = jouleTo_eV(restEnergy_J);
      kineticEnergy_eV = jouleTo_eV(kineticEnergy_J);
      totalEnergy_eV = jouleTo_eV(totalEnergy_J);
    }
    else if (variable == 3) {
      std::cout << std::endl
                << "Enter the value in J: ";
      std::cin >> kineticEnergy_J;
      restEnergy_J = massEnergyRelation(mass_rest);
      lorentz_factor = kineticEnergy_J/restEnergy_J+1;
      mass_rel = lorentz_factor*mass_rest;
      velocity = lorentzFactorToVelocity(lorentz_factor);
      restEnergy_J = massEnergyRelation(mass_rest);
      momentum = velocityToMomentum(mass_rel, velocity);
      totalEnergy_J = massEnergyRelation(mass_rel);
      restEnergy_eV = jouleTo_eV(restEnergy_J);
      kineticEnergy_eV = jouleTo_eV(kineticEnergy_J);
      totalEnergy_eV = jouleTo_eV(totalEnergy_J);
    }
    else if (variable == 4) { // rest mass
      mass_rel = lorentz_factor*mass_rest;
      velocity = lorentzFactorToVelocity(lorentz_factor);
      restEnergy_J = massEnergyRelation(mass_rest);
      momentum = velocityToMomentum(mass_rel, velocity);
      totalEnergy_J = massEnergyRelation(mass_rel);
      kineticEnergy_J = totalEnergy_J - restEnergy_J;
      restEnergy_eV = jouleTo_eV(restEnergy_J);
      kineticEnergy_eV = jouleTo_eV(kineticEnergy_J);
      totalEnergy_eV = jouleTo_eV(totalEnergy_J);
    }
    else if (variable == 5) { // relative mass
      std::cout << std::endl
                << "Enter the value in kg: ";
      std::cin >> mass_rel;
      lorentz_factor = mass_rel/mass_rest;
      velocity = lorentzFactorToVelocity(lorentz_factor);
      restEnergy_J = massEnergyRelation(mass_rest);
      momentum = velocityToMomentum(mass_rel, velocity);
      totalEnergy_J = massEnergyRelation(mass_rel);
      kineticEnergy_J = totalEnergy_J - restEnergy_J;
      restEnergy_eV = jouleTo_eV(restEnergy_J);
      kineticEnergy_eV = jouleTo_eV(kineticEnergy_J);
      totalEnergy_eV = jouleTo_eV(totalEnergy_J);
    }
    else if (variable == 6) {
      std::cout << std::endl
                << "Enter the value in eV: ";
      std::cin >> kineticEnergy_eV;
      kineticEnergy_J = eV_ToJoule(kineticEnergy_eV);
      restEnergy_J = massEnergyRelation(mass_rest);
      lorentz_factor = kineticEnergy_J/restEnergy_J+1;
      mass_rel = lorentz_factor*mass_rest;
      velocity = lorentzFactorToVelocity(lorentz_factor);
      restEnergy_J = massEnergyRelation(mass_rest);
      momentum = velocityToMomentum(mass_rel, velocity);
      totalEnergy_J = massEnergyRelation(mass_rel);
      restEnergy_eV = jouleTo_eV(restEnergy_J);
      totalEnergy_eV = jouleTo_eV(totalEnergy_J);
    }
    else if (variable == 7) {
      std::cout << std::endl
                << "Enter the value in: ";
      std::cin >> lorentz_factor;
      mass_rel = lorentz_factor*mass_rest;
      velocity = lorentzFactorToVelocity(lorentz_factor);
      restEnergy_J = massEnergyRelation(mass_rest);
      momentum = velocityToMomentum(mass_rel, velocity);
      totalEnergy_J = massEnergyRelation(mass_rel);
      kineticEnergy_J = totalEnergy_J - restEnergy_J;
      restEnergy_eV = jouleTo_eV(restEnergy_J);
      kineticEnergy_eV = jouleTo_eV(kineticEnergy_J);
      totalEnergy_eV = jouleTo_eV(totalEnergy_J);
    }

    std::cout << "Velocity       = " << velocity << " m/s" << std::endl
              << "Momentum       = " << momentum << " kg.m/s" << std::endl
              << "Total Energy   = " << totalEnergy_J << " J" << std::endl
              << "               = " << totalEnergy_eV << " eV" << std::endl
              << "Kinetic Energy = " << kineticEnergy_J << " J" << std::endl
              << "               = " << kineticEnergy_eV << " eV" << std::endl
              << "Rest Energy    = " << restEnergy_J << " J" << std::endl
              << "               = " << restEnergy_eV << " eV" << std::endl
              << "Rest Mass      = " << mass_rest << " kg" << std::endl
              << "Relative Mass  = " << mass_rel << " kg" << std::endl
              << "Lorentz Factor = " << lorentz_factor << std::endl;

  }

  else {
    std::cout << std::endl
              << "1: Velocity        2: Momentum       3: Kinetic Energy (J)" << std::endl
              << "4: Rest Mass                         6: Kinetic Energy (eV)" << std::endl
              << "Select the variable to convert: ";
    std::cin >> variable;

    if (variable == 1) { // velocity
      std::cout << std::endl
                << "Enter the value in m/s: ";
      std::cin >> velocity;
      restEnergy_J = massEnergyRelation(mass_rest);
      momentum = velocityToMomentum(mass_rest, velocity);
      kineticEnergy_J = velocityToKineticEnergy(mass_rest, velocity);
      restEnergy_eV = jouleTo_eV(restEnergy_J);
      kineticEnergy_eV = jouleTo_eV(kineticEnergy_J);
    }
    else if (variable == 3) {
      std::cout << std::endl
                << "Enter the value in J: ";
      std::cin >> kineticEnergy_J;
      restEnergy_J = massEnergyRelation(mass_rest);
      velocity = kineticEnergyToVelocity(mass_rest, kineticEnergy_J);
      restEnergy_J = massEnergyRelation(mass_rest);
      momentum = velocityToMomentum(mass_rest, velocity);
      restEnergy_eV = jouleTo_eV(restEnergy_J);
      kineticEnergy_eV = jouleTo_eV(kineticEnergy_J);
    }
    else if (variable == 4) { // rest mass
      restEnergy_J = massEnergyRelation(mass_rest);
      restEnergy_eV = jouleTo_eV(restEnergy_J);
    }
    else if (variable == 6) {
      std::cout << std::endl
                << "Enter the value in eV: ";
      std::cin >> kineticEnergy_eV;
      kineticEnergy_J = eV_ToJoule(kineticEnergy_eV);
      restEnergy_J = massEnergyRelation(mass_rest);
      velocity = kineticEnergyToVelocity(mass_rest, kineticEnergy_J);
      restEnergy_J = massEnergyRelation(mass_rest);
      momentum = velocityToMomentum(mass_rest, velocity);
      restEnergy_eV = jouleTo_eV(restEnergy_J);
    }

    std::cout << "Velocity       = " << velocity << " m/s" << std::endl
              << "Momentum       = " << momentum << " kg.m/s" << std::endl
              << "Kinetic Energy = " << kineticEnergy_J << " J" << std::endl
              << "               = " << kineticEnergy_eV << " eV" << std::endl
              << "Rest Energy    = " << restEnergy_J << " J" << std::endl
              << "               = " << restEnergy_eV << " eV" << std::endl
              << "Rest Mass      = " << mass_rest << " kg" << std::endl;
  }

  return(EXIT_SUCCESS);
}
