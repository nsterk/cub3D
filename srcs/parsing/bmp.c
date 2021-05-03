/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 14:27:57 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/30 01:46:15 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <bmp.h>

int	create_bmp(t_i2vec res, t_img *img)
{
	t_file_h		file_header;
	t_info_h		info_header;
	t_bmp_extra		bmp;

	bmp.fd = open("image.bmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (bmp.fd < 1)
		printf("opening failed\n");
	if ((res.x * (img->bpp / 8)) % 4 == 0)
		bmp.pad_size = 0;
	else
	{
		bmp.pad_size = 4 - (res.x * (img->bpp / 8) % 4);
		bmp.padding = ft_calloc(sizeof(char), bmp.pad_size);
	}
	fill_file_header(&file_header, img, res, bmp.pad_size);
	fill_info_header(&info_header, img, res);
	write_fileh_to_file(&file_header, &bmp);
	write(bmp.fd, &info_header, 40);
	write_to_file(res, img, &bmp);
	return (1);
}

/*
**
*/
int	write_fileh_to_file(t_file_h *info, t_bmp_extra *bmp)
{
	unsigned char	*header;

	header = ft_calloc(14, sizeof(unsigned char));
	header[0] = 'B';
	header[1] = 'M';
	header[3] = info->file_size;
	header[3] = info->file_size >> 8;
	header[4] = info->file_size >> 16;
	header[5] = info->file_size >> 24;
	header[10] = 54;
	write(bmp->fd, header, 14);
	free(header);
	return (1);
}

int	write_to_file(t_i2vec res, t_img *img, t_bmp_extra *bmp)
{
	int	x;
	int	y;

	y = res.y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < res.x)
		{
			write(bmp->fd, img->addr + (y * img->len + x * img->bpp / 8), sizeof(int));
			x++;
		}
		write(bmp->fd, bmp->padding, bmp->pad_size);
		y--;
	}
	return (1);
}

void	fill_info_header(t_info_h *dib, t_img *img, t_i2vec res)
{
	dib->header_size = 40;
	dib->width = res.x * (img->bpp / 8);
	dib->height = res.y * (img->bpp / 8);
	dib->colourplanes = 1;
	dib->bpp = img->bpp;
	dib->compression = 0;
	dib->img_size = 0;
	dib->x_px_per_meter = 0;
	dib->y_px_per_meter = 0;
	dib->nr_clrs = 0;
	dib->nr_important_clrs = 0;
}

void	fill_file_header(t_file_h *header, t_img *img, t_i2vec res, int pad_size)
{
	header->type[0] = 'B';
	header->type[1] = 'M';
	header->file_size = 54 + (((img->bpp / 8) * res.x + pad_size ) * res.y);
	header->na = 0;
	header->offset = 54;
}
