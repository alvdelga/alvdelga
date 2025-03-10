/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvdelga <alvdelga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:01:44 by alvdelga          #+#    #+#             */
/*   Updated: 2025/03/10 14:09:26 by alvdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_list
{
    struct s_list *next;
    void          *data;
} t_list;

int	ft_list_size(t_list *begin_list)
{
    int i;

    i = 0;
    while(begin_list)
    {
        begin_list = begin_list->next;
        i++;
    }
    return (i);
}

