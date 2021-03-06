/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 22:01:58 by mleblanc          #+#    #+#             */
/*   Updated: 2021/12/03 01:03:39 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "config.h"

static void	draw_circle_lines(t_buffer *buf, t_vec2 xy, t_vec2 cen, uint32_t c)
{
	draw_line(buf,
		(t_vec2){xy.x + cen.x, xy.y + cen.y},
		(t_vec2){-xy.x + cen.x, xy.y + cen.y},
		c);
	draw_line(buf,
		(t_vec2){xy.x + cen.x, -xy.y + cen.y},
		(t_vec2){-xy.x + cen.x, -xy.y + cen.y},
		c);
	draw_line(buf,
		(t_vec2){xy.y + cen.x, xy.x + cen.y},
		(t_vec2){-xy.y + cen.x, xy.x + cen.y},
		c);
	draw_line(buf,
		(t_vec2){xy.y + cen.x, -xy.x + cen.y},
		(t_vec2){-xy.y + cen.x, -xy.x + cen.y},
		c);
}

void	draw_circle(t_buffer *buf, t_vec2 center, double r, uint32_t c)
{
	int32_t	x;
	int32_t	y;
	int32_t	p;

	x = (int32_t)r;
	y = 0;
	p = 1 - (int32_t)r;
	if (r > 0.0)
		draw_line(buf, (t_vec2){(double)x + center.x, center.y},
			(t_vec2){(double)-x + center.x, center.y}, c);
	while (x > y)
	{
		y++;
		if (p <= 0)
			p += 2 * y + 1;
		else
		{
			x--;
			p += 2 * y - 2 * x + 1;
		}
		if (x < y)
			break ;
		draw_circle_lines(buf, (t_vec2){x, y}, (t_vec2){center.x, center.y}, c);
	}
}

void	draw_player(t_buffer *buf, t_player *player)
{
	t_vec2	line_end;
	t_vec2	scaled_pos;

	scaled_pos = ft_vec2_mul(player->pos, SQ_SIZE);
	draw_circle(buf, scaled_pos, 5.0, 0xFF0000);
	line_end = ft_vec2_add(scaled_pos, ft_vec2_mul(player->dir, 20.0));
	draw_line(buf, scaled_pos, line_end, 0xFF0000);
}
