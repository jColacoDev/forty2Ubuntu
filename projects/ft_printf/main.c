/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rde <joao-rde@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:58:48 by joao-rde          #+#    #+#             */
/*   Updated: 2024/06/05 17:36:00 by joao-rde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	int	aux;
	int	aux2;

	aux = ft_printf("%c", (char)0);
	printf("%d\n", aux);
	printf("%d\n", aux2);
	return (0);
}
