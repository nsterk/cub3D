/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_array.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/22 15:44:37 by nsterk        #+#    #+#                 */
/*   Updated: 2021/03/22 15:51:38 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_free_array(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str);
		i++;
	}
	free(str[i]);
	return (1);
}
