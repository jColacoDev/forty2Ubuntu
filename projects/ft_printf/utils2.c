/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:38:29 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/22 16:51:44 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void	handle_num_flags(char **str, t_flags flags)
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

// int main(){

// 	printf("%#.X\n", 0xee);
// 	ft_printf("%#.X\n", 0xee);

// 	return 0;
// }