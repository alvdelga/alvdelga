/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 07:15:07 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/08 07:15:10 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define M 8
#define N 8

void floodFill(int pantalla[M][N], int x, int y, int prevColor, int newColor) {
    if (x < 0 || x >= M || y < 0 || y >= N)
        return;
    if (pantalla[x][y] != prevColor)
        return;

    pantalla[x][y] = newColor;

    floodFill(pantalla, x+1, y, prevColor, newColor);
    floodFill(pantalla, x-1, y, prevColor, newColor);
    floodFill(pantalla, x, y+1, prevColor, newColor);
    floodFill(pantalla, x, y-1, prevColor, newColor);
}

void imprimirPantalla(int pantalla[M][N]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", pantalla[i][j]);
        printf("\n");
    }
}

int main() {
    int pantalla[M][N] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 0, 0},
        {1, 0, 0, 1, 1, 0, 1, 1},
        {1, 2, 2, 2, 2, 0, 1, 0},
        {1, 1, 1, 2, 2, 0, 1, 0},
        {1, 1, 1, 2, 2, 2, 2, 0},
        {1, 1, 1, 1, 1, 2, 1, 1},
        {1, 1, 1, 1, 1, 2, 2, 1}
    };

    int x = 4, y = 4, newColor = 3;
    int prevColor = pantalla[x][y];

    printf("Pantalla original:\n");
    imprimirPantalla(pantalla);

    floodFill(pantalla, x, y, prevColor, newColor);

    printf("\nPantalla tras Flood Fill:\n");
    imprimirPantalla(pantalla);

    return 0;
}