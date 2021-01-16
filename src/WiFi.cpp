#include "LossnayController.h"
#include "Secrets.h"

void ScanAndConnect() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    int networks = WiFi.scanNetworks();

    logger.log("Found %d networks", networks);

    String strongestSSID = String("");
    int strongestSignalStrength = -1000;

    for (int i = 0; i < networks; i++) {
        int signalStrength = WiFi.RSSI(i);
        String ssid = WiFi.SSID(i);
        if (strongestSignalStrength < signalStrength) {
            for (unsigned int j = 0; j < sizeof(WIFI_SSIDs)/sizeof(WIFI_SSIDs[0]); j++) {
                if (ssid.equals(WIFI_SSIDs[j])) {
                    strongestSignalStrength = signalStrength;
                    strongestSSID = WiFi.SSID(i);
                }
            }
        }
    }

    if (strongestSSID.compareTo("") != 0) {
        logger.log("Connectiong to %s (%ddBm)", strongestSSID.c_str(), strongestSignalStrength);

        const char* hostname;
        
        if (strlen(settings.get()->hostname) > 1) {
            hostname = settings.get()->hostname;    
        } else {
            hostname = HOSTNAME;
        }
        logger.log("Hostname is %s", hostname);

        WiFi.hostname(hostname);
        WiFi.begin(strongestSSID.c_str(), WIFI_PASSWORD.c_str());

        // Timeout after 30 seconds of connection attempts.
        int timeout = 60; // 60 * 0.5 = 30 seconds. 
        while (WiFi.status() != WL_CONNECTED and timeout > 0) {
            timeout--;
            delay(100);
        }

        if (timeout > 0) {
            logger.log("Connected, ip address: %s", WiFi.localIP().toString().c_str());
        } else {
            logger.log("Failed to connect in 30 seconds. Please, check the password.");
        }
    } else {
        logger.log("No known network found...");
    }

    WiFi.scanDelete();
}