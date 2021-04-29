/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 19:18:46 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/29 19:43:40 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <unistd.h>
# include <sys/uio.h>
# include <fcntl.h>

typedef struct s_bmp_h
{
	char			type[2];
	unsigned int	file_size;
	unsigned int	na;
	unsigned int	offset;
}				t_bmp_h;

typedef struct s_dib_h
{
	unsigned int		header_size;
	int					width;
	int					height;
	unsigned short int	colourplanes;
	unsigned short int	bpp;
	unsigned int		compression;
	unsigned int		img_size;
	int					res_x;
	int					res_y;
	unsigned int		nr_clrs;
	unsigned int		nr_important_clrs;

}				t_dib_h;

typedef struct	s_bmp_extra
{
	int			fd;
	int			pad_size;
	char		*padding;
}				t_bmp_extra;

int			create_bmp(t_i2vec res, t_img *img);
void		fill_dib_header(t_dib_h *dib, t_img *img, t_i2vec res);
void		fill_file_header(t_file_h *header, t_img *img, t_i2vec res);
int			write_to_file(t_i2vec res, t_img *img, t_bmp_extra *bmp);
#endif