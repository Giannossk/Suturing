# Suturing Plugin for SOFA Framework

The **Suturing** plugin is a custom SOFA component that enables you to simulate suturing in soft tissue simulation. It combines the functionality of the built-in [SuturePointPerformer](https://www.sofa-framework.org/community/forum/topic/working-example-on-simple-suturing-with-suturepointperformer/) (to pick suture points via mouse interaction) with a [SpringForceField](https://sofa-framework.github.io/doc/components/solidmechanics/spring/springforcefield/) (to simulate the connection between tissue points using spring dynamics).

## Features

- **Point Selection:** Uses the SuturePointPerformer component to let users select two suture points on tissue objects.
- **Dynamic Suturing:** Automatically creates and updates a spring (via SpringForceField) between the picked points.
- **Event-Driven Update:** Listens for simulation step events (EndStepEvent) to refresh the suture connection based on the latest picked positions.
- **Modular Design:** Easily integrates into your existing SOFA scenes and can be configured via scene files.

## Requirements

- **SOFA Framework:** Compatible with SOFA (v19.12 and later recommended).
- **Required Plugins:**  
  - Sofa.Component.UserInteraction  
  - Sofa.Component.SolidMechanics.Spring  
- **Build Tools:** CMake (version 3.10 or higher recommended) and a C++ compiler supporting C++11.

## Installation and Build Instructions

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/yourusername/SuturingPlugin.git
   cd SuturingPlugin
