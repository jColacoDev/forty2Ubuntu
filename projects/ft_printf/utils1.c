/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:08:31 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/28 02:37:47 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_zero_precision(char **str, unsigned long value,
		t_flags flags)
{
	if (flags.dot && flags.precision == 0 && value == 0)
	{
		free(*str);
		*str = ft_strdup("");
	}
}

static void	handle_num_flags(char **str, t_flags flags)
{
	int	len;

	if (flags.dot && flags.precision >= 0)
	{
		len = ft_strlen(*str);
		if ((*str)[0] == '-')
			len--;
		if (len < flags.precision)
		{
			if ((*str)[0] == '-')
				*str = ft_strjoin("-", ft_strpad(ft_strdup(*str + 1), '0',
							flags.precision - len, 0));
			else
				*str = ft_strpad(*str, '0', flags.precision - len, 0);
		}
	}
	if (flags.width > 0)
		handle_flag_width(str, flags);
}

static int	handle_hex_and_pointer(va_list ap, int c, t_flags flags)
{
	int				count;
	char			*str;
	char			*base;
	char			*prefix;
	unsigned int	value;

	prefix = "";
	if (c == 'p')
		return (handle_pointer(ap, flags));
	base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	value = va_arg(ap, unsigned int);
	str = ft_utoa_base(value, 16, base, flags);
	handle_hex(&str, &prefix, c, flags);
	count = ft_putstr(str);
	free(str);
	return (count);
}

static void	handle_signed_int(va_list ap, t_flags flags, char **str,
		char **prefix)
{
	int	num;

	num = va_arg(ap, int);
	if (num == 0 && flags.dot && flags.precision == 0)
		*str = ft_strdup("");
	else
	{
		*str = ft_itoa(num, flags);
		if (flags.plus && num >= 0)
			*prefix = "+";
		else if (flags.space && num >= 0)
			*prefix = " ";
	}
}

int	handle_number_conversion(va_list ap, int c, t_flags flags)
{
	int		count;
	char	*str;
	char	*prefix;

	prefix = "";
	str = NULL;
	if (c == 'x' || c == 'X' || c == 'p')
		return (handle_hex_and_pointer(ap, c, flags));
	else if (c == 'u')
	{
		str = ft_utoa_base(va_arg(ap, unsigned int), 10, "0123456789", flags);
		handle_zero_precision(&str, ft_atoi(str), flags);
	}
	else if (c == 'd' || c == 'i')
		handle_signed_int(ap, flags, &str, &prefix);
	handle_num_flags(&str, flags);
	count = ft_putstr(prefix) + ft_putstr(str);
	free(str);
	return (count);
}
