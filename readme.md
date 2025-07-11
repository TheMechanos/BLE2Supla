# BLE 2 Supla Gateway

This software turns an ESP32 into a BLE sensor-to-Supla gateway. The project uses [Theengs Decoder](https://github.com/theengs/decoder).  
\
It is possible to operate the device: [https://decoder.theengs.io/devices/devices.html](https://decoder.theengs.io/devices/devices.html)


## Supported Supla Devices

* Thermometer & Hygrometer
* Thermometer
* Hygrometer
* Open Sensor


## Installation
There are two target chips, ESP32-C3 and ESP32-S3 and two modes Normal and Debug(filename ending -DBG). Debug version is logging all data received from BLE, this will be useful to identify and add new devices 

### Web Installer

1. Download the file from the /dist directory.
2. Open https://espressif.github.io/esptool-js/
3. Connect to the ESP32 chip.
4. Select the downloaded file.
5. Set the Flash Address to 0x0000.
6. Click Program.
![Flashing Screen](https://github.com/TheMechanos/BLE2Supla/blob/main/img/Flashing.png?raw=true)
### PlatformIO

1. Clone the project: `git clone https://github.com/TheMechanos/BLE2Supla.git`
2. Build and upload using PlatformIO.



## Usage

Connect to the Wi-Fi network created by the device, named "BLE2SUPLA...".
Open a browser and go to 192.168.4.1. Configure your Wi-Fi network and Supla Cloud account credentials.
Select how many devices the gateway should handle, enter their BLE addresses, and choose which sensor types should be generated in Supla.
Save the configuration and test the setup. 😊

![Configuration Screen](https://github.com/TheMechanos/BLE2Supla/blob/main/img/Config.png?raw=true)


## Changelog

### V1.0.1
-Add debug mode to list all decoded BLE Devices to log