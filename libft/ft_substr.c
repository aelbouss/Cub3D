/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:08:11 by rmaanane          #+#    #+#             */
/*   Updated: 2024/11/13 04:01:09 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	char	*substr;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	sub_len = s_len - start;
	if (sub_len > len)
		sub_len = len;
	substr = malloc(sizeof(char) * (sub_len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < sub_len)
	{
		substr[i++] = s[start++];
	}
	substr[i] = '\0';
	return (substr);
}
