/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:15:20 by rmaanane          #+#    #+#             */
/*   Updated: 2025/03/10 23:56:33 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_gnl(char *s, int c);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len);
char	*ft_strdup_gnl(char *str);

char	*extract_line(char *cache)
{
	char	*line;
	char	*line_pos;

	if (!cache || !*cache)
		return (NULL);
	line_pos = ft_strchr_gnl(cache, '\n');
	if (line_pos)
		line = ft_substr_gnl(cache, 0, (line_pos - cache + 1));
	else
		line = ft_strdup_gnl(cache);
	return (line);
}

char	*update_cache(char *cache)
{
	char	*line_pos;
	char	*new_cache;

	if (!cache || !*cache)
		return (NULL);
	line_pos = ft_strchr_gnl(cache, '\n');
	if (line_pos)
		new_cache = ft_strdup_gnl(line_pos + 1);
	else
		new_cache = NULL;
	free(cache);
	return (new_cache);
}

char	*fun_help(int fd, char *cache, char *buffer)
{
	ssize_t	bytes_read;

	while (!ft_strchr_gnl(cache, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(cache);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		cache = ft_strjoin_gnl(cache, buffer);
		if (!cache)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!cache)
		cache = ft_strdup_gnl("");
	cache = fun_help(fd, cache, buffer);
	if (!cache)
		return (NULL);
	if (cache && *cache)
	{
		line = extract_line(cache);
		cache = update_cache(cache);
		return (line);
	}
	free(cache);
	cache = NULL;
	return (NULL);
}
