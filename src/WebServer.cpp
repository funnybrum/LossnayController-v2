#include "LossnayController.h"

WebServer::WebServer(int port) {

    _server = new ESP8266WebServer(port);
    _server->on("/", std::bind(&WebServer::handle_root, this));
    _server->on("/get", std::bind(&WebServer::handle_get, this));
    _server->on("/settings", std::bind(&WebServer::handle_settings, this));
    _server->on("/reset", std::bind(&WebServer::handle_reset, this));
    _server->on("/hard-reset", std::bind(&WebServer::handle_hard_reset, this));
    _server->on("/logs", std::bind(&WebServer::handle_logs, this));
    _server->on("/on", std::bind(&WebServer::handle_on, this));
    _server->on("/off", std::bind(&WebServer::handle_off, this));
    _server->on("/fan", std::bind(&WebServer::handle_fan, this));

    _httpUpdater = new ESP8266HTTPUpdateServer(true);
    _httpUpdater->setup(_server);

    MDNS.begin(HOSTNAME);
    MDNS.addService("http", "tcp", 80);

}

void WebServer::begin() {
    _server->begin();
}

void WebServer::loop() {
    _server->handleClient();
}

void WebServer::handle_root() {
    systemCheck.registerWebCall();
    _server->sendHeader("Location","/settings");
    _server->send(303);
}

void WebServer::handle_get() {
    systemCheck.registerWebCall();

    char resp[strlen_P(GET_JSON) + 32];
    sprintf_P(resp,
              GET_JSON);
    _server->send(200, "application/json", resp);
}

void WebServer::handle_settings() {
    logger.log("/settings");
    systemCheck.registerWebCall();

    bool save = false;

    if (_server->hasArg("hostname")) {
        String new_hostname = _server->arg("hostname");
        unsigned int max_hostname_length = sizeof(settings.get()->hostname) - 1;
        if (new_hostname.length() > 2 && new_hostname.length() < max_hostname_length) {
            bool valid = true;
            for (unsigned int i = 0; i < new_hostname.length(); i++) {
                char ch = new_hostname.charAt(i);
                if (!isalnum(ch) && ch != '-') {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                strcpy(settings.get()->hostname, new_hostname.c_str());
                save = true;
            }
        }
    }

    if (save) {
        logger.log("Settings updated.");
        settings.save();
    }

    char resp[strlen_P(CONFIG_PAGE) + 128];
    sprintf_P(
        resp,
        CONFIG_PAGE,
        settings.get()->hostname);
    _server->send(200, "text/html", resp);
}

void WebServer::handle_reset() {
    logger.log("/reset");
    systemCheck.registerWebCall();
    _server->send(200);
    delay(1000);
    ESP.reset();
}

void WebServer::handle_hard_reset() {
    logger.log("/hard_reset");
    systemCheck.registerWebCall();
    settings.erase();
    _server->send(200, "text/plain", "Settings erased.");
}

void WebServer::handle_logs() {
    systemCheck.registerWebCall();
    _server->send(200, "text/html", logger.getLogs());
}

void WebServer::handle_fan() {
    logger.log("/fan");
    systemCheck.registerWebCall();

    if (_server->hasArg("speed")) {
        int val = _server->arg("speed").toInt();
        if (0 <= val && val <= 4) {
            logger.log("Setting fan speed to %d", val);
            lossnay.fan_speed(val);
            _server->send(200);
            return;
        }
    }

    _server->send(404, "text/plain", "Pass in speed query argument with value between 0 and 4.");
}

void WebServer::handle_on() {
    logger.log("/on");
    systemCheck.registerWebCall();
    lossnay.turn_on();
    _server->send(200);
}

void WebServer::handle_off() {
    logger.log("/off");
    systemCheck.registerWebCall();
    lossnay.turn_off();
    _server->send(200);
}

WebServer webServer = WebServer(HTTP_PORT);
