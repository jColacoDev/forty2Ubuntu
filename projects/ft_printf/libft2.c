/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:29:00 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/24 20:16:43 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i] != '\0')
		write(1, &(s[i++]), 1);
	return (i);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strcpy(dup, s);
	return (dup);
}

static int	ft_count_digits_base(unsigned long long n, int base)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base;
		count++;
	}
	return (count);
}

char	*ft_utoa_base(unsigned long long n, int base, char *charset, t_flags flags)
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
	else if (n == 0 )
		str[0] = charset[0];
	while (n > 0)
	{
		str[--len] = charset[n % base];
		n /= base;
	}
	return (str);
}

char *ft_itoa(int n, t_flags flags)
{
    int len;
    char *str;
    unsigned int num;

    num = (n < 0) ? -n : n; // Use absolute value of n
    len = (n == 0) ? 1 : ft_count_digits_base(num, 10);
    len += (n < 0) ? 1 : 0; // Add 1 for '-' sign if n is negative
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    str[len] = '\0';
    if (n == 0 && !flags.precision)
        str[0] = ' ';
	else if (n == 0 )
        str[0] = '0';
    while (num > 0)
    {
        str[--len] = (num % 10) + '0';
        num /= 10;
    }
    if (n < 0)
        str[0] = '-';
    return (str);
}
