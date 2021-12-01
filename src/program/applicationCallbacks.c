#include "applicationCallbacks.h"

#include <cairo.h>
#include <math.h>
#include <stdio.h>

#include "cairoExtensions.h"

#define GRAPH_ARROW_LEG_LENGTH 10
#define GRAPH_ARROW_ANGLE 0.8
#define GRAPH_MARGIN_X 50
#define GRAPH_MARGIN_Y 50
#define GRAPH_SIZE_X 500
#define GRAPH_SIZE_Y 500
#define GRAPH_AXIS_LABEL_SIZE 10

static int f(int x) {
    int value = (int)(cos((double)x / 3.141) * 100);
    return value;
}

static void on_draw(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer data) {
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_source_rgb(cr, 0, 0, 0);
    
    cairo_set_line_width(cr, 0.75);
    int i;
    for (i = 100; i < 200; i++) {
        cairo_line_to(cr, i + 1, f(i+1) + 200);
    }
    cairo_stroke(cr);

    /* Draw arrows for axis. */
    cairo_set_line_width(cr, 2);
    cairo_draw_arrow(cr,
                        GRAPH_MARGIN_X, GRAPH_MARGIN_Y + GRAPH_SIZE_Y,
                        GRAPH_MARGIN_X, GRAPH_MARGIN_Y,
                        GRAPH_ARROW_LEG_LENGTH, GRAPH_ARROW_ANGLE);
    cairo_draw_arrow(cr,
                        GRAPH_MARGIN_X, GRAPH_SIZE_Y + GRAPH_MARGIN_Y,
                        GRAPH_MARGIN_X + GRAPH_SIZE_X, GRAPH_MARGIN_Y + GRAPH_SIZE_Y,
                        GRAPH_ARROW_LEG_LENGTH, GRAPH_ARROW_ANGLE);
    cairo_stroke(cr);

    cairo_set_font_size(cr, GRAPH_AXIS_LABEL_SIZE);
    cairo_move_to(cr, GRAPH_MARGIN_X + GRAPH_SIZE_X, GRAPH_MARGIN_Y + GRAPH_SIZE_Y);
    cairo_show_text(cr, " Time");
    cairo_move_to(cr, GRAPH_MARGIN_X, GRAPH_MARGIN_Y);
    cairo_show_text(cr, " CO2");
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