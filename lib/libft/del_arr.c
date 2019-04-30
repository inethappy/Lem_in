/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:26:01 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/04/24 16:26:03 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void del_arr(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}