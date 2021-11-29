/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:29:11 by mmondell          #+#    #+#             */
/*   Updated: 2021/11/29 13:04:27 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "parser.h"
#include "texture.h"
#include "config.h"

bool	valid_path(char *line)
{
	int32_t	fd;
	char	*file;

	if (verify_identifier(line) == 1)
		line += 2;
	file = ft_strtrim(line, " ");
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		free(file);
		return (false);
	}
	close(fd);
	free(file);
	return (true);
}

bool	valid_line(t_parser *p, char *line)
{
	if (!p->tex || !p->map)
		return (false);
	if (!valid_identifier(line))
		return (p_error("Error: Invalid Texture Identifier"));
	if (verify_identifier(line) == 2)
	{
		if (!valid_floor_ceiling(line))
			return (false);
	}
	if (verify_identifier(line) == 1)
	{
		if (!valid_file_ext(line, ".xpm"))
			return (p_error("Error: Invalid Texture Extension"));
		if (!valid_path(line))
			return (p_error("Error: Invalid Texture Path"));
	}
	return (true);
}

void	dispatch_line(t_parser *p, char *line)
{
	if (verify_identifier(line) == 1)
		p->tex = ft_strarr_extend(p->tex, line);
	else if (verify_identifier(line) == 2)
		p->rgb = ft_strarr_extend(p->rgb, line);
}

bool	read_line(t_parser *p, int32_t fd, bool skip, int limit)
{
	int32_t	ret;
	char	*line;

	ret = 1;
	while (ret && limit > 0)
	{
		ret = get_next_line(fd, &line);
		gnl_fail(p, ret);
		if (skip == false)
		{
			if (str_is_null(line))
				continue ;
			if (!valid_line(p, line))
				return (false);
			dispatch_line(p, line);
			limit--;
		}
		else if (ft_strarr_size(p->map) == 0 && str_is_null(line))
			continue ;
		else
			p->map = ft_strarr_extend(p->map, line);
	}
	return (true);
}