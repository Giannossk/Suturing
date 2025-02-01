# Suturing Plugin for SOFA Framework

The **Suturing** plugin is a dynamic SOFA component that simulates suturing (or tearing) of soft tissues by automatically selecting two candidate points from a tissue MechanicalObject and connecting them with a SpringForceField.

## Features

- **Dynamic Point Selection:** Automatically selects two suture points based on a chosen criterion (currently extreme x‑coordinates).
- **Automatic Spring Update:** Updates the SpringForceField every simulation step to reflect the current state.
- **No Mouse Interaction:** Designed to work without relying on manual mouse picking.
- **Modular and Extendable:** Developers can easily modify the point-selection criteria or spring parameters.

## Requirements

- SOFA Framework (v19.12 or later recommended)
- Required SOFA plugins: Sofa.Component.UserInteraction, Sofa.Component.SolidMechanics.Spring
- CMake (3.10+), C++ compiler with C++11 support

## Build Instructions

1. **Clone the repository:**

   ```bash
   git clone https://github.com/yourusername/SuturingPlugin.git
   cd SuturingPlugin
