/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:03:13 by rmaanane          #+#    #+#             */
/*   Updated: 2024/11/13 04:11:45 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*temp;
	size_t			total_size;

	if (count > 0 && size > SIZE_MAX / count)
		return (NULL);
	total_size = count * size;
	temp = malloc(total_size);
	if (temp == NULL)
		return (NULL);
	ft_memset(temp, 0, total_size);
	return ((void *)temp);
}
