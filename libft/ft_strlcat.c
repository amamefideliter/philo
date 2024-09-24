/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:42:20 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/29 11:13:33 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t a, size_t b);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t					res;
	size_t					dest_len;
	size_t					src_len;
	unsigned long int		space;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	space = (unsigned long int)size - dest_len;
	res = src_len + dest_len;
	if (size < dest_len)
		return (min(res, size + src_len));
	dst += dest_len;
	while (*src && space > 1)
	{
		*dst++ = *src++;
		space--;
	}
	*dst = '\0';
	res = src_len + dest_len;
	return (res);
}

static size_t	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
