/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:26:49 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/13 12:53:37 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stdlib.h"
# include "string.h"
# include "stdio.h"

int value_of(char c)
{
    if (c >= '0' && c <= '9')
        return(c - '0');
    else if (c >= 'a' && c <= 'f')
        return(c - 'a' + 10);
    else if (c >= 'A' && c <= 'F')
        return(c - 'A' + 10);
    else
        return (0);
}

int is_valid(char c, int base)
{
    char digits[17] = "0123456789abcdef";
    char digits2[17] = "0123456789ABCDEF";

    while(base--)
    {
        if((digits[base] == c) || (digits2[base] == c))
            return (1);
    }
    return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
    int res;
    int sig;
    int i;

    res = 0;
    sig = 1;
    i = 0;
    while (str[i] == ' ')
        i++;
    if(str[i] == '-')
        sig = -1;
    if(str[i] == '-' || str[i] == '+')
        i++;
    while (is_valid(str[i], str_base))
        res = res * str_base + value_of(str[i++]);
    return (res * sig);
}

// int		main(int ac, char **av)//
// {//
// 	if (ac == 3)//
// 		printf("result: %d\n", ft_atoi_base(av[1], atoi(av[2])));//
// 	return (0);//
// }//