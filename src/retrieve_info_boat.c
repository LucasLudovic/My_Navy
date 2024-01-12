/*
** EPITECH PROJECT, 2024
** navy
** File description:
** retrieve_info_boat.c
*/

#include "my_macros.h"
#include "retrieve_info_boat.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>

static int my_isnum(char c)
{
    if (c >= 48 && c <= 57) {
        return FALSE;
    } else {
        return TRUE;
    }
}

static int ismap(char c)
{
    if (my_isnum(c) == 0 || (c >= 65 && c <= 90)) {
        return FALSE;
    } else {
        return TRUE;
    }
}

static int size_of_arr(const char *str, int count)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] == ':' || str[i] == '\0')
            count += 1;
    }
    return count;
}

static char **len_char(const char *str)
{
    int a = 0;
    int len = 0;
    int count = 0;
    char **arr = NULL;

    count = size_of_arr(str, count);
    arr = malloc(sizeof(char *) * count);
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (ismap(str[i]) == 0 && ismap(str[i + 1]) == 0)
            len += 1;
        if ((ismap(str[i]) == 0 && str[i + 1] == ':') ||
            (ismap(str[i]) == 0 && str[i + 1] == '\0')) {
            len += 1;
            arr[a] = malloc(sizeof(char *) * len);
            len = 0;
            a += 1;
        }
    }
    return arr;
}

static void last(char **arr, int *a, int *y)
{
    *a += 1;
    arr[*y][*a] = '\0';
    *y += 1;
    *a = 0;
}

static void loop(const char *str, char **arr, int *a, int *y)
{
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (ismap(str[i]) == 0 && ismap(str[i + 1]) == 0) {
            arr[*y][*a] = str[i];
            *a += 1;
        }
        if (ismap(str[i]) == 0 && str[i + 1] == ':') {
            arr[*y][*a] = str[i];
            *a += 1;
            arr[*y][*a] = '\0';
            *y += 1;
            *a = 0;
        }
        if (str[i] == ' ')
            *a = 0;
        if (ismap(str[i]) == 0 && str[i + 1] == '\0') {
            arr[*y][*a] = str[i];
            last(arr, a, y);
        }
    }
    arr[*y] = NULL;
}

char **retrieve_info_boat(char *info)
{
    char **arr = NULL;
    int a = 0;
    int y = 0;

    if (info == NULL)
        return NULL;
    arr = len_char(info);
    loop(info, arr, &a, &y);
    return arr;
}
