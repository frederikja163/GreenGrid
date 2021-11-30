#include "applicationCallbacks.h"

int main(int argc, char **argv) {
    GtkApplication *application;
    int state;

    application = gtk_application_new("com.b228.co2", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(application, "activate", G_CALLBACK(application_activate), NULL);

    state = g_application_run(G_APPLICATION(application), argc, argv);
    g_object_unref(application);

    return state;
}
