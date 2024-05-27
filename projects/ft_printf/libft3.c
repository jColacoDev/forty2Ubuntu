/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:29:00 by joao-rde          #+#    #+#             */
/*   Updated: 2024/05/21 19:03:14 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem_byte;

	mem_byte = s;
	i = 0;
	while (i < n)
		mem_byte[i++] = (unsigned char)c;
	return (s);
}


unsigned long ft_strtoul_base(const char *str, const char *base)
{
    unsigned long result = 0;
    int base_len = ft_strlen(base);
    int sign = 1;
    int i = 0;

    // Handle leading whitespace
    while (ft_isspace(str[i]))
        i++;

    // Handle sign
    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i] == '-') ? -1 : 1;
        i++;
    }

    // Calculate result
    while (str[i]) {
        int j = 0;
        while (base[j] && str[i] != base[j])
            j++;
        if (!base[j])
            break;
        result = result * base_len + j;
        i++;
    }

    return sign * result;
}

int ft_isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n'
            || c == '\v' || c == '\f' || c == '\r');
}

static int ft_get_value(char c, const char *base)
{
    int i = 0;
    while (base[i])
    {
        if (base[i] == c)
            return i;
        i++;
    }
    return -1; // Return -1 for invalid characters
}

int ft_atoi_base(const char *str, const char *base)
{
    int result = 0;
    int sign = 1;
    int base_len = ft_strlen(base);
    int i = 0;

    // Handle leading whitespace
    while (ft_isspace(str[i]))
        i++;

    // Handle sign
    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i] == '-') ? -1 : 1;
        i++;
    }

    // Calculate result
    while (str[i]) {
        int value = ft_get_value(str[i], base);
        if (value == -1)
            break; // Invalid character, stop parsing
        result = result * base_len + value;
        i++;
    }

    return sign * result;
}

char *ft_strchr(const char *s, int c) 
{
    while (*s != '\0') {
        if (*s == (char)c) {
            return (char *)s;
        }
        s++;
    }
    if (c == '\0') {
        return (char *)s;
    }
    return NULL;
}


char *ft_concat(const char *str1, const char *str2, int at_beginning)
{
    size_t len1 = 0, len2 = 0;
    while (str1[len1] != '\0') len1++;
    while (str2[len2] != '\0') len2++;

    // Allocate memory for concatenated string
    char *result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
    if (result == NULL) {
        // fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Concatenate strings
    if (at_beginning) {
        // Copy str2 followed by str1
        for (size_t i = 0; i < len2; i++) {
            result[i] = str2[i];
        }
        for (size_t i = 0; i < len1; i++) {
            result[i + len2] = str1[i];
        }
        result[len1 + len2] = '\0'; // Null-terminate the string
    } else {
        // Copy str1 followed by str2
        for (size_t i = 0; i < len1; i++) {
            result[i] = str1[i];
        }
        for (size_t i = 0; i < len2; i++) {
            result[i + len1] = str2[i];
        }
        result[len1 + len2] = '\0'; // Null-terminate the string
    }

    return result;
}