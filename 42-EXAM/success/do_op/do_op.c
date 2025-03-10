/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:15:26 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/06 21:31:47 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stdlib.h"
# include "stdio.h"

int main(int argc, char **argv)
{
	int a;
	int b;
	char c;
	int res;

	

	if(argc == 4)
	{
		a = atoi(argv[1]);
		b = atoi(argv[3]);
		c = argv[2][0];
		if (c == '+')
			res = (a + b);
		if (c == '*')
			res = (a * b);
		if (c == '-')
			res = (a - b);
		if (c == '/')
			res = (a / b);
		if (c == '%')
			res = (a % b);
		printf("%d", res);
	}
	printf("\n");
	return (0);
}