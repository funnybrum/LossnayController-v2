#include "LossnayController.h"

char buffer[4096];

WebServer::WebServer(Logger* logger, NetworkSettings* networkSettings)
    :WebServerBase(networkSettings, logger) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/get", std::bind(&WebServer::handle_get, this));
    server->on("/on", std::bind(&WebServer::handle_on, this));
    server->on("/off", std::bind(&WebServer::handle_off, this));
    server->on("/mode", std::bind(&WebServer::handle_mode, this));
    server->on("/speed", std::bind(&WebServer::handle_speed, this));

}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    wifi.parse_config_params(this);

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);


    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_get() {
    sprintf_P(buffer,
              GET_JSON,
              0.0f,
              0.0f,
              0.0f,
              0.0f,
              0.0f,
              0.0f,
              "false",
              "true",
              -1);
    server->send(200, "application/json", buffer);
}

void WebServer::handle_on() {
    server->send(200);
}

void WebServer::handle_off() {
    server->send(200);
}

void WebServer::handle_mode() {
    if (server->args() != 1
        || server->arg(0).length() != 0) {
        server->send(400, "text/plain", "try with /mode?lossnay");
        return;
    }

    if (!server->argName(0).equals("lossnay")
        && !server->argName(0).equals("bypass")) {
        server->send(400, "text/plain", "supported modes are lossnay and bypass");
        return;
    }

    // TODO
    Serial.print("Mode set to ");
    Serial.println(server->argName(0));
    server->send(200);
}

void WebServer::handle_speed() {
    if (server->args() != 1
        || server->arg(0).length() != 0
        || server->argName(0).length() != 1) {
        server->send(400, "text/plain", "try with /speed?3");
        return;
    }

    uint8_t speed = atoi(server->argName(0).c_str());
    if (speed < 1 || speed > 4) {
        server->send(400, "text/plain", "supported speed values are 1 to 4");
        return;
    }

    // TODO
    Serial.print("Speed set to ");
    Serial.println(speed);
    server->send(200);
}
