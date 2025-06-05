#pragma once

#include <supla/network/web_sender.h>
#include <supla/storage/config.h>

#include <devices/BLE_H_Sensor.hpp>
#include <devices/BLE_Sensor.hpp>
#include <devices/BLE_TH_Sensor.hpp>
#include <devices/BLE_T_Sensor.hpp>
#include <devices/BLE_Open_Sensor.hpp>

class BLE_Sensor_Factory {
public:
    static BLE_Sensor* CreateSensor(BLE_Sensor::Type type, String mac, BleScanner* scanner, uint32_t validTimeMs) {

        switch (type) {
        case BLE_Sensor::Type::TermoAndHum:
            return new BLE_TH_Sensor(mac, scanner, validTimeMs);

        case BLE_Sensor::Type::Thermo:
            return new BLE_T_Sensor(mac, scanner, validTimeMs);

        case BLE_Sensor::Type::Humidity:
            return new BLE_H_Sensor(mac, scanner, validTimeMs);

        case BLE_Sensor::Type::Open:
            return new BLE_Open_Sensor(mac, scanner, validTimeMs);
        }

        return nullptr;
    }

    static void SendFunctionCheckbox(Supla::WebSender* sender, uint8_t devNum, BLE_Sensor::Type type) {
        auto cfg = Supla::Storage::ConfigInstance();

        char tag[32];
        snprintf(tag, 32, "%s%u", BLE_Sensor::TYPE_CODES[type], devNum);

        uint8_t checkedVal = 0;
        cfg->getUInt8(tag, &checkedVal);

        sender->send("<div class=\"form-field right-checkbox\">");
        sender->sendLabelFor(tag, BLE_Sensor::TYPE_LABEL[(uint8_t)type]);
        sender->send("<label>");
        sender->send("<span class=\"switch\">");

        sender->send("<input type=\"hidden\" name=\"");
        sender->send(tag);
        sender->send("\" ");
        sender->send("value=\"");
        sender->send(checkedVal ? "on" : "off");
        sender->send("\">");

        sender->send("<input type=\"checkbox\" value=\"on\" id=\"");
        sender->send(tag);
        sender->send("\" ");
        sender->send(checkedVal ? " checked" : "");
        sender->send(" onchange=\"document.getElementsByName('");
        sender->send(tag);
        sender->send("')[0].value = this.checked ? 'on' : 'off'\"");
        sender->send(">");

        sender->send("<span class=\"slider\"></span>");

        sender->send("</span>");
        sender->send("</label>");
        sender->send("</div>");
    }

    static bool HandleResponse(uint8_t devNum, BLE_Sensor::Type type, const char* key, const char* value) {
        auto cfg = Supla::Storage::ConfigInstance();

        char tag[32];
        snprintf(tag, 32, "%s%u", BLE_Sensor::TYPE_CODES[type], devNum);

        if (strcmp(key, tag) == 0) {
            if (strcmp(value, "on") == 0)
                cfg->setUInt8(tag, 1);
            else if (strcmp(value, "off") == 0)
                cfg->setUInt8(tag, 0);
            return true;
        }
        return false;
    }

    static bool IsType(uint8_t devNum, BLE_Sensor::Type type) {
        auto cfg = Supla::Storage::ConfigInstance();

        char tag[32];
        snprintf(tag, 32, "%s%u", BLE_Sensor::TYPE_CODES[type], devNum);

        uint8_t checkedVal = 0;
        cfg->getUInt8(tag, &checkedVal);
        return checkedVal;
    }
};
