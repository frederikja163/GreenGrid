#include "applicationCallbacks.h"

#include <cairo.h>
#include <math.h>
#include <stdio.h>

#include "cairoExtensions.h"

static int f(int x) {
    int value = (int)(cos((double)x / 3.141) * 100);
    return value;
}

static void on_draw(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer data) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 0.75);

    int i;
    for (i = 100; i < 200; i++) {
        cairo_line_to(cr, i + 1, f(i+1) + 200);
    }
    cairo_stroke(cr);

    cairo_set_line_width(cr, 2);
    cairo_draw_arrow(cr, 50, 500, 50, 50, 10, 0.8);
    cairo_draw_arrow(cr, 50, 500, 500, 500, 10, 0.8);
    cairo_stroke(cr);
}

void application_activate(GApplication *application, gpointer userdata) {
    GtkWidget *window;
    GtkBuilder *builder;

    builder = gtk_builder_new_from_file("bin/main.ui");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "win"));
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(application));

    gtk_window_present(GTK_WINDOW(window));
    
    GtkWidget *area;
    area = gtk_drawing_area_new();
    gtk_widget_allocate(area, 700, 700, -1, NULL);
    gtk_widget_set_parent(area, window);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), on_draw, NULL, NULL);
}