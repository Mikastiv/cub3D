/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:50:59 by mleblanc          #+#    #+#             */
/*   Updated: 2021/11/10 22:11:45 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "event.h"

int	main(void)
{
	void		*mlx;
	void		*win;
	t_game		game;

	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "cub3D");
	init_game(&game, mlx, win);
	mlx_do_key_autorepeatoff(mlx);
	mlx_hook(win, 2, 1, &keydown, &game);
	mlx_hook(win, 3, 2, &keyup, &game);
	mlx_hook(win, 17, 0, &quit_game, &game);
	mlx_loop_hook(mlx, &update, &game);
	mlx_loop(mlx);
}
