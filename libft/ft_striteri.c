/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:27:53 by dzubkova          #+#    #+#             */
/*   Updated: 2024/05/29 11:13:23 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	idx;
	unsigned int	len;

	idx = 0;
	len = ft_strlen(s);
	while (idx < len)
	{
		(f)(idx, &s[idx]);
		idx++;
	}
}
