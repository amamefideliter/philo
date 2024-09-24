/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:01:23 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/29 11:13:46 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	char			*new_st;
	unsigned int	idx;

	len = ft_strlen(s);
	new_st = malloc(len + 1);
	if (!new_st)
		return (NULL);
	idx = 0;
	while (idx < len)
	{
		new_st[idx] = (f)(idx, s[idx]);
		idx++;
	}
	new_st[idx] = '\0';
	return (new_st);
}
