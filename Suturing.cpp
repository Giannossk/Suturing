#include "Suturing.h"
#include <sofa/core/ObjectFactory.h>
#include <sofa/simulation/EndStepEvent.h>
#include <cmath>

namespace sofa {
namespace component {
namespace suturing {

Suturing::Suturing()
    : d_tissueObject(initData(&d_tissueObject,
          core::objectmodel::SPtr< component::statecontainer::MechanicalObject<defaulttype::Vec3d> >(),
          "tissueObject",
          "Tissue MechanicalObject providing particle positions"))
    , d_sutureSpring(initData(&d_sutureSpring,
          core::objectmodel::SPtr< solidmechanics::spring::SpringForceField >(),
          "sutureSpring",
          "SpringForceField connecting the sutured points"))
    , d_autoSuture(initData(&d_autoSuture, true, "autoSuture",
          "If true, selects suture points dynamically"))
{
}

Suturing::~Suturing() {}

void Suturing::init()
{
    if (!d_tissueObject.getValue())
    {
        msg_error(this->getContext()->getMessageHandler(),
                  "No tissue MechanicalObject provided in d_tissueObject.");
        return;
    }
    if (!d_sutureSpring.getValue())
    {
        auto spring = core::objectmodel::New< solidmechanics::spring::SpringForceField >();
        spring->d_stiffness.setValue(200.0);
        spring->d_damping.setValue(5.0);
        d_sutureSpring.setValue(spring);
        this->addObject(spring);
    }
}

void Suturing::handleEvent(core::objectmodel::Event* event)
{
    if (auto endStep = dynamic_cast<sofa::simulation::EndStepEvent*>(event))
        updateSuture(endStep->getDt());
    BaseObject::handleEvent(event);
}

void Suturing::updateSuture(double /*dt*/)
{
    if (!d_autoSuture.getValue())
        return;

    auto tissue = d_tissueObject.getValue();
    if (!tissue)
        return;

    const auto& positions = tissue->d_position.getValue();
    if (positions.empty())
        return;

    // Select candidate points based on extreme x-coordinates.
    size_t minIndex = 0, maxIndex = 0;
    double minX = positions[0][0], maxX = positions[0][0];

    for (size_t i = 1; i < positions.size(); ++i)
    {
        double x = positions[i][0];
        if (x < minX) { minX = x; minIndex = i; }
        if (x > maxX) { maxX = x; maxIndex = i; }
    }
    if (minIndex == maxIndex)
        return;

    const auto& pos1 = positions[minIndex];
    const auto& pos2 = positions[maxIndex];
    double restLength = (pos2 - pos1).norm();

    auto spring = d_sutureSpring.getValue();
    if (!spring)
        return;

    std::vector<unsigned int> indices1 = { static_cast<unsigned int>(minIndex) };
    std::vector<unsigned int> indices2 = { static_cast<unsigned int>(maxIndex) };
    spring->d_springsIndices1.setValue(indices1);
    spring->d_springsIndices2.setValue(indices2);

    std::vector<double> lengths = { restLength };
    spring->d_lengths.setValue(lengths);

    msg_info(this->getContext()->getMessageHandler(),
             "Dynamic suturing: indices (%u, %u), rest length %.3f",
             static_cast<unsigned int>(minIndex),
             static_cast<unsigned int>(maxIndex),
             restLength);
}

int SuturingClass = core::RegisterObject("Dynamic suturing plugin")
    .add<Suturing>();

} // namespace suturing
} // namespace component
} // namespace sofa
