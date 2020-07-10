#include "KSTrajTermMovingSurfaceBuilder.h"

#include "KSRootBuilder.h"

using namespace Kassiopeia;
using namespace std;

namespace katrin
{

template<> KSTrajTermMovingSurfaceBuilder::~KComplexElement() {}

STATICINT sKSTrajTermMovingSurfaceStructure =
    KSTrajTermMovingSurfaceBuilder::Attribute<string>("name") +
    KSTrajTermMovingSurfaceBuilder::Attribute<double>("theta") +
    KSTrajTermMovingSurfaceBuilder::Attribute<double>("phi") +
    KSTrajTermMovingSurfaceBuilder::Attribute<string>("value_formula") +
    KSTrajTermMovingSurfaceBuilder::Attribute<double>("value_min") +
    KSTrajTermMovingSurfaceBuilder::Attribute<double>("value_max");

STATICINT sToolboxKSTrajTermMovingSurface = KSRootBuilder::ComplexElement<KSTrajTermMovingSurface>("kstraj_term_moving_surface");

}  // namespace katrin
