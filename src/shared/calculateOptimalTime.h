    /* 7 days in a week, 24 hours a day, 6*10 minutes in an hour */
#define DATA_SIZE (7*24*6)

struct emission_time
{
    double emissions;
    int min;
};
typedef struct emission_time emission_time;

/* int compare_function (const void *ptr1, const void *ptr2); */
void load_emission_data(emission_time *et, double emissions, int min);
int find_optimal_time(int activeHours);
void load_all_data(emission_time *data);