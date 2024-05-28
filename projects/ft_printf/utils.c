/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:08:31 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/28 02:25:47 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_pointer_width(char *full_str, t_flags flags)
{
	int		padding_len;
	int		count;
	char	*padded_str;

	padding_len = flags.width - ft_strlen(full_str);
	padded_str = malloc(flags.width + 1);
	if (!padded_str)
	{
		free(full_str);
		return (0);
	}
	if (flags.minus)
	{
		ft_strcpy(padded_str, full_str);
		ft_memset(padded_str + ft_strlen(full_str), ' ', padding_len);
	}
	else
	{
		ft_memset(padded_str, ' ', padding_len);
		ft_strcpy(padded_str + padding_len, full_str);
	}
	padded_str[flags.width] = '\0';
	count = ft_putstr(padded_str);
	free(padded_str);
	return (count);
}

int	handle_pointer(va_list ap, t_flags flags)
{
	int				count;
	char			*str;
	char			*full_str;
	unsigned long	ptr;

	count = 0;
	ptr = va_arg(ap, unsigned long);
	if (ptr == 0)
		full_str = ft_strdup("(nil)");
	else
	{
		str = ft_utoa_base(ptr, 16, "0123456789abcdef", flags);
		full_str = ft_strjoin("0x", str);
		free(str);
	}
	if (flags.width > (int)ft_strlen(full_str))
		count = handle_pointer_width(full_str, flags);
	else
		count = ft_putstr(full_str);
	free(full_str);
	return (count);
}

static void	handle_flag_width_aux(char **str, char pad_char, int len,
		t_flags flags)
{
	char	*new_str;

	if (flags.minus)
		*str = ft_strpad(*str, pad_char, flags.width - len, 1);
	else if (pad_char == '0' && **str == '-')
	{
		new_str = malloc(flags.width + 1);
		if (!new_str)
			return ;
		new_str[0] = '-';
		ft_memset(new_str + 1, '0', flags.width - len);
		ft_strcpy(new_str + flags.width - len + 1, *str + 1);
		free(*str);
		*str = new_str;
	}
	else
		*str = ft_strpad(*str, pad_char, flags.width - len, 0);
}

void	handle_flag_width(char **str, t_flags flags)
{
	char	pad_char;
	int		len;

	len = ft_strlen(*str);
	pad_char = ' ';
	if (flags.zero && !flags.minus && !flags.dot)
		pad_char = '0';
	if (len < flags.width)
		handle_flag_width_aux(str, pad_char, len, flags);
}
