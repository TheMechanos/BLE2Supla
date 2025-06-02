#include <main.hpp>


void setup() {
    Serial.begin(115200);
    Serial.println("Scanning...");

    NimBLEDevice::setScanFilterMode(CONFIG_BTDM_SCAN_DUPL_TYPE_DEVICE);
    NimBLEDevice::setScanDuplicateCacheSize(200);
    NimBLEDevice::init(DEVICE_NAME);

    scanner.init();

    scanner.addSensor("A4:C1:38:??:??:??", [](String MAC, JsonObject data){
        serializeJson(data, Serial);
        Serial.println("");
    });
}


void loop() {
    scanner.iterate();
    delay(100);
}