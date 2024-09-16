/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imraoui <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:28:09 by imraoui           #+#    #+#             */
/*   Updated: 2022/05/13 08:19:17 by imraoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}
/*
int	main(void)
{
	int c = '@';
	ft_isdigit(c);
	printf("%d\n",ft_isalnum(c));
	printf("%d\n",isalnum(c));
	return(0);
}
*/
