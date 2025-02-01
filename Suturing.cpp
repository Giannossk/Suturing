#include "Suturing.h"
#include <sofa/core/ObjectFactory.h>
#include <sofa/core/ExecParams.h>
#include <sofa/simulation/EndStepEvent.h>
#include <sofa/core/vector.h>
#include <cmath>

namespace sofa
{
namespace component
{
namespace suturing
{

Suturing::Suturing()
    : d_suturePerformer(initData(&d_suturePerformer,
                                 core::objectmodel::SPtr<gui::component::performer::SuturePointPerformer>(),
                                 "suturePerformer",
                                 "Component to pick suture points"))
    , d_sutureSpring(initData(&d_sutureSpring,
                              core::objectmodel::SPtr<solidmechanics::spring::SpringForceField>(),
                              "sutureSpring",
                              "Spring that connects the sutured points"))
{
}

Suturing::~Suturing()
{
}

void Suturing::init()
{
    // Create the SuturePointPerformer if it has not been provided already.
    if (!d_suturePerformer.getValue())
    {
        auto performer = core::objectmodel::New<gui::component::performer::SuturePointPerformer>();
        // (Optional: configure performer parameters here.)
        d_suturePerformer.setValue(performer);
        // Add performer as a child to have its lifecycle managed.
        this->addObject(performer);
    }

    // Create the SpringForceField if not provided.
    if (!d_sutureSpring.getValue())
    {
        auto spring = core::objectmodel::New<solidmechanics::spring::SpringForceField>();
        // Set default spring parameters (adjust as needed).
        spring->d_stiffness.setValue(200.0);
        spring->d_damping.setValue(5.0);
        // (In a complete implementation, you might preconfigure other data such as rest lengths.)
        d_sutureSpring.setValue(spring);
        this->addObject(spring);
    }
}

/// Override handleEvent to check for simulation step events.
void Suturing::handleEvent(core::objectmodel::Event* event)
{
    // If the event is an EndStepEvent (i.e. the simulation step has just finished)
    if (auto endStep = dynamic_cast<sofa::simulation::EndStepEvent*>(event))
    {
        // Call updateSuture with the time step (or dt) from the event.
        updateSuture(endStep->getDt());
    }
    // Call the base class event handler to propagate the event.
    BaseObject::handleEvent(event);
}

/// Update the spring parameters based on the picked suture points.
void Suturing::updateSuture(double /*dt*/)
{
    // Retrieve the performer.
    auto performer = d_suturePerformer.getValue();
    if (!performer)
    {
        return;
    }

    // --- Assumptions on SuturePointPerformer data fields ---
    // We assume the performer exposes:
    //   - d_pickedPositions: a vector of Vec3 positions (e.g. sofa::defaulttype::Vec3d)
    //   - d_pickedIndices: a vector of unsigned int indices corresponding to particles.
    //
    // We update the spring only if exactly two points have been picked.
    auto pickedPositions = performer->d_pickedPositions.getValue(); // type: std::vector<sofa::defaulttype::Vec3d>
    auto pickedIndices   = performer->d_pickedIndices.getValue();   // type: std::vector<unsigned int>

    if (pickedPositions.size() == 2 && pickedIndices.size() == 2)
    {
        // Compute the Euclidean distance between the two points (the desired rest length).
        sofa::defaulttype::Vec3d pos1 = pickedPositions[0];
        sofa::defaulttype::Vec3d pos2 = pickedPositions[1];
        double restLength = (pos2 - pos1).norm();

        // Retrieve the spring component.
        auto spring = d_sutureSpring.getValue();
        if (!spring)
        {
            return;
        }

        // Update the spring’s index lists.
        std::vector<unsigned int> indices1 = { pickedIndices[0] };
        std::vector<unsigned int> indices2 = { pickedIndices[1] };

        spring->d_springsIndices1.setValue(indices1);
        spring->d_springsIndices2.setValue(indices2);

        // Update the rest lengths (assuming d_lengths is a Data field of type vector<double>).
        std::vector<double> lengths = { restLength };
        spring->d_lengths.setValue(lengths);

        // Optionally, print debugging information.
        msg_info(this->getContext()->getMessageHandler(),
                 "Suturing updated: picked indices (%u, %u) with rest length %.3f",
                 pickedIndices[0], pickedIndices[1], restLength);
    }
}

int SuturingClass = core::RegisterObject("Custom suturing plugin combining SuturePointPerformer and SpringForceField")
    .add<Suturing>();

} // namespace suturing
} // namespace component
} // namespace sofa
