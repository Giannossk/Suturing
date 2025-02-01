# Suturing Plugin for SOFA Framework

The **Suturing** plugin dynamically simulates suturing (or tearing) of soft tissue by automatically selecting two candidate points from a tissue MechanicalObject and connecting them using a SpringForceField. This implementation does not rely on manual mouse interaction; instead, it computes candidate points based on a predefined criterion (in this example, the points with the minimum and maximum x-coordinates).

## Code Documentation

The source code is documented using Doxygen-style comments:

- **Suturing.h**  
  - Declares the `Suturing` class.
  - Describes data members:
    - `d_tissueObject`: Reference to a tissue MechanicalObject providing particle positions.
    - `d_sutureSpring`: SpringForceField used to connect the two selected points.
    - `d_autoSuture`: Boolean flag to enable dynamic selection.
  - Documents each public method (`init()`, `handleEvent()`) and the protected method (`updateSuture()`).

- **Suturing.cpp**  
  - Implements the initialization, event handling, and dynamic update logic.
  - In `updateSuture()`, the tissue's particle positions are scanned and the points with the extreme x-values are selected.
  - The SpringForceField is updated with the computed indices and rest length.

## Features

- **Dynamic Point Selection:** Automatically selects two suture points without relying on mouse input.
- **Automatic Spring Update:** Continuously updates the suture connection based on the current state of the tissue.
- **Modular Design:** Easily extended or modified by adjusting the dynamic selection criteria.

## Requirements

- SOFA Framework (v19.12 or later recommended)
- Required SOFA plugins:
  - `Sofa.Component.UserInteraction`
  - `Sofa.Component.SolidMechanics.Spring`
- CMake (3.10+), C++ compiler with C++11 support

## Build Instructions

1. **Clone the repository:**

   ```bash
   git clone https://github.com/Giannossk/Suturing.git
   cd SuturingPlugin
