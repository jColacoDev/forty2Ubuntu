/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:29:00 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/28 02:23:57 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_strtoul_base_aux(unsigned long *result, int i, const char *str,
		const char *base)
{
	int	j;
	int	base_len;

	base_len = ft_strlen(base);
	while (str[i])
	{
		j = 0;
		while (base[j] && str[i] != base[j])
			j++;
		if (!base[j])
			break ;
		*result = *result * base_len + j;
		i++;
	}
}

unsigned long	ft_strtoul_base(const char *str, const char *base)
{
	unsigned long	result;
	int				sign;
	int				i;

	result = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = 1;
		if ((str[i] == '-'))
			sign = -1;
		i++;
	}
	ft_strtoul_base_aux(&result, i, str, base);
	return (sign * result);
}

char	*ft_concat(const char *str1, const char *str2, int at_beginning)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (result == NULL)
	{
		exit(1);
	}
	if (at_beginning)
	{
		ft_strcat(result, str2, 0);
		ft_strcat(result, str1, len2);
	}
	else
	{
		ft_strcat(result, str1, 0);
		ft_strcat(result, str2, len1);
	}
	return (result);
}

char	*ft_strfill(char c, int width)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)malloc(sizeof(char) * (width + 1));
	if (!str)
		return (NULL);
	while (++i < width)
		str[i] = c;
	str[width] = '\0';
	return (str);
}
