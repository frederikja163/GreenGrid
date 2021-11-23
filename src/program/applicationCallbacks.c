#include "applicationCallbacks.h"

void application_activate(GApplication *app, gpointer userdata) {
    GtkApplication *application = GTK_APPLICATION(app);
    GtkWidget *widget = gtk_application_window_new(application);
    GtkWindow *window = GTK_WINDOW(widget);

    gtk_window_set_title(window, "Power consumption CO2 Calculator");
    gtk_window_set_default_size(window, 400, 300);

    gtk_window_present(window);
}