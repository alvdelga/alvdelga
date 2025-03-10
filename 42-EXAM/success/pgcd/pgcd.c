/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pgcd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:29:48 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/08 21:56:15 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int main(int argc, char **argv)
{
    int num;
    int num2;
    int i;
    int count;

    i = 1;
    count = 0;
    if (argc == 3)
    {
        num = atoi(argv[1]);
        num2 = atoi(argv[2]);
        if(num <= 0 || num2 <= 0)
        {
            write(1, "\n", 1);
            return (0);
        }
        while ((i <= num) || (i <= num2))
        {
            if ((num % i == 0) && (num2 % i == 0))
            {
                count = i;
            }
            i++;
        }
        printf("%d", count);
    }
   	printf("\n");
    return (0);
}