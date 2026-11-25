/* ============================ | --------------- | ============================
 *
 * Artie
 *
 * Artie is a diet management system written in C. This file provides the
 * prototipes of structured data and functions implementing its features.
 *
 * ============================ | --------------- | ========================== */

#ifndef ARTIE_H
#define ARTIE_H

typedef struct artie_ingredient artie_ingredient;
typedef struct artie_meal artie_meal;
typedef struct artie_plan artie_plan;

typedef enum artie_mode
{
    ARTIE_UPDATE_INGREDIENT = 0,
    ARTIE_UPDATE_MEAL,
    ARTIE_UPDATE_PLAN
} artie_mode;

typedef enum artie_error
{
    ARTIE_NOERR = 0,
    ARTIE_INVEXT
} artie_error;

typedef enum artie_ingredient_category
{
    ARTIE_ING_NC = -1,
    ARTIE_ING_CARB,
    ARTIE_ING_PROT,
    ARTIE_ING_FAT
} artie_ingredient_category;

typedef enum artie_meal_category
{
    ARTIE_MEAL_NC = -1,
    ARTIE_MEAL_FULL,
    ARTIE_MEAL_SNACK
} artie_meal_category;


artie_ingredient *artie_ingredient_create(void);
void artie_ingredient_destroy(artie_ingredient *);

artie_meal *artie_meal_create(void);
void artie_meal_destroy(artie_meal *);

artie_plan *artie_plan_create(void);
void artie_plan_destroy(artie_plan *);

#endif /* ARTIE_H */

/* artie.h ends here */
