/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 15:17:02 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/27 15:47:14 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;

	i = 0;
	if (lst)
	{
		while (lst)
		{
			lst = lst->next;
			i++;
		}
	}
	return (i);
}
