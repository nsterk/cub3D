/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 19:43:22 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/24 13:43:46 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

void	init_sprite(t_sprite *spr);
void	init_keys(t_keys *keys);
void	init_img(t_img *img);
void	init_tex(t_tex *tex);
void	init_mlx(t_img *img, void *mlx, void *window);
void	init_file(t_file *file);
void	init_map(t_map *map);
void	init_unsorted(t_data *data);

#endif
