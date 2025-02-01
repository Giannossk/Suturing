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

/**
 * \brief A dynamic suturing plugin for SOFA.
 *
 * This plugin automatically selects two candidate points from a tissue MechanicalObject
 * (based on a chosen criterion—in this example, the points with the minimum and maximum
 * x-coordinates) and connects them using a SpringForceField. It listens for simulation
 * end-of-step events (EndStepEvent) and updates the spring to “suture” the points together.
 *
 * \note The dynamic selection criterion can be modified to suit specific simulation needs.
 */
class Suturing : public core::objectmodel::BaseObject
{
public:
    SOFA_CLASS(Suturing, core::objectmodel::BaseObject);

    /// Pointer to the MechanicalObject that provides tissue particle positions.
    Data< core::objectmodel::SPtr< component::statecontainer::MechanicalObject<defaulttype::Vec3d> > > d_tissueObject;

    /// Pointer to the SpringForceField component that connects the two selected points.
    Data< core::objectmodel::SPtr< solidmechanics::spring::SpringForceField > > d_sutureSpring;

    /// If true, automatically selects suture points dynamically (ignores mouse input).
    Data<bool> d_autoSuture;

    /**
     * \brief Constructor for the Suturing plugin.
     *
     * Initializes data fields with default values.
     */
    Suturing();

    /**
     * \brief Destructor.
     */
    virtual ~Suturing();

    /**
     * \brief Initializes the plugin.
     *
     * Verifies that a tissue MechanicalObject is provided and creates a SpringForceField
     * if one is not already assigned.
     */
    void init() override;

    /**
     * \brief Handles simulation events.
     *
     * Listens for EndStepEvent and calls updateSuture() at the end of each simulation step.
     *
     * \param event Pointer to the incoming event.
     */
    void handleEvent(core::objectmodel::Event* event) override;

protected:
    /**
     * \brief Dynamically updates the suture connection.
     *
     * Scans the positions in the tissue MechanicalObject to select two candidate points.
     * In this example, it selects the points with the lowest and highest x-coordinates.
     * It then computes the Euclidean distance between them (rest length) and updates the
     * SpringForceField's indices and rest length.
     *
     * \param dt The current time step (unused in this implementation).
     */
    void updateSuture(double dt);
};

} // namespace suturing
} // namespace component
} // namespace sofa

#endif // SUTURING_H
