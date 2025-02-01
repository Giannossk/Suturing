#ifndef SUTURING_H
#define SUTURING_H

#include <sofa/core/ObjectFactory.h>
#include <sofa/core/BaseObject.h>
#include <sofa/core/objectmodel/Data.h>
#include <sofa/component/solidmechanics/spring/SpringForceField.h>
#include <sofa/component/statecontainer/MechanicalObject.h>
#include <sofa/defaulttype/Vec3dTypes.h>

namespace sofa {
namespace component {
namespace suturing {

class Suturing : public core::objectmodel::BaseObject
{
public:
    SOFA_CLASS(Suturing, core::objectmodel::BaseObject);

    Data< core::objectmodel::SPtr< component::statecontainer::MechanicalObject<defaulttype::Vec3d> > > d_tissueObject;
    Data< core::objectmodel::SPtr< solidmechanics::spring::SpringForceField > > d_sutureSpring;
    Data<bool> d_autoSuture;

    Suturing();
    virtual ~Suturing();

    void init() override;
    void handleEvent(core::objectmodel::Event* event) override;

protected:
    void updateSuture(double dt);
};

} // namespace suturing
} // namespace component
} // namespace sofa

#endif // SUTURING_H
