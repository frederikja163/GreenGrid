#include "applicationCallbacks.h"

#include <cairo.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "fileIO.h"
#include "dmiParser.h"
#include "cairoExtensions.h"
#include "calculateOptimalTime.h"

#define GRAPH_ARROW_LEG_LENGTH 10
#define GRAPH_ARROW_ANGLE 0.8
#define GRAPH_PADDING_X 50
#define GRAPH_PADDING_Y 50
#define GRAPH_AXIS_LABEL_SIZE 10
#define GRAPH_GRID_WIDTH 0.5
#define GRAPH_WIDTH 1
#define GRAPH_LABEL_WIDTH 2
#define GRAPH_HIGHLIGHT_WIDTH 4

#define GET_X_VALUE(i, width, start, end) (GRAPH_PADDING_X + ((i) - (start)) * (width) / ((end) - (start)))
#define GET_Y_VALUE(wind, height) (GRAPH_PADDING_Y + (25 - calculate_co2(wind)) * (height) / 25)

static void on_draw(GtkDrawingArea *drawing_area, cairo_t *cr, int width, int height, gpointer data) {
    width -= GRAPH_PADDING_X * 2;
    height -= GRAPH_PADDING_Y * 2;

    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_source_rgb(cr, 0, 0, 0);

    /* Find optimal time. */
    int *args = (int*)data;
    int activeHours = args[0];
    int startHour = args[1];
    int endHour = args[2];
    char *optimalTime = find_optimal_time(activeHours, startHour, endHour);
    
    /* Graph data. */
    int i, x, y, startIndex = -1;
    char *inputString = read_file("data/ninjo2dmidk.json");
    char *updateTimeStamp;
    windValue *values = load_wind_data(inputString, &updateTimeStamp);
    free(inputString);
    free(updateTimeStamp);

    /* Graph data. */
    cairo_set_line_width(cr, GRAPH_WIDTH);
    x = GET_X_VALUE(startHour, width, startHour, endHour);
    y = GET_Y_VALUE(values[startHour].windspeed, height);
    for (i = startHour; i <= endHour; i++) {
        /* Start highlight for optimal time. */
        if (strcmp(optimalTime, values[i].timestamp) == 0) {
            startIndex = i;
            cairo_stroke(cr);
            cairo_set_line_width(cr, GRAPH_WIDTH);
            cairo_set_source_rgb(cr, 0, 0, 0);
        }
        /* Continue highlight for optimal time. */
        else if (i - startIndex <= activeHours && startIndex != -1) {
            cairo_stroke(cr);
            cairo_set_source_rgb(cr, 1, 0.2, 1);
            cairo_set_line_width(cr, GRAPH_HIGHLIGHT_WIDTH);
        }
        /* Normal graph. */
        else {
            cairo_stroke(cr);
            cairo_set_line_width(cr, GRAPH_WIDTH);
            cairo_set_source_rgb(cr, 0, 0, 0);
        }

        /* Draw graph. */
        cairo_move_to(cr, x, y);
        x = GET_X_VALUE(i, width, startHour, endHour);
        y = GET_Y_VALUE(values[i].windspeed, height);
        cairo_line_to(cr, x, y);
        
        if ((endHour - startHour) <= 8 || (i - startHour) % ((endHour - startHour) / 8) == 0) {
            /* Draw grid. */
            cairo_stroke_preserve(cr);
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_set_line_width(cr, GRAPH_GRID_WIDTH);
            cairo_line_to(cr, x, GRAPH_PADDING_Y + height);
            cairo_stroke(cr);

            /* X axis labels. */
            cairo_move_to(cr, x, GRAPH_PADDING_Y * 2 + height);
            cairo_rotate(cr, -1);
            cairo_text_timestamp(cr, "", values[i].timestamp);
            cairo_rotate(cr, 1);
        }
    }
    cairo_stroke(cr);
    
    cairo_set_line_width(cr, GRAPH_LABEL_WIDTH);
    cairo_set_source_rgb(cr, 0, 0, 0);

    /* Display optimal time. */
    cairo_move_to(cr, GRAPH_PADDING_X, GRAPH_PADDING_Y / 2);
    cairo_text_timestamp(cr, "Optimal time: ", optimalTime);

    /* Draw arrows for axis. */
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

    for (i = 0; i < WINDVALUE_COUNT; i++) {
        free(values[i].timestamp);
    }
    free(values);
}

void application_activate(GApplication *application, gpointer userdata) {
    GtkWidget *window;

    /* Create window. */
    window = gtk_application_window_new(GTK_APPLICATION(application));
    gtk_window_set_title (GTK_WINDOW(window), "Greengrid");
    gtk_window_set_default_size (GTK_WINDOW(window), 500, 500);
    gtk_window_set_application(GTK_WINDOW(window), GTK_APPLICATION(application));

    /* Create drawing area. */
    GtkWidget *area;
    area = gtk_drawing_area_new();
    gtk_widget_allocate(area, 500, 500, -1, NULL);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(area), on_draw, userdata, NULL);
    gtk_window_set_child(GTK_WINDOW(window), area);
    
    gtk_window_present(GTK_WINDOW(window));
}