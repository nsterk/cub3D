/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/29 19:18:46 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/14 14:46:08 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include <unistd.h>
# include <sys/uio.h>
# include <fcntl.h>

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

void		fill_info_header(t_info_h *dib, t_img *img, t_i2vec res);
void		write_fileheader(int bpp, int pad_size, int fd, t_i2vec res);
#endif