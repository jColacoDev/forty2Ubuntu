/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:48:11 by joao-rde          #+#    #+#             */
/*   Updated: 2024/06/05 17:27:14 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert(va_list ap, int s, t_flags flags)
{
	int	count;

	if (s == '%' || s == 's' || s == 'c')
		count = handle_special_cases(ap, s, flags);
	else
		count = handle_number_conversion(ap, s, flags);
	return (count);
}

static t_flags	flags_init(t_flags flags)
{
	flags.hash = 0;
	flags.zero = 0;
	flags.minus = 0;
	flags.space = 0;
	flags.plus = 0;
	flags.width = 0;
	flags.precision = -1;
	flags.dot = 0;
	return (flags);
}

static t_flags	parse_flags_width_precision(const char **format, t_flags flags)
{
	if (**format >= '0' && **format <= '9')
		flags.width = ft_atoi(*format);
	while (**format >= '0' && **format <= '9')
		(*format)++;
	if (**format == '.')
	{
		flags.dot = 1;
		(*format)++;
		flags.precision = ft_atoi(*format);
		while (**format >= '0' && **format <= '9')
			(*format)++;
	}
	return (flags);
}

static t_flags	parse_flags(const char **format)
{
	t_flags	flags;

	flags = flags_init(flags);
	while (**format == '#' || **format == '0' || **format == '-'
		|| **format == ' ' || **format == '+')
	{
		if (**format == '#')
			flags.hash = 1;
		else if (**format == '0')
			flags.zero = 1;
		else if (**format == '-')
			flags.minus = 1;
		else if (**format == ' ')
			flags.space = 1;
		else if (**format == '+')
			flags.plus = 1;
		(*format)++;
	}
	return (parse_flags_width_precision(format, flags));
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	t_flags	flags;

	count = 0;
	va_start(ap, format);
	if (!format || !*format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			flags = parse_flags(&format);
			count += convert(ap, *format, flags);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
