/*
** EPITECH PROJECT, 2024
** Main
** File description:
** Main for the navy project
*/

#include "my_macros.h"
#include <stdio.h>
#include "my_navy.h"

int main(int ac, char **av)
{
    if (ac > 2 || av == NULL || av[1] == NULL)
        return FAILURE;
    if (ac == 2 && av[2] == NULL)
        return FAILURE;
    return my_navy(av);
}
