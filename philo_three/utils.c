/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 10:17:25 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/03 17:31:19 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	tmp_c;

	if (b == 0)
		return (0);
	ptr = (unsigned char*)b;
	tmp_c = (unsigned char)c;
	while (len--)
		*ptr++ = tmp_c;
	return (b);
}

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	j = 0;
	x = 0;
	while (dst[i] != 0)
		i++;
	while (src[j] != 0)
		j++;
	if (i < dstsize)
		j = i + j;
	else
		j = j + dstsize;
	while (src[x] != '\0' && i + 1 < dstsize)
		dst[i++] = src[x++];
	dst[i] = '\0';
	return (j);
}

int		ft_free_all(int ret)
{
	t_context	*cxt;

	cxt = ft_get_context();
	sem_post(cxt->eating);
	sem_close(cxt->eating);
	sem_post(cxt->pickup);
	sem_close(cxt->pickup);
	sem_post(cxt->forks);
	sem_close(cxt->forks);
	sem_post(cxt->print);
	sem_close(cxt->print);
	init_semlink();
	free(cxt->philosophers);
	free(cxt->pid);
	return (ret);
}
