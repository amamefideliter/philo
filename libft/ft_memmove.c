/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:24:21 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/29 11:12:45 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*res;
	char	tmp[1024];
	size_t	idx;
	char	*chsrc;
	char	*chdest;

	if (!src && !dest)
		return (NULL);
	if (n > 1024)
		return (dest);
	res = dest;
	idx = 0;
	chdest = (char *)dest;
	chsrc = (char *)src;
	while (idx < n)
	{
		tmp[idx] = *chsrc++;
		idx++;
	}
	idx = 0;
	while (idx < n)
		*chdest++ = tmp[idx++];
	return (res);
}
