/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 03:06:02 by rmaanane          #+#    #+#             */
/*   Updated: 2024/11/13 03:59:40 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_itoa(int n)
{
	int		len;
	long	nb;

	len = 0;
	nb = n;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb = -nb;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

static void	ft_nbplus(char *result, long nb, int len)
{
	while (nb > 0)
	{
		len--;
		result[len] = (nb % 10) + '0';
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	nb;

	nb = n;
	len = len_itoa(n);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nb == 0)
	{
		result[0] = '0';
		return (result);
	}
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	ft_nbplus(result, nb, len);
	return (result);
}
