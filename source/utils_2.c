/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mromao-d <mromao-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 14:14:58 by mromao-d          #+#    #+#             */
/*   Updated: 2024/02/11 14:20:39 by mromao-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*output;

	output = malloc(sizeof(char) * (nmemb * size));
	if (output == NULL)
		return (NULL);
	ft_bzero (output, nmemb * size);
	return (output);
}

// prints error. returns 1
int	th_error(char *log, char *funct)
{
	printf("%s on function %s\n", log, funct);
	return (1);
}
