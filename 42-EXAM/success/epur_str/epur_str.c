/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epur_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:10:26 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/06 23:02:38 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "unistd.h"

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (c);
}

int main(int argc, char **argv)
{
	int i;
	int j;
	int len;

	len = 0;
	i = 0;
	j = 0;
    if (argc == 2)
    {
		while(argv[1][j])
		{
			len++;
			j++;
		}
		if (argv[1][0] == ' ' && argv[1][0])
				i++;
        while(argv[1][i])
        {
            while(argv[1][i] != ' ' && argv[1][i])
                ft_putchar(argv[1][i++]);
			while (argv[1][i] == ' '&& argv[1][i])
                i++;
			if ((i < len) && (i < len -1))
				ft_putchar(' ');
			while(argv[1][i] != ' ' && argv[1][i])
			{
				ft_putchar(argv[1][i++]);
			}
        }
    }
    ft_putchar('\n');
    return (0);
}