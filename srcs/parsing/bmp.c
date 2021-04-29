/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bmp.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nsterk <nsterk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/28 14:27:57 by nsterk        #+#    #+#                 */
/*   Updated: 2021/04/29 19:43:54 by nsterk        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <bmp.h>

int	create_bmp(t_i2vec res, t_img *img)
{
	t_bmp_h		bitmap_header;
	t_dib_h		info_header;
	t_bmp_extra	bmp;

	bmp.fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (bmp.fd < 1)
		printf("opening failed\n");
	if ((res.x * (img->bpp / 8)) % 4 == 0)
		bmp.pad = 0;
	else
	{
		bmp.pad = 4 - (res.x * (img->bpp / 8) % 4);
		bmp->padding = ft_calloc(sizeof(char), bmp.pad);
	}
	return (1);
}

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
			write(fd, img->addr + (y * img->len + x * (img->bpp / 8)), sizeof(int));
			x++;
		}
		if (pad)
			write(fd, padding, pad);
		y--;
	}
	return (1);
}

void	fill_dib_header(t_dib_h *dib, t_img *img, t_i2vec res)
{
	dib->header_size = 40;
	dib->colourplanes = 1;
	dib->bpp = img->bpp;
	dib->compression = 0;
	dib->img_size = 0;
	dib->res_x = res.x;
	dib->res_y = res.y;
	dib->colours = 0;
	dib->important_colours = 0;
}
/*
**	add value for file_size
*/

void	fill_file_header(t_file_h *header, t_img *img)
{
	header->type[0] = 'B';
	header->type[1] = 'M';
	header->na = 0;
	header->offset = 54;
}
