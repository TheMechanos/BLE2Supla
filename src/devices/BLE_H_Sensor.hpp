#pragma once

#include <functional>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <supla/sensor/hygro_meter.h>

#include "BLE_Sensor.hpp"


class BLE_H_Sensor : public BLE_Sensor, public Supla::Sensor::HygroMeter {
public:
    BLE_H_Sensor(String mac, BleScanner* scanner, uint32_t validTimeMs)
        : BLE_Sensor(BLE_Sensor::Type::Humidity, mac, scanner, validTimeMs, &channel)
        , humi(HUMIDITY_NOT_AVAILABLE) { }


private:
    virtual void onData(String MAC, JsonObject data) {

        if (data["hum"].is<double>())
            humi = data["hum"].as<double>();
        else
            humi = HUMIDITY_NOT_AVAILABLE;

        printf("TH SENSOR '%s' -> %0.0f%%\n", MAC.c_str(), humi);

        sendNewValue();
    }

    virtual void onInvalidTime() {
        humi = HUMIDITY_NOT_AVAILABLE;
        sendNewValue();
    }


    void onInit() override { init(); }
    void iterateAlways() override { iterate(); }

    void sendNewValue() { channel.setNewValue(humi); }


    double humi;
};