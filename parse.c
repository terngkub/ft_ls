/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkamolba <nkamolba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 19:47:59 by nkamolba          #+#    #+#             */
/*   Updated: 2018/10/15 19:48:19 by nkamolba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
void parse_args(int argc, char **argv)
{
    while ()
    {

    }
}

void parse_flag()
{

}
*/

// store a list of flag
// store a list of path
// process each path in queue
// if r when process path 


void process_path(const char *path)
{
    DIR             *dip;
    struct dirent   *dit;

    dip = opendir(path);
    
    while (1)
    {
        dit = readdir(dip);
        if (dit == NULL)
            break;
        ft_printf("%s\t", dit->d_name);
    }
    ft_putchar('\n');
    closedir(dip);
}

/*
trying stat
int main(int argc, char **argv)
{
    struct stat file_stat;

    if (argc != 2)
        return 1;
    if (stat(argv[1], &file_stat) < 0)
        return 1;
    printf("Size: %ld\n", file_stat.st_size);
    printf("Mode: %d\n", file_stat.st_mode);
    return (0);
}
*/

/*
trying time
int main(void)
{
    time_t seconds;
    const char *date;

    seconds = time(NULL);
    date = ctime(&seconds);
    printf("%ld\n", seconds);
    printf("%s", date);
    return (0);
}
*/