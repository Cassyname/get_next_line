/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:28:30 by cgeoffra          #+#    #+#             */
/*   Updated: 2023/03/21 11:35:47 by cgeoffra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*str;
	char		*s1;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!ft_strchr(str, '\n'))
		str = ft_readline(fd, str);
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
	}
	if (!str || ft_strlen(str) == 0)
		return (NULL);
	s1 = ft_line(str);
	str = ft_afterline(str);
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
	}
	if (s1[0] == '\0')
		free(s1);
	return (s1);
}

char	*ft_readline(int fd, char *str)
{
	char	*buff;

	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (NULL);
	buff[BUFFER_SIZE] = '\0';
	while (read(fd, buff, BUFFER_SIZE) == BUFFER_SIZE)
	{
		str = ft_strjoin(str, buff);
		if (ft_strchr(buff, '\n') != NULL)
			break ;
	}
	if (ft_strlen(buff) != BUFFER_SIZE)
		str = ft_strjoin(str, buff);
	free(buff);
	return (str);
}

char	*ft_line(char *str)
{
	char	*s1;
	int		i;

	i = 0;
	while (str[i] != '\n')
		i++;
	i++;
	s1 = malloc(sizeof(char) * i + 1);
	if (!s1)
		return (NULL);
	i = 0;
	while (str[i] != '\n')
	{
		s1[i] = str[i];
		i++;
	}
	s1[i++] = '\n';
	s1[i] = '\0';
	return (s1);
}

char	*ft_afterline(char *str)
{
	char	*tmp;
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (str[i++] != '\n')
	i++;
	tmp = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	while (str[i] != '\0')
		tmp[a++] = str[i++];
	free(str);
	str = ft_calloc((ft_strlen(tmp) + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (tmp[i] != '\0')
	{
		str[i] = tmp[i];
		i++;
	}
	free(tmp);
	return (str);
}

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	i = 1;
	fd = open("test.txt", O_RDONLY);
	while (i < 25)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("Lignes %d : %s", i, line);
		free(line);
		i++;
	}
	return (0);
}
