# BLE 2 Supla Gateway

This software turns an ESP32 into a BLE sensor-to-Supla gateway. The project uses [Theengs Decoder](https://github.com/theengs/decoder).  
Supported devices list: [https://decoder.theengs.io/devices/devices.html](https://decoder.theengs.io/devices/devices.html)

## Installation

### Web Installer

1. Download the file from the /dist directory.
2. Open https://espressif.github.io/esptool-js/
3. Connect to the ESP32 chip.
4. Select the downloaded file.
5. Set the Flash Address to 0x1000.
6. Click Program.

### PlatformIO

1. Clone the project: `git clone https://github.com/TheMechanos/BLE2Supla.git`
2. Build and upload using PlatformIO.

## Usage

Connect to the Wi-Fi network created by the device, named "BLE2SUPLA...".
Open a browser and go to 192.168.4.1. Configure your Wi-Fi network and Supla Cloud account credentials.
Select how many devices the gateway should handle, enter their BLE addresses, and choose which sensor types should be generated in Supla.
Save the configuration and test the setup. 😊
