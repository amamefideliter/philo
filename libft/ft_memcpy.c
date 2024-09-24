/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:26:06 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/29 11:12:41 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;
	void		*res;

	if (!dest && !src)
		return (NULL);
	cdest = (char *)dest;
	csrc = (const char *)src;
	res = cdest;
	while (n--)
	{
		*cdest = *csrc;
		cdest++;
		csrc++;
	}
	return (res);
}
