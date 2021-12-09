#ifndef IS_DATA_OUTDATED_H
#define IS_DATA_OUTDATED_H

#include <stdbool.h>

int get_time_difference(const char *timeStamp);
struct tm timestamp_to_tm(const char *timeStamp);
bool is_data_outdated(int maxTimeDiff, const char * receivingData);

#endif