/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnguegan <fnguegan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:00:24 by fnguegan          #+#    #+#             */
/*   Updated: 2026/07/31 21:27:34 by fnguegan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*pool_check(char *pool)
{
	char	*new_pool;
	int		i;

	if (!pool)
		return (NULL);
	i = 0;
	while (pool[i] && pool[i] != '\n')
		i++;
	if (!pool[i])
	{
		free (pool);
		return (NULL);
	}
	i++;
	new_pool = ft_strdup(pool + i);
	free(pool);
	return (new_pool);
}

char	*retrieve_line(char *pool)
{
	char	*line;
	int		i;

	if (!pool || !pool[0])
		return (NULL);
	i = 0;
	while (pool[i] && pool[i] != '\n')
		i++;
	if (pool[i] == '\n')
		i++;
	line = ft_substr(pool, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*read_from_buffer_and_save(int fd, char *pool)
{
	char	*buffer;
	int		bytes;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(pool), NULL);
	while (!ft_strchr (pool, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buffer), free(pool), NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(pool, buffer);
		if (!temp)
			return (free(buffer), free(pool), NULL);
		free(pool);
		pool = temp;
	}
	free(buffer);
	return (pool);
}

char	*get_next_line(int fd)
{
	static char	*pool;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (free(pool), pool = NULL, NULL);
	}
	if (!pool)
	{
		pool = ft_strdup("");
		if (!pool)
			return (NULL);
	}
	pool = read_from_buffer_and_save(fd, pool);
	if (!pool)
		return (NULL);
	line = retrieve_line(pool);
	if (!line)
	{
		free(pool);
		pool = NULL;
		return (NULL);
	}
	pool = pool_check(pool);
	return (line);
}

// int main(void)
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line;

// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
