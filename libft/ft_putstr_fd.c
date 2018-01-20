/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 15:55:15 by gvynogra          #+#    #+#             */
/*   Updated: 2017/11/06 15:56:06 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	size_t		i;

	i = 0;
	if (s && fd)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}
