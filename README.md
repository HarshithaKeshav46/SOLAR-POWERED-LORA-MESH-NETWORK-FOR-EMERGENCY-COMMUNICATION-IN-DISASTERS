# SOLAR-POWERED-LORA-MESH-NETWORK-FOR-EMERGENCY-COMMUNICATION-IN-DISASTERS
📌Open Source Project

Project hardware: 

▫️Solar panel — HST06003

Key specs: Open-circuit voltage (Voc) 10.8 V, Maximum power-point voltage (Vm) 8.5 V, Short-circuit current (Isc) 0.38 A.

Role: Primary energy harvester for daytime operation and battery charging.

▫️Li-ion charge controller — TP4056 module

Key function: Linear charger IC for single-cell lithium-ion batteries, accepts 5 V input (USB), adjustable charge current (commonly up to 1 A on modules).

Role: Manages charging from the solar-powered 5 V supply/USB input and implements safe charge termination.

▫️LoRa microcontroller board — TTGO LoRa32 (5 V)

Key features: ESP32 microcontroller integrated with Semtech LoRa transceiver, USB 5 V input, Wi-Fi/Bluetooth + long-range LoRa communication.

Role: Runs sensors, power management logic, and transmits data over LoRaWAN or custom LoRa links with very low-power sleep modes.

▫️Energy storage — Single-cell Lithium-ion battery

Role: Stores energy for night-time and low-sun periods, provides a stable supply to the TTGO board and peripherals.


BLOCK DIAGRAM:

![WhatsApp Image 2025-11-08 at 8 32 46 PM](https://github.com/user-attachments/assets/b3261ae5-af09-4979-9bc5-5cb2cd96a9e5)




