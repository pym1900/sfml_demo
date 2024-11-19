# SFML Cloth Simulation

This project is a cloth simulation using **SFML (Simple and Fast Multimedia Library)** for rendering. It demonstrates the application of physics-based constraints and particle systems.

## Features

- Real-time interaction with mouse input
- Configurable grid size and physics parameters

## Prerequisites

- A C++ compiler that supports C++17 or higher
- CMake version 3.10 or above
- SFML library version 2.5 or higher

## Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/pym1900/sfml_demo.git
cd sfml_demo
```

### 2. Install Dependencies

Ensure **SFML** is installed on your system. You can install it via package managers or build it from source.

#### On Ubuntu

```bash
sudo apt update
sudo apt install libsfml-dev
```

#### On macOS (using Homebrew)

```bash
brew install sfml
```

#### On Windows

1. Download SFML from [SFML official website](https://www.sfml-dev.org/).
2. Follow the installation instructions for your compiler.

### 3. Build the Project

#### Step 1: Create a Build Directory

```bash
mkdir build
cd build
```

#### Step 2: Configure with CMake

```bash
cmake ..
```

#### Step 3: Compile the Project

```bash
make
```

### 4. Run the Simulation

After building, you can run the simulation:

```bash
./SFML_SIMULATION
```

## Project Structure

```
SFML_SIMULATION/
├── CMakeLists.txt       # CMake build configuration
├── include/             # Header files
│   ├── constraint.hpp   # Constraint system
│   ├── input_handler.hpp# Input handling for mouse events
│   └── particle.hpp     # Particle system
├── src/                 # Source files
│   ├── main.cpp         # Main simulation logic
└── README.md            # Project documentation
```

## Configurations
