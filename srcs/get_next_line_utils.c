/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:45:35 by aelbouss          #+#    #+#             */
/*   Updated: 2025/09/19 03:36:09 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	loking_for_newline(const char *str)
{
	int	idx;

	if (!str)
		return (0);
	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '\n')
			return (1);
		idx++;
	}
	return (0);
}

char	*elicit_line(char *str)
{
	char	*buff;
	int		i;

	if (!str || !*str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	buff = malloc(i + 1);
	if (!buff)
		return (NULL);
	buff[i] = '\0';
	while (i--)
		buff[i] = str[i];
	return (buff);
}

char	*copy_remaining(char *str, int i)
{
	char	*remainder;
	int		rem_len;
	int		j;

	rem_len = 0;
	if (str[i])
		rem_len = ft_strlen(&str[i]);
	remainder = malloc(rem_len + 1);
	if (!remainder)
		return (NULL);
	j = 0;
	while (str[i])
		remainder[j++] = str[i++];
	remainder[j] = '\0';
	return (remainder);
}

char	*get_remaining(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while ((str[i] && str[i] != '\0') && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (!str[i])
		return (NULL);
	return (copy_remaining(str, i));
}
