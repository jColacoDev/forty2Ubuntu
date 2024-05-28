/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:32:51 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/28 00:25:55 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
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

char	*ft_strpad(char *str, char pad, int len, int left_align)
{
	int		orig_len;
	char	*new_str;
	int		i;

	orig_len = ft_strlen(str);
	new_str = malloc(len + orig_len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	if (left_align)
	{
		ft_strcpy(new_str, str);
		while (i < len)
			new_str[orig_len + i++] = pad;
	}
	else
	{
		while (i < len)
			new_str[i++] = pad;
		ft_strcpy(new_str + i, str);
	}
	new_str[orig_len + len] = '\0';
	free(str);
	return (new_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_strcpy(joined, s1);
	ft_strcpy(joined + len1, s2);
	return (joined);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
