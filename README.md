# Voltage Analyzer

This repository hosts a terminal-based application built using `ncurses` that processes and analyzes voltage samples transmitted over Ethernet. The application reads real-time Ethernet packets from a microcontroller, parses the data, and then applies various analyses.

## Project Overview

The Voltage Analyzer is designed for real-time packet capturing and data analysis. It works by interfacing directly with the microcontroller over Ethernet, capturing voltage sample packets in real time, and displaying the data in a terminal-based UI.

The primary features of the project include:

1. **Real-Time Packet Reading**: Captures Ethernet packets directly from the microcontroller using raw socket programming.
2. **Data Analysis**: Processes and visualizes voltage data, with planned integration of advanced numerical methods using `std::numerics`.
3. **Interactive User Interface**: Utilizes `ncurses` for displaying graphs and data visualizations, allowing for an intuitive way to observe voltage behavior in real time.

### Key Features

- **Ethernet Packet Parsing**: Reads and parses voltage samples from real-time Ethernet packets without the need for external packet capture tools.
- **Data Analysis**: Converts packet data to voltage values and performs calculations such as average, maximum, and minimum readings.
- **Graphical Display**: Visualizes real-time data in a terminal-based UI using `ncurses`, with color-coded output for easier analysis.
- **Interactive Key Bindings**: Allows user interaction to capture new packets, reset data, or switch between views.
  
### Usage Instructions

1. **Install Dependencies**:

   Make sure you have the following libraries installed:

   ```bash
   sudo apt-get update
   sudo apt-get install libncurses5-dev libpcap-dev
   sudo apt-get install gdb-multiarch openocd stlink-tools
   ```

2. **Clone the Repository**:

   Clone the project using the following command:

   ```bash
   git clone https://github.com/stevemac321/voltage-analyzer.git
   cd voltage-analyzer
   ```

3. **Build the Application**:

   Use the provided Makefile to build the application. Make sure to have `ncurses` and `libpcap` installed on your system:

   ```bash
   make
   ```

   This will generate the `voltage_analyzer` binary in the build directory.

4. **Run the Application**:

   Execute the binary to start capturing packets and visualizing the data:

   ```bash
   ./voltage_analyzer
   ```

5. **View Analysis Results**:

   The terminal-based UI will display real-time voltage sample values, and any identified signal anomalies or trends.

### Planned Enhancements

- **Real-time Integration**: Continuous improvement of the real-time packet handling and Ethernet sniffing for more reliable data capture.
- **Threading for Performance**: Implement multi-threaded packet handling for better performance and smoother UI updates.
- **Advanced Signal Processing**: Integration of Fast Fourier Transform (FFT) and other numerical methods using `std::numerics` for frequency domain analysis.
- **Comprehensive Statistical Testing**: Implement chi-square and other statistical tests to validate signal properties and randomness.
- **Enhanced GUI Options**: Explore transitioning to a more advanced graphical toolkit (e.g., GTK or Qt) for enhanced visualization.

### Prerequisites

- Development Board: Nucleo-H723ZG or compatible STM32 microcontroller.
- Linux Environment: Developed on Ubuntu and FreeBSD but should work on most Linux distributions.
- `ncurses` Library: For terminal-based UI and visualization.
- `libpcap` Library: For capturing and parsing Ethernet packets.

### Folder Structure

```
├── src/                   # Source files for parsing, data processing, and visualization
├── include/               # Header files for classes and utility functions
├── build/                 # Directory for build artifacts
├── Makefile               # Makefile for building the project
└── README.md              # Project overview and instructions
```

### License

This project is licensed under the GPL version 2 (GPLv2).
