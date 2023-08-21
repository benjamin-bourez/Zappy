/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** test_args
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Args.hpp"

Test(args, default_constructeur)
{
    Zappy::GUI::Args args;

    cr_assert_eq(args.getPort(), 0);
    cr_assert_eq(args.getIp(), "");
}

Test(args, setters)
{
    Zappy::GUI::Args args;

    args.setPort(4242);
    args.setIp("192.168.0.0");
    cr_assert_eq(args.getPort(), 4242);
    cr_assert_eq(args.getIp(), "192.168.0.0");
}

Test(args, set_args_empty, .init = cr_redirect_stderr)
{
    Zappy::GUI::Args args;
    char *av[] = {"./zappy_gui", NULL};
    int ac = 1;

    cr_assert_eq(args.setArgs(ac, av), 85);
    cr_assert_stderr_eq_str("Erreur : le numéro de port (-p) doit être spécifié.\n");
}

Test(args, set_all_args)
{
    Zappy::GUI::Args args;
    char *av[] = {"./zappy_gui", "-p", "4242", "-h", "127.0.0.1", NULL};

    cr_assert_eq(args.setArgs(5, av), 0);
    cr_assert_eq(args.getPort(), 4242);
    cr_assert_eq(args.getIp(), "127.0.0.1");
}
