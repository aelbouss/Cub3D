/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:54:32 by rmaanane          #+#    #+#             */
/*   Updated: 2024/11/13 04:00:45 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	size_src;
	size_t	size_dest;
	size_t	i;
	size_t	j;

	size_src = ft_strlen(src);
	size_dest = ft_strlen(dst);
	if (dstsize == 0 || size_dest >= dstsize)
		return (dstsize + size_src);
	i = 0;
	j = size_dest;
	while (src[i] && j < dstsize - 1)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (size_src + size_dest);
}
