/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:51:29 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/29 11:13:16 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*res;

	res = NULL;
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
		{
			res = (char *)s;
			return (res);
		}
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		res = (char *)s;
	return (res);
}
