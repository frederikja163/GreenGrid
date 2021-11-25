#include "applicationCallbacks.h"

void application_activate(GApplication *application, gpointer userdata) {
    GtkWidget *window;
    GtkBuilder *builder;

    builder = gtk_builder_new_from_file("bin/main.ui");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "win"));
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(application));

    gtk_window_present(GTK_WINDOW(window));
}