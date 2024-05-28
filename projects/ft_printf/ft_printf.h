/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:09:57 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/28 02:33:57 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_flags
{
	int			hash;
	int			zero;
	int			minus;
	int			space;
	int			plus;
	int			width;
	int			precision;
	int			dot;
}				t_flags;

size_t			ft_strlen(const char *s);
int				ft_count_digits_base(unsigned long long n, int base);
int				ft_isspace(int c);
int				ft_get_value(char c, const char *base);
int				ft_get_sign(const char **str);
int				ft_putstr(char *s);
int				ft_atoi(const char *str);
int				ft_atoi_base(const char *str, const char *base);
char			*ft_utoa_base(unsigned long long n, int base, char *charset,
					t_flags flags);
char			*ft_itoa(int n, t_flags flags);
char			*ft_concat(const char *str1, const char *str2,
					int at_beginning);
char			*ft_strpad(char *str, char pad, int len, int left_align);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strdup(const char *s);
char			*ft_substr(const char *s, unsigned int start, size_t len);
unsigned long	ft_strtoul_base(const char *str, const char *base);
char			*ft_strchr(const char *s, int c);
char			*ft_strcat(char *dest, const char *src, size_t start);
char			*ft_strfill(char c, int width);
void			*ft_memset(void *s, int c, size_t n);

int				handle_number_conversion(va_list ap, int c, t_flags flags);
int				handle_pointer(va_list ap, t_flags flags);
void			handle_flag_width(char **str, t_flags flags);
void			handle_hex(char **str, char **prefix, int c, t_flags flags);
int				handle_special_cases(va_list ap, int s, t_flags flags);
void			handle_zero_precision(char **str, unsigned long value,
					t_flags flags);

int				ft_printf(const char *format, ...);
#endif
