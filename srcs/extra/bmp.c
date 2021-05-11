/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 14:27:57 by nsterk        #+#    #+#                 */
/*   Updated: 2021/05/11 00:47:58 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>
#include <bmp.h>

int	create_bmp(t_i2vec res, t_img *img)
{
	t_info_h	info_header;
	int			fd;
	int			pad_size;
	int			y;

	fd = open("image.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 1)
	{
		printf("opening failed\n");  // ERROR
		return (0);
	}
	if ((res.x * (img->bpp / 8)) % 4 == 0)
		pad_size = 0;
	else
		pad_size = 4 - (res.x * (img->bpp / 8) % 4);
	write_fileh_to_file(img->bpp, pad_size, fd, res);
	fill_info_header(&info_header, img, res);
	write(fd, &info_header, 40);
	y = res.y - 1;
	while (y >= 0)
	{
		write(fd, img->addr + (y * img->len), res.x * sizeof(int));
		y--;
	}
	return (1);
}

int	write_fileh_to_file(int bpp, int pad_size, int fd, t_i2vec res)
{
	unsigned char	*header;
	unsigned int	size;

	size = 54 + (((bpp / 8) * (res.x + pad_size)) * res.y);
	header = ft_calloc(14, sizeof(unsigned char));  // ERROR
	header[0] = 'B';
	header[1] = 'M';
	header[3] = size;
	header[3] = size >> 8;
	header[4] = size >> 16;
	header[5] = size >> 24;
	header[10] = 54;
	write(fd, header, 14);
	free(header);
	return (1);
}

void	fill_info_header(t_info_h *dib, t_img *img, t_i2vec res)
{
	dib->header_size = 40;
	dib->width = res.x;
	dib->height = res.y;
	dib->colourplanes = 1;
	dib->bpp = img->bpp;
	dib->compression = 0;
	dib->img_size = 0;
	dib->x_px_per_meter = 0;
	dib->y_px_per_meter = 0;
	dib->nr_clrs = 0;
	dib->nr_important_clrs = 0;
}
