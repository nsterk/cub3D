/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/12 11:58:10 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/23 16:49:51 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <structs.h>
# include <get_next_line.h>
# include <libft.h>
# include <stdio.h>

# define W		13
# define A		0
# define S		1
# define D		2
# define LEFT	123
# define RIGHT	124
# define ESC	53

void		init_data(t_data *data);

int			complete_data(t_data *data);
int			complete_img(t_status *status, t_img *img, void *mlx);
int			check_validity_path(char *str);
int			complete_sprites(t_status *status, t_sprite *spr, t_map *map);
void		position_sprites(char **map, t_d2vec *pos, int *xmax, int ymax);

/*
**	Window management.
*/
void		*start_mlx(t_data *data);

int			exit_window(t_data *data);
int			window_loop(t_data *data);

int			key_press(int keycode, t_data *data);
int			key_release(int keycode, t_data *data);

void		move_hooks(t_data *data);
void		move_up(t_data *data);
void		move_down(t_data *data);
void		move_left(t_data *data);
void		move_right(t_data *data);

void		rotate_left(t_data *data);
void		rotate_right(t_data *data);

/*
**	Parsing functions.
*/
typedef int	(*t_id)(t_data *data, char *id);
int			parsing(t_data *data);
int			parse_res(t_data *data, char *line);
int			parse_tex(t_data *data, char *line);
int			parse_sprite(t_data *data, char *line);

int			colour(t_data *data, char *line);
int			parse_colour(t_status *status, int *colour, char *line);
int			ready_for_map(t_data *data);
int			str_array_size(char **str);
int			validate_res(t_data *data, char *line);
int			get_largest_number(int *x, int y);
int			parse_map(t_data *data, int fd);
int			read_map(t_data *data, int fd);
int			copy_map(t_list *list, t_data *data);
int			get_map_info(t_data *data);
int			get_spawn_info(t_data *data, int y);
void		set_spawn_dir(char c, t_d2vec *dir, t_d2vec *plane);
int			validate_map(t_data *data);
int			allocate_check(t_status *status, t_map *map);
int			copy_to_check(t_map *map);
void		floodfill(t_status *status, int y, int x, t_map *map);

/*
**	Raycasting.
*/

void		raycaster(t_data *data, int x);
void		calc_step_distance(t_d2vec pos, t_ray *ray);
void		differential_analysis(t_data *data);
void		calc_line(t_d2vec pos, t_i2vec res, t_ray *ray);

void		calc_texture(t_data *data, int i);
void		put_texture(t_data *data, int x, int i);

int			draw_sprites(t_data *data);
void		sort_sprites(t_sprite *spr);
void		calculate_sprite(t_data *data, int i);
void		put_sprite(t_sprite *spr, t_i2vec res, double *z_buf, t_img *img);
void		put_pixel_sprite(t_sprite *spr, int res_y, t_img *mlx_img, int y);

/*
**	Utils.
*/

int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			create_trgb(int t, int r, int g, int b);
t_colour	get_colour(t_sprite *spr);
void		apply_shade(t_sprite *spr, t_colour *colour);

void		free_str_array(char **str, int len);
void		close_free(t_data *data);
void		free_parse(t_data *data);

int			create_bmp(t_i2vec res, t_img *img);
void		put_pixel(int x, int y, int colour, t_img *img);

char		first_char(char *str);
int			is_space(char *s);
int			set_status(t_status *status, t_status num);
#endif