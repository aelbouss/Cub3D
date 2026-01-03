/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 13:45:41 by aelbouss          #+#    #+#             */
/*   Updated: 2025/09/19 03:36:17 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*join_strs(char *s1, char *s2, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			res[j++] = s1[i++];
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			res[j++] = s2[i++];
	}
	res[j] = '\0';
	return (res);
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;
	int		s1_len;
	int		s2_len;

	s1_len = 0;
	s2_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	if (s2)
		s2_len = ft_strlen(s2);
	result = malloc(s1_len + s2_len + 1);
	if (!result)
		return (NULL);
	result = join_strs(s1, s2, result);
	if (s1)
		free(s1);
	return (result);
}

static char	*read_buffer(int fd, char *storage)
{
	char	*buffer;
	int		br;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE * sizeof(char)) + 1);
	if (!buffer)
		return (NULL);
	br = 1;
	while (!loking_for_newline(storage) && br > 0)
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br == 0)
			break ;
		if (br < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[br] = '\0';
		storage = join_and_free(storage, buffer);
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	char		*holder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_buffer(fd, storage);
	if (!storage)
		return (NULL);
	line = elicit_line(storage);
	holder = get_remaining(storage);
	free(storage);
	storage = holder;
	return (line);
}
