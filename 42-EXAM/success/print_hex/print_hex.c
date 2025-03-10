/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:10:42 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/07 22:49:56 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include "stdlib.h"

int main(int argc, char **argv)
{
    int num;
    char *cen;
    char res[20];
    int i;
    int j;

    j = 0;
    i = 0;
    
    cen = "0123456789abcdef";
    if (argc == 2)
    {   
		num = atoi(argv[1]);
		if (num == 0)
        	res[j++] = '0';
        while (num > 0)
        {
            res[j++] = cen[num % 16];
			num /= 16;
			i++;
		}
		i = j -1;
        while (i >=0)
            write(1, &res[i--], 1);

    }
    write(1, "\n", 1);
    return (0);
}