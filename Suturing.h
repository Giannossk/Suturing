#ifndef SUTURING_H
#define SUTURING_H

#include <sofa/core/ObjectFactory.h>
#include <sofa/core/BaseObject.h>
#include <sofa/core/objectmodel/Data.h>

// Include the performer and spring components:
#include <sofa/gui/component/performer/SuturePointPerformer.h>
#include <sofa/component/solidmechanics/spring/SpringForceField.h>

// Forward-declare the simulation event we'll handle
#include <sofa/simulation/EndStepEvent.h>

namespace sofa
{
namespace component
{
namespace suturing
{

class Suturing : public core::objectmodel::BaseObject
{
public:
    SOFA_CLASS(Suturing, core::objectmodel::BaseObject);

    // Data fields to hold pointers to the performer and the spring.
    Data< core::objectmodel::SPtr< gui::component::performer::SuturePointPerformer > > d_suturePerformer;
    Data< core::objectmodel::SPtr< solidmechanics::spring::SpringForceField > > d_sutureSpring;

    Suturing();
    virtual ~Suturing();

    // Standard initialization function (called once after construction)
    void init() override;

    // Override event handler to update suturing each simulation step.
    void handleEvent(core::objectmodel::Event* event) override;

protected:
    /// Update suture spring based on picked points.
    void updateSuture(double dt);
};

} // namespace suturing
} // namespace component
} // namespace sofa

#endif // SUTURING_H
