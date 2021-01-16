#include "LossnayController.h"

void Logger::begin() {
    buffer[0] = 0;
#ifdef LOG_TO_SERIAL
    Serial.begin(115200);
    while (! Serial) {
        delay(1);
    }
#endif
}

void Logger::loop() {
}

void Logger::log(char* msg) {
#ifdef LOG_TO_SERIAL
    Serial.println(msg);
#endif
    // new_size = pos + strlen(msg) + 1 '\n' + 1 '\0'
    // this will overflow the buffer by new_size - sizeof(buffer)
    int overflowBy = pos + strlen(msg) + 2 - sizeof(buffer);

    if (overflowBy > 0) {
        // shift back overflowBy chars to avoid buffer overflow
        memmove(buffer, buffer + overflowBy, sizeof(buffer) - overflowBy);
        pos -= overflowBy;
    }

    strcpy(buffer + pos, msg);
    pos += strlen(msg);

    // add new line char
    buffer[pos] = '\n';
    pos++;

    // add null terminating character
    buffer[pos] = 0;
}

void Logger::log(const char *format, ...) {
    va_list arg;
    va_start(arg, format);
    char buffer[128];
    unsigned int len = vsnprintf(buffer, sizeof(buffer), format, arg);
    va_end(arg);
    if (len > sizeof(buffer)) {
        log("Trimming log!");
    }
    log(buffer);
}

const char* Logger::getLogs() {
    return buffer;
}

Logger logger = Logger();