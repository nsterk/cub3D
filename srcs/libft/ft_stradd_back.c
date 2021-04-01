/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stradd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/01 14:54:17 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/01 15:00:36 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_stradd_back(t_list **lst, char *content)
{
	t_list	*new;
	t_list	*temp;

	if (!lst)
		return (NULL);
	new = ft_lstnew(content);
	if (!new)
		return (NULL);
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
	return (new);
}
