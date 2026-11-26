/* artie.c */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <assert.h>
#include <string.h>

#include "artie.h"
#include "chopdat/chopdat.h"
#include "dvector/dvector.h"

#define NOFARGS 3
#define DBPATH "./db/artie.db"

void usage(FILE *stream)
{
    fprintf(stream, "usage: ./artie <-i | -m | -p> <input.csv>\n");
}

artie_error get_file_ext(const char *file_path)
{
    artie_error code = ARTIE_INVEXT;
    const char *ext = strrchr(file_path, '.');

    if (!ext) return code;

    ext = ext + 1;

    if (strcmp(ext, "csv") == 0) {
        code = ARTIE_NOERR;
    }
    return code;
}

int main(int argc, char **argv)
{

    /* arguments parsing */
    if (argc < NOFARGS) {
        usage(stderr);
        fprintf(stderr, "artie: error: option or input file not provided.\n");
        exit(1);
    }

    const char *file_path = argv[2];
    int ext_code = get_file_ext(file_path);

    if (ext_code != ARTIE_NOERR) {
        fprintf(stderr, "artie: error: invalid file extension\n");
        usage(stderr);
        exit(1);
    }

    /* reading the file into memory */
    chopdat_buffer *buffer = chopdat_buffer_create(file_path);

    if (!buffer) {
        fprintf(stderr, "chopdat: error: could not read file into memory.\n");
        exit(1);
    }

    /* extracting tokens */
    chopdat_csv_table *table = chopdat_csv_file(buffer);
    chopdat_csv_perror parse_error = chopdat_csv_table_errcode(table);
    size_t nrows = chopdat_csv_table_nrows(table);
    size_t ncols = chopdat_csv_table_ncols(table);
    size_t ntokens = chopdat_csv_table_ntokens(table);

    switch (parse_error) {
    case CHOPDAT_CSV_NOTABLE:
        fprintf(stderr, "chopdat: error: the table is null\n");
        exit(1);
        break;
    case CHOPDAT_CSV_NOERR:
        printf("chopdat: file is well formatted\n");
        break;
    case CHOPDAT_CSV_NULLBUF:
        fprintf(stderr, "chopdat: error: no data to parse\n");
        exit(1);
        break;
    case CHOPDAT_CSV_SYNTAX:
        fprintf(stderr, "chopdat: error: invalid syntax at line %ld\n", nrows);
        exit(1);
        break;
    default:
        fprintf(stderr, "chopdat: error: defaulted for some reason\n");
        exit(1);
        break;
    }

    /* database connection opening and setting */
    sqlite3 *db;

    if (sqlite3_open(DBPATH, &db) != SQLITE_OK) {
        fprintf(stderr, "could not open database: %s.\n", sqlite3_errmsg(db));
        return 1;
    }

    int tmp = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    if (tmp != SQLITE_OK) {
        fprintf(stderr, "error: PRAGMA: %s\n", sqlite3_errmsg(db));
        return 1;
    }


    chopdat_token *sn = chopdat_csv_table_spit_token(table, 0);
    char *s_name = chopdat_token_start(sn);
    size_t l_name = chopdat_token_length(sn);

    chopdat_token *scat = chopdat_csv_table_spit_token(table, 1);
    char *s_scat = chopdat_token_start(scat);
    size_t l_scat = chopdat_token_length(scat);

    chopdat_token *smac = chopdat_csv_table_spit_token(table, 2);
    char *s_smac = chopdat_token_start(smac);
    size_t l_smac = chopdat_token_length(smac);

    chopdat_token *skcal = chopdat_csv_table_spit_token(table, 3);
    char *s_skcal = chopdat_token_start(skcal);
    size_t l_skcal = chopdat_token_length(skcal);

    char *n = strndup(s_name, l_name);
    artie_ingredient_category c = atoi(strndup(s_scat, l_scat));
    double m = atof(strndup(s_smac, l_smac));
    size_t k = (size_t) atoi(strndup(s_skcal, l_skcal));

    artie_ingredient *i = artie_ingredient_create(n, c, m, 0, 0, k);

    if (!i) {
        fprintf(stderr, "artie: error: could not allocate new ingredient\n");
        exit(1);
    }

    char *a = artie_ingredient_name(i);
    artie_ingredient_category b = artie_ingredient_cat(i);
    double *pio = artie_ingredient_macrop(i);
    size_t d = artie_ingredient_calories(i);

    printf("(%s,%d,[%f;%f;%f],%zu)\n", a, b, pio[0], pio[1], pio[2], d);

    /* closing connection */
    if (sqlite3_close(db) != SQLITE_OK) {
        fprintf(stderr, "could not close database: %s.\n", sqlite3_errmsg(db));
        return 1;
    }

    /* freeing memory */
    chopdat_csv_table_destroy(table);
    chopdat_buffer_destroy(buffer);

    return 0;
}

/* artie.c ends here */
