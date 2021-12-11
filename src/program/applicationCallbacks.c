#include "applicationCallbacks.h"

#include <cairo.h>
#include <math.h>
#include <stdio.h>

#include "fileIO.h"
#include "dmiParser.h"
#include "cairoExtensions.h"
#include "calculateOptimalTime.h"

#define GRAPH_ARROW_LEG_LENGTH 10
#define GRAPH_ARROW_ANGLE 0.8
#define GRAPH_PADDING_X 50
#define GRAPH_PADDING_Y 50
#define GRAPH_SIZE_X 500
#define GRAPH_SIZE_Y 500
#define GRAPH_AXIS_LABEL_SIZE 10

#define GET_X_VALUE(i, width, start, end) (GRAPH_PADDING_X + (i) * (width) / ((end) - (start)))
#define GET_Y_VALUE(wind, height) (GRAPH_PADDING_Y + (25 - calculate_co2(wind)) * (height) / 25)

static void on_draw(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer data) {
    width -= GRAPH_PADDING_X * 2;
    height -= GRAPH_PADDING_Y * 2;

    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_source_rgb(cr, 0, 0, 0);

    cairo_set_line_width(cr, 1);
    int *args = (int*)data;
    int activeHours = args[0];
    int startHour = args[1];
    int endHour = args[2];
    char *optimal_time = find_optimal_time(activeHours, startHour, endHour);
    cairo_move_to(cr, 250, 250);
    cairo_show_text(cr, optimal_time);

    cairo_show_text_format(cr, "Test %i", 1);

    
    /* Graph data. */
    int i;
    char *inputString = read_file("data/ninjo2dmidk.json");
    char *updateTimeStamp;
    windValue *values = load_wind_data(inputString, &updateTimeStamp);
    free(inputString);
    free(updateTimeStamp);
    cairo_set_line_width(cr, 0.75);
    cairo_move_to(cr, GET_X_VALUE(i, width, startHour, endHour), GET_Y_VALUE(values[i].windspeed, height));
    for (i = 0; i < DATA_SIZE; i++) {
        cairo_line_to(cr, GET_X_VALUE(i, width, startHour, endHour), GET_Y_VALUE(values[i].windspeed, height));
    }
    cairo_stroke(cr);

    /* Draw arrows for axis. */
    cairo_set_line_width(cr, 2);
    cairo_draw_arrow(cr,
                        GRAPH_PADDING_X, GRAPH_PADDING_Y + height,
                        GRAPH_PADDING_X, GRAPH_PADDING_Y,
                        GRAPH_ARROW_LEG_LENGTH, GRAPH_ARROW_ANGLE);
    cairo_draw_arrow(cr,
                        GRAPH_PADDING_X, height + GRAPH_PADDING_Y,
                        GRAPH_PADDING_X + width, GRAPH_PADDING_Y + height,
                        GRAPH_ARROW_LEG_LENGTH, GRAPH_ARROW_ANGLE);
    cairo_stroke(cr);

    /* Draw axis labels. */
    cairo_set_font_size(cr, GRAPH_AXIS_LABEL_SIZE);
    cairo_move_to(cr, GRAPH_PADDING_X + width, GRAPH_PADDING_Y + height);
    cairo_show_text(cr, " Time");
    cairo_move_to(cr, GRAPH_PADDING_X, GRAPH_PADDING_Y);
    cairo_show_text(cr, "CO2");
}

void application_activate(GApplication *application, gpointer userdata) {
    GtkWidget *window;

    window = gtk_application_window_new(GTK_APPLICATION(application));
    gtk_window_set_title (GTK_WINDOW(window), "Greengrid");
    gtk_window_set_default_size (GTK_WINDOW(window), 500, 500);
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(application));

    GtkWidget *area;
    area = gtk_drawing_area_new();
    gtk_widget_allocate(area, 500, 500, -1, NULL);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), on_draw, userdata, NULL);
    gtk_window_set_child(GTK_WINDOW(window), area);
    
    gtk_window_present(GTK_WINDOW(window));
}