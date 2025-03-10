/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fizzbuzz.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:04:10 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/07 17:06:35 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>

void ft_putnbr(int n)
{
	char res;
	if (n >= 10)
	{
		ft_putnbr(n /10);
	}
	res = (n % 10) + '0';
	write(1, &res, 1);
	
}

int main(int argc, char **argv)
{
    int i;

    i = 1;

    while ( i <= 100)
    {
		if ((i % 3 == 0 ) && ( i % 5 == 0 ) )
		write(1, "fizzbuzz", 8);
        else if(i % 3 == 0 )
            write(1, "fizz", 4);
        else if ( i % 5 == 0 )
			write(1, "buzz", 4);
        else
            ft_putnbr(i);
        write(1, "\n", 1);
        i++;
    }

}