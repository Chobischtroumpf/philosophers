/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 10:28:42 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/29 15:57:42 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

sem_t	*ft_sem_open(char const *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char	*make_semaphore_name(char const *base, char *buffer, int position)
{
	int	i;

	i = ft_strcpy(buffer, base);
	while (position > 0)
	{
		buffer[i++] = (position % 10) + '0';
		position /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}
