#pragma once
#include <math.h>
#include <stdlib.h>

#define dx 0.01
#define l_bound -90.0
#define u_bound 12.0
#define N (size_t)((u_bound - l_bound) / dx)

enum
{
    db_size = N
};

double DB_C0[db_size];

void create_lookup_table(double *DB_C0)
{
    for (size_t i = 0; i < N; ++i)
    {
        DB_C0[i] = powf(10.0f, (l_bound + i * dx) * 0.05f);
    }
}

double lookup(double value, double *DB_C0)
{
    value = value > l_bound ? value : l_bound;
    value = value < u_bound ? value : u_bound;
    return DB_C0[(size_t)((value - l_bound) / dx)];
}
