/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:08:31 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/24 20:19:34 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
static void handle_zero_precision(char **str, unsigned long value, t_flags flags)
{
    if (flags.dot && flags.precision == 0 && value == 0)
    {
        free(*str);
        *str = ft_strdup("");
    }
}

static void handle_hex(char **str, char **prefix, int c, t_flags flags)
{
    unsigned long value = 0;
    int is_hex = 1;
    int i = -1;

	printf("string0:[%s]\n", *str);
    // Check if the input string is in hexadecimal format
    while ((*str)[++i] != '\0') {
        if (!ft_strchr("0123456789abcdefABCDEF", (*str)[i])) {
            is_hex = 0;
            break;
        }
    }

    // Handle zero precision
    if (!is_hex) {
        value = ft_atoi_base(*str, "0123456789abcdef");
        handle_zero_precision(str, value, flags);
    }

    if (flags.hash && **str != '0' && **str != '\0')
    {
        *prefix = "0x";
        if (c == 'X')
            *prefix = "0X";
    }
    if (flags.dot && flags.precision > 0)
    {
        int len = ft_strlen(*str);
        if (len < flags.precision)
            *str = ft_strpad(*str, '0', flags.precision - len, 0);
    }

	printf("string1:[%s]\n", *str);

    if (flags.width > 0)
        handle_flag_width(str, *prefix, flags);
    else
		ft_strjoin((const char *)(prefix), (const char *)(*str));
	printf("string2:[%s]\n", *str);
    
}

static int handle_pointer_width(char *full_str, t_flags flags)
{
    int padding_len;
    int count;
    char *padded_str;

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

static int handle_pointer(va_list ap, t_flags flags)
{
    int count;
    char *str;
    char *full_str;
    unsigned long ptr;

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

static int handle_hex_and_pointer(va_list ap, int c, t_flags flags)
{
    int count;
    char *str;
    char *base;
    char *prefix;

    prefix = "";
    if (c == 'p')
        return (handle_pointer(ap, flags));
    base = "0123456789abcdef";
    if (c == 'X')
        base = "0123456789ABCDEF";
    unsigned int value = va_arg(ap, unsigned int);
    str = ft_utoa_base(value, 16, base, flags);
    handle_hex(&str, &prefix, c, flags);
    count = ft_putstr(str);
    free(str);
    return (count);
}

char *ft_strfill(char c, int width)
{
    char *str;

    str = (char *)malloc(sizeof(char) * (width + 1));
    if (!str)
        return (NULL);
    for (int i = 0; i < width; ++i)
        str[i] = c;
    str[width] = '\0';
    return (str);
}

int handle_number_conversion(va_list ap, int c, t_flags flags)
{
    int count;
    char *str;
    char *prefix;
    int num;

    prefix = "";
    count = 0;
    str = NULL;
    if (c == 'x' || c == 'X' || c == 'p')
        return (handle_hex_and_pointer(ap, c, flags));
    else if (c == 'u')
    {
        str = ft_utoa_base(va_arg(ap, unsigned int), 10, "0123456789", flags);
        handle_zero_precision(&str, (int)ft_atoi(str), flags);
    }
    else if (c == 'd' || c == 'i')
    {
        num = va_arg(ap, int);
        if (num == 0 && flags.dot && flags.precision == 0)
        {
            str = ft_strdup("");
        }
        else
        {
            str = ft_itoa(num, flags);
            if (flags.plus && num >= 0)
                prefix = "+";
            else if (flags.space && num >= 0)
                prefix = " ";
        }
    }
    handle_num_flags(&str, prefix, flags);
    count = ft_putstr(prefix) + ft_putstr(str);
    free(str);
    return (count);
}
