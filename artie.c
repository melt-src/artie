/* artie.c */

#include "dvector/dvector.h"
#include "artie.h"

struct artie_ingredient
{
    char *name;
    artie_ingredient_category category;
    float macro_props;
    size_t calories;
};

struct artie_meal
{
    char *name;
    artie_meal_category category;
    dvector *ingredients;
};

struct artie_plan
{
    artie_day_of_week dow;


/* artie.c ends here */
