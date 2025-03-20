/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lcm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:28:55 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/13 21:09:20 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

// Función para calcular el MCD (Máximo Común Divisor) usando el Algoritmo de Euclides
unsigned int mcd(unsigned int a, unsigned int b)
{
    unsigned int temp;
    
    while (b != 0)
    {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Función para calcular el MCM (Mínimo Común Múltiplo)
unsigned int lcm(unsigned int a, unsigned int b)
{
    if (a > INT_MAX || b > INT_MAX)
    return 0;
    if (a == 0 || b == 0)
        return 0;
    return (a / mcd(a, b)) * b;
}

int main()
{
    unsigned int a = 10;
    unsigned int b = 18;

    unsigned int res;

    res = lcm(a, b);


    printf("MCD = %u\n", mcd(a, b));
    printf("MCM = %u\n", res);

    return 0;
}
