# Voltage Analyzer
(pair this client-host native Linux application with the EmbeddedEthernet project: https://github.com/stevemac321/EmbeddedEthernet).
This repository hosts a terminal-based application built using `ncurses` that processes and analyzes voltage samples transmitted over Ethernet. The application captures real-time Ethernet packets from a microcontroller, parses the data, and performs various analyses, including signal processing techniques such as Fast Fourier Transform (FFT), matrix operations, and statistical analysis.

## Project Overview

The Voltage Analyzer interfaces directly with a microcontroller over Ethernet, capturing voltage sample packets in real time and displaying the data in a terminal-based UI. It demonstrates advanced networking, numerical analysis techniques, and matrix operations on real-time data.

### Key Features

- **Real-Time Packet Capture**: Uses `libpcap` and raw socket programming to capture Ethernet packets from the microcontroller.
  
- **Data Transformation and Analysis**:
  - Converts raw ADC values to real voltages using the formula:

    ```
    V_real = (ADC_value * V_reference) / 2^Resolution
    ```
    
    where:
    - `ADC_value` is the raw value obtained from the ADC.
    - `V_reference` is the reference voltage (e.g., 3.3V).
    - `Resolution` is the ADC resolution (e.g., 12 bits).
    
  - Computes the magnitude of complex numbers from FFT analysis using:

    ```
    Magnitude = sqrt(real^2 + imag^2)
    ```
    
- **Graphical Display**: Visualizes real-time voltage data, FFT results, and matrix operations using `ncurses`.

- **Matrix Operations**:
  - Performs matrix addition, subtraction, and multiplication on captured packet data.
  - The results are displayed in the terminal along with execution times.
  - **New Feature**: Logs matrix validation results to `matrix_validation.txt` after each run.

- **Polynomial Multiplication**:
  - Uses FFT results (`save_fft`) to perform polynomial multiplication in the frequency domain.
  - Efficiently computes the product of two polynomials in O(n log n) time using FFT.

- **Fourier Series Approximation**:
  - Approximates the signal using Fourier series based on FFT data.
  - The Fourier series approximation reconstructs the signal as a sum of sinusoidal harmonics.

- **Interactive Key Bindings**:
  - **Press '1'**: Captures packets and provides a voltage view.
  - **Press '2'**: Displays matrix operations (addition, subtraction, multiplication), with validation status.
  - **Press '3'**: Access the "More Math" feature, including Fourier series approximation and polynomial multiplication.

### Usage Instructions

1. **Install Dependencies**:

   Make sure you have the following libraries installed:

   ```bash
   sudo apt-get update
   sudo apt-get install libncurses5-dev libpcap-dev
   sudo apt-get install libpcap-dev

Clone the Repository:

Clone the project using the following command:

bash
Copy code
git clone https://github.com/stevemac321/voltage-analyzer.git
cd voltage-analyzer
Build the Application:

Use the provided Makefile to build the application. Make sure ncurses and libpcap are installed:

bash
Copy code
make
Run the Application:

Run the application with sudo to ensure it has the necessary permissions for capturing packets:

bash
Copy code
sudo ./remote_monitor
View Analysis Results:

The terminal-based UI displays real-time voltage sample values and matrix operations (addition, subtraction, multiplication). Each operation is validated, and the results are shown in the interface.

Validation logs can be found in matrix_validation.txt after each run, which records the comparison between the computed results and the expected results.

The Fourier series approximation and polynomial multiplication results can be viewed by pressing 3 for "More Math".

Prerequisites
Hardware: Nucleo-H723ZG or compatible STM32 microcontroller.
Environment: Developed on Ubuntu but should work on most Linux distributions.
Libraries: ncurses for terminal-based UI and libpcap for Ethernet packet capture.
Folder Structure
makefile
Copy code
├── src/                   # Source files for parsing, data processing, and visualization
├── include/               # Header files for classes and utility functions
├── build/                 # Directory for build artifacts
├── matrix_validation.txt  # Log file containing matrix validation results
├── Makefile               # Makefile for building the project
└── README.md              # Project overview and instructions
License
This project is licensed under the GPL version 2 (GPLv2).
