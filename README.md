# Voltage Analyzer

This repository hosts a terminal-based application built using `ncurses` that processes and analyzes voltage samples transmitted over Ethernet. The application captures real-time Ethernet packets from a microcontroller, parses the data, and performs various analyses, including signal processing techniques such as Fast Fourier Transform (FFT) and statistical analysis.

## Project Overview

The Voltage Analyzer interfaces directly with a microcontroller over Ethernet, capturing voltage sample packets in real time and displaying the data in a terminal-based UI. It demonstrates advanced networking and numerical analysis techniques on real-time data.

### Key Features

- **Real-Time Packet Capture**: Uses `libpcap` and raw socket programming to capture Ethernet packets from the microcontroller.
- **Data Transformation and Analysis**:
  - Converts raw ADC values to real voltages using the formula:
    \[
    V_{\text{real}} = \frac{ADC_{\text{value}} \times V_{\text{reference}}}{2^{\text{Resolution}}}
    \]
    where:
    - `ADC_value` is the raw value obtained from the ADC.
    - `V_reference` is the reference voltage (e.g., 3.3V).
    - `Resolution` is the ADC resolution (e.g., 12 bits).
  - Computes the magnitude of complex numbers from FFT analysis using:
    \[
    \text{Magnitude} = \sqrt{(\text{real}^2 + \text{imag}^2)}
    \]
- **Graphical Display**: Visualizes real-time voltage data, FFT results, and matrix operations using `ncurses`.
- **Matrix Operations**:
  - Performs matrix addition, subtraction, and multiplication on captured packet data.
  - The results are displayed in the terminal along with execution times.
  - **New Feature**: Each matrix operation is validated against expected results, and the validation status (pass or fail) is displayed. Validation logs are saved to a file `matrix_validation.txt` after each run.
  
- **Interactive Key Bindings**:
  - **Press '1'**: Captures packets and provides a voltage view.
  - **Press '2'**: Displays matrix multiplication results, with validation status.
  
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

   Use the provided Makefile to build the application. Make sure `ncurses` and `libpcap` are installed:

   ```bash
   make
   ```

4. **Run the Application**:

   Run the application with `sudo` to ensure it has the necessary permissions for capturing packets:

   ```bash
   sudo ./remote_monitor
   ```

5. **View Analysis Results**:

   The terminal-based UI displays real-time voltage sample values and matrix operations (addition, subtraction, multiplication). Each operation is validated, and the results are shown in the interface.

   - Validation logs can be found in `matrix_validation.txt` after each run, which records the comparison between the computed results and the expected results.

### Prerequisites

- **Hardware**: Nucleo-H723ZG or compatible STM32 microcontroller.
- **Environment**: Developed on Ubuntu but should work on most Linux distributions.
- **Libraries**: `ncurses` for terminal-based UI and `libpcap` for Ethernet packet capture.

### Folder Structure

```
├── src/                   # Source files for parsing, data processing, and visualization
├── include/               # Header files for classes and utility functions
├── build/                 # Directory for build artifacts
├── matrix_validation.txt  # Log file containing matrix validation results
├── Makefile               # Makefile for building the project
└── README.md              # Project overview and instructions
```

### License

This project is licensed under the GPL version 2 (GPLv2).
