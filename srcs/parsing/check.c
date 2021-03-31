
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <get_next_line.h>
#include <libft.h>

typedef struct s_lst
{
	void			*content;
	struct s_lst	*next;
}					t_lst;

static void	print_list(t_lst *lst)
{
	t_lst	*temp;

	temp = lst;
	while (temp != NULL)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}

static t_lst	*ft_strlast(t_lst *lst)
{
	t_lst	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

static t_lst	*ft_strnew(char *content)
{
	t_lst	*new_element;

	new_element = malloc(sizeof(t_lst));
	if (!new_element)
		return (NULL);
	new_element->content = content;
	new_element->next = NULL;
	return (new_element);
}

static void	*ft_str_add_back(t_lst **lst, char *content)
{
	t_lst	*new;
	t_lst	*temp;

	if (!lst)
		return (NULL);
	new = ft_strnew(content);
	if (!new)
		return (NULL);
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_strlast(*lst);
		temp->next = new;
	}
}

static char	*ft_strduppie(const char *src)
{
	char	*rstr;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	rstr = (char *)malloc(sizeof(*rstr) * (len + 1));
	if (!rstr)
		return (NULL);
	len = 0;
	while (src[len] != '\0')
	{
		rstr[len] = src[len];
		len++;
	}
	rstr[len] = '\0';
	return (rstr);
}

int		main(void)
{
	char	*line;
	t_lst	*head;
	int		ret;
	char	*str;
	int		fd;

	str = "regel 0";
	ret = 1;
	fd = open("/Users/NaomiSterk/codam/cub3d/srcs/parsing/text.cub", O_RDONLY);
	if (fd < 0)
	{
		printf("failed to open text.cub\n");
		return (1);
	}
	head = ft_strnew(ft_strduppie(str));
	if (!head)
	{
		printf("failed to create head\n");
		return (1);
	}
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret < 0)
		{
			printf("failed to get next line from fd\n");
			return (1);
		}
		ft_str_add_back(&head, ft_strduppie(line));
		free(line);
	}
	print_list(head);

}