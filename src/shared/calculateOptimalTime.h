
#define DATA_SIZE 7*24

struct emission_time
{
    double emissions;
    int hour;
};
typedef struct emission_time emission_time;

int compare_function (const void *ptr1, const void *ptr2);
void load_emission_data(emission_time *et, double emissions, int hour);