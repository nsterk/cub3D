/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/03 15:35:22 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/31 16:37:30 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = ft_lstlast(*lst);
		current->next = new;
	}
}
/*
void	*ft_lstadd_back(t_list **lst, char *content)
{
	t_list	*new;
	t_list	*temp;

	if (!lst)
		return ;
	new = ft_lstnew(content);
	if (!temp)
		return (NULL);
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
}
*/
