/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:01:57 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/06 21:12:56 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>

int main(int argc, char **argv)
{
	int i;
	char res;

	i = 0;
	if (argc == 2)
	{
		while(argv[1][i])
		{
			if(argv[1][i] >= 'a' && argv[1][i] <= 'z')
			{
				res = (argv[1][i] <= 'm') ? argv[1][i] + 13 : argv[1][i] - 13;
			}
			else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
			{
				res = (argv[1][i] <= 'M') ? argv[1][i] + 13 : argv[1][i] - 13;
			}
			else
				res = (argv[1][i]);
			write(1, &res, 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}