/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:29:00 by joao-rde          #+#    #+#             */
/*   Updated: 2024/06/05 17:27:30 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_itoa_aux(char *str, int *len, int n, t_flags flags)
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

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

char	*ft_utoa_base(unsigned long long n, int base, char *charset,
		t_flags flags)
{
	int		len;
	char	*str;

	if (base < 2)
		return (NULL);
	len = ft_count_digits_base(n, base);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n == 0 && !flags.precision)
		str[0] = ' ';
	else if (n == 0)
		str[0] = charset[0];
	while (n > 0)
	{
		str[--len] = charset[n % base];
		n /= base;
	}
	return (str);
}

int	ft_atoi_base(const char *str, const char *base)
{
	int	result;
	int	sign;
	int	base_len;
	int	value;

	result = 0;
	base_len = ft_strlen(base);
	while (ft_isspace(*str))
	{
		str++;
	}
	sign = ft_get_sign(&str);
	while (*str)
	{
		value = ft_get_value(*str, base);
		if (value == -1)
		{
			break ;
		}
		result = result * base_len + value;
		str++;
	}
	return (sign * result);
}
