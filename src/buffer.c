/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 00:19:04 by mleblanc          #+#    #+#             */
/*   Updated: 2021/12/03 04:44:34 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include <libft/libft.h>
#include <mlx.h>
#include <stdint.h>
#include <stdlib.h>

t_buffer	*new_buffer(void *mlx, int32_t w, int32_t h)
{
	t_buffer	*b;

	b = ft_calloc(1, sizeof(t_buffer));
	b->w = w;
	b->h = h;
	b->img = mlx_new_image(mlx, w, h);
	b->data = mlx_get_data_addr(b->img, &b->bpp, &b->pitch, &b->endian);
	return (b);
}

void	destroy_buffer(void *mlx, t_buffer *buf)
{
	mlx_destroy_image(mlx, buf->img);
	free(buf);
}

void	put_pixel(t_buffer *buf, int32_t x, int32_t y, uint32_t c)
{
	char	*dst;

	if (x < 0 || x >= buf->w)
		return ;
	if (y < 0 || y >= buf->h)
		return ;
	dst = buf->data + (y * buf->pitch + x * (buf->bpp / 8));
	*(uint32_t *)dst = c;
}

void	clear_buffer(t_buffer *buf, uint32_t c)
{
	int32_t	x;
	int32_t	y;

	y = 0;
	while (y < buf->h)
	{
		x = 0;
		while (x < buf->w)
		{
			put_pixel(buf, x, y, c);
			x++;
		}
		y++;
	}
}
