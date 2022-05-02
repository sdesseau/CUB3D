/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdesseau <sdesseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:16:26 by sdesseau          #+#    #+#             */
/*   Updated: 2022/05/02 17:35:31 by sdesseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include "mlx_linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>

# define HEIGHT 1440
# define WIDTH 900

typedef struct	s_win {
	void *mlx;
	void *mlx_win;
}	t_win;

typedef struct s_img{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_color {
	int	color;
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_data {	
	t_img		img;
	int			mouse_x;
	int			mouse_y;
	t_win		win;
	int			y;
	int			x;
	int			max;
	int			lastx;
	int			lasty;
	int			r;
	int			g;
	int			b;
	char		*name;
	t_color color;
}	t_data;


int main(int argc, char **argv);

#endif