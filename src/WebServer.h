#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include "LossnayController.h"
#include "WebPages.h"

class WebServer {
    public:
        WebServer(int port);
        void begin();
        void loop();
    private:
        ESP8266WebServer *_server;
        ESP8266HTTPUpdateServer *_httpUpdater;

        void handle_root();
        void handle_get();
        void handle_settings();
        void handle_reset();
        void handle_hard_reset();
        void handle_logs();
        void handle_on();
        void handle_off();
        void handle_fan();
};

extern WebServer webServer;

#endif
