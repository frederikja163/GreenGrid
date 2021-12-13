#include "cairoExtensions.h"
#include <cairo.h>
#include <math.h>
#include <string.h>
#include "timestamp.h"
#define PI 3.141592654

void cairo_text_timestamp(cairo_t *cr, const char *text, const char *timeStamp) {
    int len = strlen(text);
    char *str = calloc(len + 13, sizeof(char));
    struct tm time = timestamp_to_tm(timeStamp);

    sprintf(str, "%s%02i/%02i %02i:%02i", text, time.tm_mday, time.tm_mon + 1, time.tm_hour, time.tm_min);

    cairo_show_text(cr, str);

    free(str);
}

/* With help from math.stackexchange https://math.stackexchange.com/questions/1314006/drawing-an-arrow */
void cairo_draw_arrow(cairo_t *cr, double startX, double startY, double endX, double endY, double legLength, double legAngle) {
    /* Rename variables for easier conversion with stackexchange. */
    double x1 = startX;
    double y1 = startY;
    double x2 = endX;
    double y2 = endY;
    double l2 = legLength;
    double theta = legAngle;

    /* Calculate l1. */
    double baseX = x1 - x2;
    double baseY = y1 - y2;
    double l1 = sqrt(baseX * baseX + baseY * baseY);

    /* Pre-computed variables. */
    double l2Overl1 = l2 / l1;
    double cosTheta = cos(theta);
    double sinTheta = sin(theta);

    /* Calculate legs. */
    double x3 = x2 + l2Overl1 * (baseX * cosTheta + baseY * sinTheta);
    double y3 = y2 + l2Overl1 * (baseY * cosTheta - baseX * sinTheta);
    double x4 = x2 + l2Overl1 * (baseX * cosTheta - baseY * sinTheta);
    double y4 = y2 + l2Overl1 * (baseY * cosTheta + baseX * sinTheta);

    /* Draw base of arrow. */
    cairo_move_to(cr, x1, y1); cairo_line_to(cr, x2, y2);
    /* Draw arrow legs. */
    cairo_line_to(cr, x3, y3);
    cairo_move_to(cr, x4, y4); cairo_line_to(cr, x2, y2);
}