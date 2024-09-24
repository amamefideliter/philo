/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:21:45 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/29 11:12:38 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*chs1;
	char	*chs2;

	chs1 = (char *)s1;
	chs2 = (char *)s2;
	while (n--)
	{
		if ((unsigned char)*chs1 > (unsigned char)*chs2)
			return (1);
		else if ((unsigned char)*chs1 < (unsigned char)*chs2)
			return (-1);
		chs1++;
		chs2++;
	}
	return (0);
}
