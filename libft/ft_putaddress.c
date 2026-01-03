/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <rmaanane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:33:23 by rmaanane          #+#    #+#             */
/*   Updated: 2025/03/07 22:23:55 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_adress(unsigned long nb)
{
	int		count;
	char	*base;

	count = 0;
	base = "0123456789abcdef";
	if (nb >= 16)
		count += ft_adress(nb / 16);
	count += write(1, &base[nb % 16], 1);
	return (count);
}

int	ft_ptrhandler(unsigned long nb)
{
	int	count;

	count = 0;
	if (!nb)
		return (write(1, "(nil)", 5));
	count += write(1, "0x", 2);
	count += ft_adress(nb);
	return (count);
}
