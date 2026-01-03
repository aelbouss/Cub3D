/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:15:26 by rmaanane          #+#    #+#             */
/*   Updated: 2025/03/03 16:53:43 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *str, int c)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if ((char)c == str[i])
			return (&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&str[i]);
	return (NULL);
}

char	*ft_strdup_gnl(char *str)
{
	size_t	i;
	char	*result;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen_gnl(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	result = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen_gnl(s);
	if (s_len <= start)
		return (ft_strdup_gnl(""));
	sub_len = s_len - start;
	if (sub_len > len)
		sub_len = len;
	substr = malloc(sizeof(char) * (sub_len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < sub_len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
