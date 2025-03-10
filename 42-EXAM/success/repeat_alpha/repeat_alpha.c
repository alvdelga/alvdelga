/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:01:40 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/07 10:38:34 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (argc == 2)
	{
		while (argv[1][i])
		{
			if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
				count = argv[1][i] - 96;
			else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
				count = argv[1][i] - 64;
			else
				write(1, &argv[1][i], 1);
			while(count > 0)
			{
				write(1, &argv[1][i], 1);
				count--;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}