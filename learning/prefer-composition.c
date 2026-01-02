#include <stdio.h>
#include <stdbool.h>

typedef struct {
    void (*log)(const char*);
} Logger;

void console_log(const char *msg) {
    printf("Console: %s\n", msg);
}

void file_log(const char *msg) {
    printf("File: %s\n", msg);
}

// object that HAS-A Logger
typedef struct {
    Logger logger;
} Application;


void app_log(Application *app, const char *msg) {
    app->logger.log(msg);
}


int main(void) {
    Logger console_logger = { console_log };
    Logger file_logger = { file_log };

    Application app_1 = { console_logger };
    Application app_2 = { file_logger };

    app_log(&app_1, "Hello");
    app_log(&app_2, "John!");

    return 0;
}
