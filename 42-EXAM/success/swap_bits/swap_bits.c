/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:12:31 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/07 17:26:24 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	swap_bits(unsigned char octet)
{
    return ((octet >> 4) | (octet << 4));
}


// unsigned char	swap_bits(unsigned char octet)
// {
//     return
//         (((octet >> 0) & 1 )  << 7 ) |
//         (((octet >> 1) & 1 )  << 6 ) |
//         (((octet >> 2) & 1 )  << 5 ) |
//         (((octet >> 3) & 1 )  << 4 ) |
//         (((octet >> 4) & 1 )  << 3 ) |
//         (((octet >> 5) & 1 )  << 2 ) |
//         (((octet >> 6) & 1 )  << 1 ) |
//         (((octet >> 7) & 1 )  << 0 );
        
// }
// #include <stdio.h>

// int main()
// {
//     unsigned char c = 0x41; // 0100 0001 en binario
//     printf("Resultado: %x\n", swap_bits(c)); // Esperado: 0x14
//     return 0;
// }