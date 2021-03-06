/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 09:32:09 by mmondell          #+#    #+#             */
/*   Updated: 2021/12/18 22:38:45 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mlx.h>
#include <libft/libft.h>
#include "world.h"
#include "parser.h"

bool	free_parser(t_parser *p)
{
	if (p)
	{
		if (p->map)
			ft_strarr_free(p->map);
		if (p->tex)
			ft_strarr_free(p->tex);
		if (p->rgb)
			ft_strarr_free(p->rgb);
		free(p);
	}
	return (false);
}

size_t	find_longest_line(char **map)
{
	size_t	len;
	size_t	temp;
	size_t	i;

	i = 0;
	len = 0;
	temp = 0;
	while (map[i])
	{
		temp = ft_strlen(map[i]);
		if (temp > len)
			len = temp;
		i++;
	}
	return (len);
}

char	**allocate_sqr_map(char **map)
{
	t_string	str;
	int32_t		i;
	int32_t		diff;
	uint32_t	size;

	size = find_longest_line(map);
	i = 0;
	while (map[i])
	{
		diff = size - ft_strlen(map[i]);
		str = ft_str_new(map[i]);
		while (diff-- > 0)
			ft_str_add_back(str, MAP_OOB);
		map[i] = ft_str_take(str);
		i++;
	}
	return (map);
}
