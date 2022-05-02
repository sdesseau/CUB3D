/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdesseau <sdesseau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:33:27 by sdesseau          #+#    #+#             */
/*   Updated: 2022/05/02 17:39:48 by sdesseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int     init(t_data *data)
{
        data->win.mlx = mlx_init();
        if (data->win.mlx == 0)
                return (0);
        data->win.mlx_win = mlx_new_window(data->win.mlx, HEIGHT, WIDTH, "CUB3D");
        if (data->win.mlx_win == 0)
        {
                free(data->win.mlx);
                return (0);
        }
        data->img.img = mlx_new_image(data->win.mlx, HEIGHT, WIDTH);
        if (data->img.img == 0)
                mlx_destroy_image(data->win.mlx_win, data->img.img);
        data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
                        &data->img.line_length, &data->img.endian);
        return (1);
}

int     ft_close(t_data *data)
{
        printf("ft_close\n");
        if (data->win.mlx != 0)
                mlx_destroy_window(data->win.mlx, data->win.mlx_win);
        exit(0);
        return (0);
}

int     encode_rgb(int red, int green, int blue)
{
        return (red << 16 | green << 8 | (blue & 0xFF));
}

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
        char    *dst;

        dst = data->img.addr + (y * data->img.line_length
                        + x * (data->img.bits_per_pixel / 8));
        *(unsigned int *)dst = color;
}

int	key_hook(int keycode, t_data *data)
{
        printf("keyhook >> %i\n", keycode);
        if (keycode == 65307)
                ft_close(data);
}

int     hook_expose(t_data *data)
{
        int x = 0;
        int y = 0;
        
        while (y < WIDTH)
        {
                x = 0;
                while (x < HEIGHT)
                {
                        data->color.g = data->g * x % 256;
	                data->color.r = data->r * x % 256;
	                data->color.b = data->b * x % 256;
                        data->color.color = encode_rgb(data->color.r, data->color.g, data->color.b);
                        my_mlx_pixel_put(data, x, y, data->color.color);
                        x++;
                }
                y++;
        }
        mlx_put_image_to_window(data->win.mlx, data->win.mlx_win, data->img.img, 0, 0); 
}

int     main(int argc, char **argv)
{
        t_data  data;

        if (init(&data) == 0)
        {
                write(1, "Error : mlx error\n", 17);
                return (1);
        }
        mlx_loop_hook(data.win.mlx, hook_expose, &data);
	mlx_hook(data.win.mlx_win, 17, 0L, ft_close, &data);
        mlx_key_hook(data.win.mlx_win, key_hook, &data);
	mlx_loop(data.win.mlx);
        return (0);
}