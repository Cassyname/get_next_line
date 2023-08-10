/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgeoffra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:28:30 by cgeoffra          #+#    #+#             */
/*   Updated: 2023/04/11 12:52:40 by cgeoffra         ###   ########.fr       */
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
	if (!str || str[0] == '\0')
		return (NULL);
	s1 = ft_line(str);
	if (ft_strchr(str, '\n') != NULL)
		str = ft_afterline(str);
	else
		str[0] = '\0';
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
	}
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
		ft_bzero(buff, BUFFER_SIZE + 1);
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
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	s1 = ft_calloc((i + 2), sizeof(char));
	if (!s1)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s1[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s1[i] = '\n';
	return (s1);
}

char	*ft_afterline(char *str)
{
	char	*tmp;
	int		i;
	int		a;

	i = 0;
	a = 0;
	while (str[i] != '\n')
		i++;
	i++;
	tmp = ft_calloc((ft_strlen(str) - i + 1), sizeof(char));
	if (!tmp)
		return (NULL);
	while (str[i] != '\0')
		tmp[a++] = str[i++];
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

char	*ft_strdup(char *s)
{
	char	*str;
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	str = ft_calloc(i + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
