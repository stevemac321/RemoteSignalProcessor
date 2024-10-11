# Voltage Analyzer

This repository hosts a terminal-based application built using `ncurses` that processes and analyzes voltage samples transmitted over Ethernet. The application reads real-time Ethernet packets from a microcontroller, parses the data, and then applies various analyses, including signal processing techniques such as Fast Fourier Transform (FFT) and statistical analysis.

## Project Overview

The Voltage Analyzer is designed for real-time packet capturing and data analysis. It interfaces directly with a microcontroller over Ethernet, capturing voltage sample packets in real time and displaying the data in a terminal-based UI. The project serves as a demonstration of advanced networking and numerical analysis techniques on real-time data.

The primary features of the project include:

1. **Real-Time Packet Reading**: Captures Ethernet packets directly from the microcontroller using raw socket programming and the `libpcap` library.
2. **Data Analysis**: Converts packet data to voltage values and performs calculations such as average, maximum, minimum, and Fast Fourier Transform (FFT).
3. **Interactive User Interface**: Utilizes `ncurses` for displaying graphs and data visualizations, providing an intuitive way to observe voltage behavior in real time.
4. **Graph-Based Analysis**: Constructs a graph from FFT results and uses graph algorithms to identify peaks and valleys in the voltage signal.

### Key Features

- **Ethernet Packet Parsing**: Reads and parses voltage samples from real-time Ethernet packets without the need for external packet capture tools like Wireshark.
- **Data Analysis and Transformation**: 
  - Converts raw ADC data to voltage using a specific formula:
    - **Voltage Calculation Formula**:
      \[
      V_{\text{real}} = \frac{ADC_{\text{value}} \times V_{\text{reference}}}{2^{\text{Resolution}}}
      \]
      where:
      - `ADC_value` is the raw value obtained from the ADC.
      - `V_reference` is the reference voltage (e.g., 3.3V).
      - `Resolution` is the ADC resolution (e.g., 12 bits).

  - Calculates the magnitude of a complex number (used in FFT analysis) with the formula:
    \[
    \text{Magnitude} = \sqrt{(\text{real}^2 + \text{imag}^2)}
    \]

- **Graphical Display**: Visualizes real-time data in a terminal-based UI using `ncurses`, with color-coded output for easier analysis.
- **Priority Queue and Graph Analysis**: Uses a priority queue to sort magnitudes and constructs an adjacency matrix to represent relationships between signal peaks and valleys.

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

   The terminal-based UI will display real-time voltage sample values, FFT results, and any identified signal anomalies or trends.

### Voltage and FFT Analysis

The application captures raw ADC values from the microcontroller. These values are then converted to real voltage values using the voltage calculation formula. The voltage values are used to compute FFT and obtain the magnitude of the frequency components.

#### Converting ADC Values to Voltage

Given the ADC raw value `ADC_value`, reference voltage `V_reference`, and ADC resolution `Resolution`, the real voltage can be calculated using the following formula:

\[
V_{\text{real}} = \frac{ADC_{\text{value}} \times V_{\text{reference}}}{2^{\text{Resolution}}}
\]

For example, with `ADC_value = 2048`, `V_reference = 3.3V`, and `Resolution = 12`:

\[
V_{\text{real}} = \frac{2048 \times 3.3}{2^{12}} = \frac{2048 \times 3.3}{4096} = 1.65V
\]

#### Magnitude Calculation in FFT

Each FFT result is a complex number represented as `real` and `imaginary` parts. The magnitude of the complex number is calculated as:

\[
\text{Magnitude} = \sqrt{(\text{real}^2 + \text{imag}^2)}
\]

The magnitudes are stored in a priority queue and used to identify peaks and valleys in the frequency domain.

### Planned Enhancements

- **Real-time Integration**: Continuous improvement of the real-time packet handling and Ethernet sniffing for more reliable data capture.
- **Threading for Performance**: Implement multi-threaded packet handling for better performance and smoother UI updates.
- **Advanced Signal Processing**: Integration of additional signal processing algorithms such as filtering, windowing functions, and spectral analysis.
- **Enhanced GUI Options**: Explore transitioning to a more advanced graphical toolkit (e.g., GTK or Qt) for enhanced visualization.
- **Comprehensive Graph-Based Analysis**: Leverage the graph structure to identify more complex relationships and patterns in the data.

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
