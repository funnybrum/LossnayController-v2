#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "LossnayController.h"

#ifndef LOG_SIZE
#define LOG_SIZE 1024
#endif

/*
 * Logging tool.
 * 
 * Provide rotating log buffer with configurable maximum log content size.
 */
class Logger {
    public:
        void begin();
        void loop();
        void log(char* msg);
        void log(const char *format, ...);
        const char* getLogs();
    private:
        char buffer[LOG_SIZE];
        unsigned int pos = 0;
};

extern Logger logger;

#endif
