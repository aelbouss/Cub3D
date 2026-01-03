/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:07:54 by rmaanane          #+#    #+#             */
/*   Updated: 2024/11/10 21:40:30 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*s1;
	char	*s2;
	size_t	i;
	size_t	j;
	size_t	backup;

	s1 = (char *)haystack;
	s2 = (char *)needle;
	i = 0;
	if (ft_strlen(s2) == 0)
		return (s1);
	while (s1[i] != '\0' && i < len)
	{
		backup = i;
		j = 0;
		while (s2[j] == s1[backup] && s2[j] != '\0' && backup < len)
		{
			j++;
			backup++;
		}
		if (s2[j] == '\0')
			return (&s1[i]);
		i++;
	}
	return (NULL);
}
