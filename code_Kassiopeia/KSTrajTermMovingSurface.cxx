#include "KSTrajTermMovingSurface.h"

#include "KConst.h"

namespace Kassiopeia
{

KSTrajTermMovingSurface::KSTrajTermMovingSurface() :
  fTheta(0.),
  fPhi(0.),
  fValueFormula("x"),
  fValueMin(0.),
  fValueMax(0.)
{}
KSTrajTermMovingSurface::KSTrajTermMovingSurface(const KSTrajTermMovingSurface& aCopy) :
  KSComponent(),
  fTheta(aCopy.fTheta),
  fPhi(aCopy.fPhi),
  fValueFormula(aCopy.fValueFormula),
  fValueMin(aCopy.fValueMin),
  fValueMax(aCopy.fValueMax),
{}
KSTrajTermMovingSurface* KSTrajTermMovingSurface::Clone() const
{
    return new KSTrajTermMovingSurface(*this);
}
KSTrajTermMovingSurface::~KSTrajTermMovingSurface() {}

void KSTrajTermMovingSurface::Differentiate(double /*aTime*/, const KSTrajExactParticle& aParticle,
                                      KSTrajExactDerivative& aDerivative) const
{
    KThreeVector tForce(0., 0., 0.);

    if () { // Act like a Heaviside function for the distance to the surface 
      // Change angle ° to rad
      double fThetaRad = fTheta * katrin::KConst::Pi()/180;
      double fPhiRad = fPhi * katrin::KConst::Pi()/180;

      // Initialize the direction of the force
      tForce = new KThreeVector(sin(fThetaRad) * cos(fPhiRad), sin(fThetaRad) * sin(fPhiRad), cos(fThetaRad));

      fValueFunction = new TF1("function", fValueFormula.c_str(), fValueMin, fValueMax);
      double tTimeValue = aParticle.GetTime();
      double tForceMagnitude = aParticle.GetMass() * fValueFunction->Derivative2(tTimeValue, 0, 0.001);
      tForce.SetMagnitude(tForceMagnitude);
    }

    aDerivative.AddToForce(tForce);
}

void KSTrajTermMovingSurface::Differentiate(double /*aTime*/, const KSTrajExactSpinParticle& aParticle,
                                      KSTrajExactSpinDerivative& aDerivative) const
{
    aDerivative.AddToForce(fGravity * aParticle.GetMass());
}

// void KSTrajTermMovingSurface::Differentiate(double /*aTime*/, const KSTrajAdiabaticParticle& aParticle, KSTrajAdiabaticDerivative& aDerivative ) const
// {
//     aDerivative.AddToForce( fGravity );
// }

void KSTrajTermMovingSurface::Differentiate(double /*aTime*/, const KSTrajAdiabaticSpinParticle& aParticle,
                                      KSTrajAdiabaticSpinDerivative& aDerivative) const
{
    aDerivative.AddToForce(fGravity * aParticle.GetMass());
}

// void KSTrajTermMovingSurface::Differentiate(double /*aTime*/, const KSTrajElectricParticle& aParticle, KSTrajElectricDerivative& aDerivative ) const
// {
//     aDerivative.AddToForce( fGravity );
// }
//
// void KSTrajTermMovingSurface::Differentiate(double /*aTime*/, const KSTrajMagneticParticle& aParticle, KSTrajMagneticDerivative& aDerivative ) const
// {
//     aDerivative.AddToForce( fGravity );
// }

void KSTrajTermMovingSurface::SetGravity(const KThreeVector& aGravity)
{
    fGravity = aGravity;
    return;
}

}  // namespace Kassiopeia
