# Automatic-Entry-Exit-Control-System-With-Vacant-Slot-Display
This is a system that counts people or vehicles entering and exiting a space and displaying the number of available slots in real time
# Display Module — SPI Screen

## Feature Description
This branch implements the SPI display module for the Automatic Entry/Exit Control System.
It handles real-time rendering of occupancy data on the screen.

## What It Shows
- Total Capacity
- Occupied Slots
- Vacant Slots

## Hardware
- ESP32 microcontroller
- SPI-connected display

## How It Works
1. Display initializes on system boot
2. Receives occupancy data from the main counter logic
3. Refreshes screen whenever values change
