/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 14:27:57 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/29 20:37:12 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <bmp.h>

int	create_bmp(t_i2vec res, t_img *img)
{
	t_file_h		file_header;
	t_info_h		info_header;
	t_bmp_extra		bmp;

	fill_file_header(&file_header, img, res);
	fill_info_header(&info_header, img, res);
	bmp.fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (bmp.fd < 1)
		printf("opening failed\n");
	if ((res.x * (img->bpp / 8)) % 4 == 0)
		bmp.pad_size = 0;
	else
	{
		bmp.pad_size = 4 - (res.x * (img->bpp / 8) % 4);
		bmp.padding = ft_calloc(sizeof(char), bmp.pad_size);
	}
	write(bmp.fd, &file_header, 14);
	write(bmp.fd, &info_header, 40);
	write_to_file(res, img, &bmp);
	return (1);
}

/*
**
*/
int	write_to_file(t_i2vec res, t_img *img, t_bmp_extra *bmp)
{
	int	x;
	int	y;

	y = res.y;
	while (y >= 0)
	{
		x = 0;
		while (x < res.x)
		{
			write(bmp->fd, img->addr + (y * img->len + x * (img->bpp / 8)), sizeof(int));
			x++;
		}
		if (bmp->pad_size)
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

void	fill_file_header(t_file_h *header, t_img *img, t_i2vec res)
{
	header->type[0] = 'B';
	header->type[1] = 'M';
	header->file_size = 54 + ((img->bpp / 8) * res.x * res.y);
	header->na = 0;
	header->offset = 54;
}
