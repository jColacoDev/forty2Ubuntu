/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:02:43 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/28 02:28:07 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	handle_string_precision(char **str, t_flags flags)
{
	if (!*str && flags.precision < 6)
		*str = ft_strfill(' ', flags.precision);
	else if ((size_t)flags.precision < ft_strlen(*str))
		*str = ft_substr(*str, 0, flags.precision);
	else
		*str = ft_strdup(*str);
}

static int	handle_string(va_list ap, t_flags flags)
{
	char	*str;
	int		count;

	str = va_arg(ap, char *);
	if (!str)
	{
		if (flags.precision > 0 && flags.precision < 6)
			str = "";
		else
			str = "(null)";
	}
	if (flags.dot && flags.precision >= 0)
		handle_string_precision(&str, flags);
	else
		str = ft_strdup(str);
	handle_flag_width(&str, flags);
	count = ft_putstr(str);
	free(str);
	return (count);
}

static void	handle_char_minus(char *temp, int next_arg, t_flags flags)
{
	int	i;

	if (flags.minus)
	{
		temp[0] = next_arg;
		i = 1;
		while (i < flags.width && i < flags.width)
			temp[i++] = ' ';
	}
	else
	{
		i = 0;
		while (i < flags.width - 1)
			temp[i++] = ' ';
		temp[i] = next_arg;
	}
}

static int	handle_char(va_list ap, t_flags flags)
{
	int		next_arg;
	int		size;
	char	*temp;
	int		count;

	next_arg = va_arg(ap, int);
	size = 1;
	if (flags.width > 1)
		size = flags.width;
	temp = malloc(size + 1);
	if (!temp)
		return (0);
	handle_char_minus(temp, next_arg, flags);
	temp[size] = '\0';
	count = write(1, temp, size);
	free(temp);
	return (count);
}

int	handle_special_cases(va_list ap, int s, t_flags flags)
{
	int	count;

	count = 0;
	if (s == '%')
		count += write(1, "%", 1);
	else if (s == 's')
		count += handle_string(ap, flags);
	else if (s == 'c')
		count += handle_char(ap, flags);
	return (count);
}
