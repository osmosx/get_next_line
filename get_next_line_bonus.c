/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nenvoy <nenvoy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:29:11 by nenvoy            #+#    #+#             */
/*   Updated: 2021/11/11 17:23:27 by nenvoy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_reminder(char *reminder)
{
	int		i;
	int		j;
	int		len;
	char	*line;

	i = 0;
	j = 0;
	len = ft_strlen(reminder);
	while (reminder[i] && reminder[i] != '\n')
		i++;
	if (!reminder[i])
	{
		free(reminder);
		return (NULL);
	}
	line = malloc(sizeof(char) * ((len - i) + 1));
	if (!line)
		return (NULL);
	i++;
	while (reminder[i])
		line[j++] = reminder[i++];
	line[j] = '\0';
	free(reminder);
	return (line);
}

char	*fd_reader(int fd, char *reminder)
{
	char	*buf;
	int		byte_read;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	byte_read = 1;
	buf[0] = '\0';
	while (!(ft_strchr(buf, '\n')) && byte_read)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[byte_read] = '\0';
		reminder = ft_strjoin(reminder, buf);
	}
	free(buf);
	return (reminder);
}

char	*get_next_line(int fd)
{
	static char	*reminder[1024];
	char		*line;
	int			i;

	line = NULL;
	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	reminder[fd] = fd_reader(fd, reminder[fd]);
	if (!reminder[fd])
		return (NULL);
	if (*reminder[fd])
	{
		while (reminder[fd][i] && reminder[fd][i] != '\n')
			i++;
		line = malloc(sizeof(char) * (i + 2));
		if (!line)
			return (NULL);
		line = ft_strcpy(line, reminder[fd]);
	}
	reminder[fd] = ft_reminder(reminder[fd]);
	return (line);
}
