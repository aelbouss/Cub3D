/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:27:49 by rmaanane          #+#    #+#             */
/*   Updated: 2024/11/13 04:07:25 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*destination;
	char	*source;

	destination = (char *)dst;
	source = (char *)src;
	if (destination == NULL && source == NULL)
		return (NULL);
	if (destination == source || len == 0)
		return (dst);
	if (destination > source)
	{
		while (len > 0)
		{
			len--;
			destination[len] = source[len];
		}
	}
	else if (destination < source)
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
