
# Voltage Analyzer

This repository hosts a terminal-based application built using `ncurses` that processes and analyzes voltage samples transmitted over Ethernet. The application is designed to work in conjunction with another embedded Ethernet project, which collects voltage samples from a microcontroller and transmits them as Ethernet packets.

## Project Overview

The `Voltage Analyzer` application is not designed for real-time monitoring. Instead, it works by importing pre-captured Ethernet packets using Wireshark, processing the voltage samples, and then applying various analyses such as:

- **Fast Fourier Transform (FFT)**: For frequency domain analysis.
- **Magnitude Calculations**: To find peak values and visualize the signal.
- **Statistical Testing**: Including chi-square tests to verify randomness or uniformity of signal values.
- **Graphing and Visualization**: Utilizing `ncurses` for displaying graphs and other data visualizations in the terminal.

This project is ideal for offline data processing and analysis, making it a great tool for detailed inspection of voltage behavior from the microcontroller.

## Features

- **Ethernet Packet Parsing**: Reads voltage sample packets captured in Wireshark.
TODO - import the following from CMSIS/DSP Project
- ** - Replace Wireshark capture with real-time socket app
- **Data Analysis**: Includes FFT, magnitude calculations, and potentially other numerical methods using `std::numerics`.
- **Graphical Display**: Visualizes data and results in a terminal-based UI using `ncurses`.
- **Statistical Testing**: Plan to include chi-square tests and other statistical metrics to verify signal quality and randomness.

## Usage

### 1. **Capture Ethernet Packets with Wireshark**:  
   Use Wireshark to capture packets sent from the microcontroller. Export the packets as C arrays for integration with this application.
   
### 2. **Compile the Application**:  
   Use the provided `Makefile` to build the application. Make sure `ncurses` is installed on your system:
   ```bash
   make
   ```
   
   This will generate the `voltage_analyzer` binary in the build directory.

### 3. **Run the Application**:  
   Execute the binary and provide the C array data as input:
   ```bash
   ./voltage_analyzer
   ```
   
### 4. **View Analysis Results**:  
   The terminal-based UI will display the voltage sample values, any identified signal peaks, FFT results, and other relevant metrics.

## Planned Enhancements

- **Real-time Integration**: Adding real-time processing capabilities using Ethernet sniffing libraries.
- **Graphical User Interface**: Transitioning from `ncurses` to a more advanced graphical toolkit (e.g., GTK or Qt).
- **Advanced Statistical Testing**: Including more statistical tests to validate signal properties.
- **Extended Signal Processing**: Implementing additional signal processing techniques like windowing functions, filtering, and spectral analysis.

## Prerequisites  (I developed this with clang++ on FreeBSD, but it should work on Linux too).

- **Development Board**: Nucleo-H723ZG or compatible STM32 microcontroller.
- **Wireshark**: To capture and export Ethernet packets.
- **NCurses**: Terminal-based UI library for graphing and visualization.
- **C++ Standard Library**: For numerical analysis and data handling.

## Folder Structure

```
├── src/                   # Source files for parsing, data processing, and visualization
├── include/               # Header files for classes and utility functions
├── data/                  # Sample data files (e.g., C arrays exported from Wireshark)
├── Makefile               # Makefile for building the project
├── build/                 # Directory for build artifacts
└── README.md              # This readme file with project overview and instructions
```

## License

This project is licensed under the GPL 2

