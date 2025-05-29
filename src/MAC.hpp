#pragma once

#include <Arduino.h>

class MAC {
public:
    static bool isValid(String mac, bool allowWildcard = true) {
        if (mac.length() != 17)
            return false; // długość MAC musi wynosić 17

        if (!allowWildcard && hasWildcard(mac))
            return false;

        for (int i = 0; i < mac.length(); i++) {
            if ((i + 1) % 3 == 0) {
                if (mac.charAt(i) != ':')
                    return false;
            } else {
                char c = mac.charAt(i);
                if (!isHexCharacter(c) && c != '?')
                    return false;
            }
        }
        return true;
    }

    static bool compare(String mac, String pattern) {
        if (mac.length() != pattern.length())
            return false;

        for (unsigned int i = 0; i < mac.length(); i++) {
            if (pattern[i] == '?')
                continue;

            if (mac[i] != pattern[i])
                return false;
        }

        return true;
    }



private:
    static bool hasWildcard(String mac) { return mac.indexOf('?') != -1; }
    static bool isHexCharacter(char c) { return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'); }
};