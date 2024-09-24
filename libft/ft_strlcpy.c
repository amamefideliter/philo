/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:27:30 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/29 11:13:40 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	idx;
	size_t			res;

	idx = 0;
	res = ft_strlen(src);
	while (*src != '\0' && idx < (size - 1) && size != 0)
	{
		*dst++ = *src++;
		idx++;
	}
	if (size)
		*dst = '\0';
	return (res);
}
