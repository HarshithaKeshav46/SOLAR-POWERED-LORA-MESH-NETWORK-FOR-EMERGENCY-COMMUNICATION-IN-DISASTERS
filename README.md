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

![WhatsApp Image 2025-11-29 at 9 07 14 PM](https://github.com/user-attachments/assets/a688b86c-3fb7-49c4-9a55-711523112720)

EFFICIENCY AND ACCURACY:
1) Message Delivery Ratio (MDR / PDR):
Expected (single-node loopback): 99.5% – 100%
Rationale: messages are local to node; missed messages mostly from app disconnects or 
GATT write failures.
Acceptable threshold: ≥ 95%
Excellent target: ≥ 99.9%


2) Packet Error Rate (PER):
Expected: 0% – 0.5% (PER = 100 − MDR)


3)End-to-End Latency (phone → ESP32 processed/displayed):BLE (GATT) typical 
mean: 20 ms – 120 ms . BLE heavy/load or Android background: 50 ms – 250 ms (p95)
WebSocket (local Wi-Fi AP) mean: 5 ms – 50 ms
Acceptable target (demo): mean < 200 ms, p95 < 400 ms
Excellent target: mean < 50 ms, p95 < 100 ms


4)Solar Charging Efficiency :Expected practical efficiency (panel → battery): 40% –75% overall
