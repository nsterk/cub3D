/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <marvin@codam.nl>                     +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 09:36:19 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/01 19:53:56 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strccpy(char *dest, const char *src, char c)
{
	int	i;

	i = 0;
	while (*src != '\0')
	{
		if (*src != c)
		{
			dest[i] = *src;
			i++;
		}
		src++;
	}
	dest[i] = '\0';
	return (dest);
}
