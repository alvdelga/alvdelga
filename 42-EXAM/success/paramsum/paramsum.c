/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:11:06 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/12 09:33:52 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "unistd.h"
# include "stdio.h"

char ft_putnbr(int nb)
{
    if(nb > 9)
        ft_putnbr(nb / 10);
    nb = ((nb % 10) + '0');
    write(1, &nb, 1);
}

int main(int argc, char **argv)
{
    int i;
    char num;

    i = 1;
    if(argc == 1)
    {
        write(1, "0\n", 2);
        return(0);
    }
    while(argv[i])
    {
        i++;
    }
    i--;
    num = ft_putnbr(i);
    write(1, "\n", 1);
}