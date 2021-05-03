/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 19:18:46 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/30 01:34:01 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <unistd.h>
# include <sys/uio.h>
# include <fcntl.h>

typedef struct s_file_h
{
	char			type[2];
	unsigned int	file_size;
	unsigned int	na;
	unsigned int	offset;
}				t_file_h;

typedef struct s_info_h
{
	unsigned int		header_size;
	int					width;
	int					height;
	unsigned short int	colourplanes;
	unsigned short int	bpp;
	unsigned int		compression;
	unsigned int		img_size;
	int					x_px_per_meter;
	int					y_px_per_meter;
	unsigned int		nr_clrs;
	unsigned int		nr_important_clrs;

}				t_info_h;

typedef struct	s_bmp_extra
{
	int				fd;
	int				pad_size;
	unsigned char	*padding;
}				t_bmp_extra;

void		fill_info_header(t_info_h *dib, t_img *img, t_i2vec res);
void		fill_file_header(t_file_h *header, t_img *img, t_i2vec res, int pad_size);
int			write_fileh_to_file(t_file_h *info, t_bmp_extra *bmp);
int			write_to_file(t_i2vec res, t_img *img, t_bmp_extra *bmp);
#endif