/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 03:47:20 by adorigo           #+#    #+#             */
/*   Updated: 2020/12/03 21:02:47 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	format_error(char *arg, int ret)
{
	ft_putstr_fd("Invalide format of argument :", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}

int	amount_arg_error(int ret)
{
	ft_putstr_fd("invalid amount of arguments", 2);
	return (ret);
}

int	error_ret(char *str, int ret)
{
	ft_putstr_fd(str, 2);
}