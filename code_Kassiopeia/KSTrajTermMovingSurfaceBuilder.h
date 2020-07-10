#ifndef Kassiopeia_KSTrajTermMovingSurfaceBuilder_h_
#define Kassiopeia_KSTrajTermMovingSurfaceBuilder_h_

#include "KComplexElement.hh"
#include "KSTrajTermMovingSurface.h"

using namespace Kassiopeia;
namespace katrin
{

typedef KComplexElement<KSTrajTermMovingSurface> KSTrajTermMovingSurfaceBuilder;

template<> inline bool KSTrajTermMovingSurfaceBuilder::AddAttribute(KContainer* aContainer)
{
    if (aContainer->GetName() == "name") {
        aContainer->CopyTo(fObject, &KNamed::SetName);
        return true;
    }
    if (aContainer->GetName() == "theta") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurface::SetTheta);
        return true;
    }
    if (aContainer->GetName() == "phi") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurface::SetPhi);
        return true;
    }
    if (aContainer->GetName() == "value_formula") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurface::SetValueFormula);
        return true;
    }
    if (aContainer->GetName() == "value_min") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurface::SetValueMin);
        return true;
    }
    if (aContainer->GetName() == "value_max") {
        aContainer->CopyTo(fObject, &KSTrajTermMovingSurface::SetValueMax);
        return true;
    }
    return false;
}

}  // namespace katrin
#endif
