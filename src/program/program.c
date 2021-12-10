#include <stdio.h>
#include <stdlib.h>
#include "applicationCallbacks.h"

int start_application(int args[3]) {
    GtkApplication *application;
    int state;

    application = gtk_application_new("com.b228.co2", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(application, "activate", G_CALLBACK(application_activate), args);

    state = g_application_run(G_APPLICATION(application), 0, NULL);
    g_object_unref(application);

    return state;
}


int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "3 arguments are needed for this command! try '%s [activeTime] [startSearch] [endSearch]'", argv[0]);
        return EXIT_FAILURE;
    }
    int args[3] = { atoi(argv[1]), atoi(argv[2]), atoi(argv[3]) };

    start_application(args);
}
