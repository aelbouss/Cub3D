/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:07:59 by rmaanane          #+#    #+#             */
/*   Updated: 2024/11/09 13:06:48 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		j;

	str = (char *)s;
	j = ft_strlen(str);
	while (j >= 0)
	{
		if ((char)c == str[j])
			return (&str[j]);
		j--;
	}
	return (NULL);
}
