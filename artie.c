/* artie.c */

#include <stdlib.h>
#include <time.h>

#include "dvector/dvector.h"
#include "artie.h"

struct artie_ingredient
{
    char *name;
    artie_ingredient_category category;
    double *macro_proportions;
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
    time_t dom;
    artie_meal meal;
};

artie_ingredient *artie_ingredient_create(char *n,
                                          artie_ingredient_category c,
                                          double mc,
                                          double mp,
                                          double mf,
                                          size_t k)
{
    artie_ingredient *i = malloc(sizeof(*i));

    if (!i) return NULL;

    i->macro_proportions = malloc(3 * sizeof(*(i->macro_proportions)));

    if (!i->macro_proportions) return NULL;

    i->name = n;
    i->category = c;
    i->macro_proportions[0] = mc;
    i->macro_proportions[1] = mp;
    i->macro_proportions[2] = mf;
    i->calories = k;

    return i;
}

void artie_ingredient_destroy(artie_ingredient *i)
{
    if (i && i->macro_proportions) {
        free(i->macro_proportions);
        free(i);
    }
    return;
}

char *artie_ingredient_name(artie_ingredient *i)
{
    if (!i) return NULL;
    return i->name;
}

artie_ingredient_category artie_ingredient_cat(artie_ingredient *i)
{
    if (!i) return ARTIE_ING_NC;
    return i->category;
}

double *artie_ingredient_macrop(artie_ingredient *i)
{
    if (!i) return NULL;
    return i->macro_proportions;
}

size_t artie_ingredient_calories(artie_ingredient *i) {
    if (!i) return 0;
    return i->calories;
}


/* artie.c ends here */
