/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:29:00 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/28 00:14:23 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem_byte;

	mem_byte = s;
	i = 0;
	while (i < n)
		mem_byte[i++] = (unsigned char)c;
	return (s);
}

void	ft_strtoul_base_aux(unsigned long *result, int i,
		const char *str, const char *base)
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

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static int	ft_get_value(char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *str, const char *base)
{
	int	result;
	int	sign;
	int	base_len;
	int	i;
	int	value;

	result = 0;
	sign = 1;
	base_len = ft_strlen(base);
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i])
	{
		value = ft_get_value(str[i], base);
		if (value == -1)
			break ;
		result = result * base_len + value;
		i++;
	}
	return (sign * result);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_concat(const char *str1, const char *str2, int at_beginning)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = 0;
	len2 = 0;
	while (str1[len1] != '\0')
		len1++;
	while (str2[len2] != '\0')
		len2++;
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (result == NULL)
	{
		exit(1);
	}
	if (at_beginning)
	{
		for (size_t i = 0; i < len2; i++)
		{
			result[i] = str2[i];
		}
		for (size_t i = 0; i < len1; i++)
		{
			result[i + len2] = str1[i];
		}
		result[len1 + len2] = '\0';
	}
	else
	{
		for (size_t i = 0; i < len1; i++)
		{
			result[i] = str1[i];
		}
		for (size_t i = 0; i < len2; i++)
		{
			result[i + len1] = str2[i];
		}
		result[len1 + len2] = '\0';
	}
	return (result);
}

char	*ft_itoa_aux(char *str, int *len, int n, t_flags flags)
{
	unsigned int	num;

	num = n;
	if (n < 0)
		num = -n;
	if (n == 0 && !flags.precision)
		str[0] = ' ';
	else if (n == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--(*len)] = (num % 10) + '0';
		num /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
char	*ft_itoa(int n, t_flags flags)
{
	int				len;
	char			*str;
	unsigned int	num;

	num = n;
	if (n < 0)
		num = -n;
	len = ft_count_digits_base(num, 10);
	if (n == 0)
		len = 1;
	else if (n < 0)
		len += 1;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	ft_itoa_aux(str, &len, n, flags);
	return (str);
}
