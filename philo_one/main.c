/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:26:35 by adorigo           #+#    #+#             */
/*   Updated: 2020/08/04 10:46:41 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *Philosopher(void *threadid)
{
	
}

int main (int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return(1);
	}
	if (initcontext(argc, argv))
	
}