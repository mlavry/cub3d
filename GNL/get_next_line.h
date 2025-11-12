/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlavry <mlavry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:29:21 by mlavry            #+#    #+#             */
/*   Updated: 2025/11/12 22:18:01 by mlavry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

void	*ft_calloc(size_t n, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_free(char *buffer, char *buff);
char	*read_file(int fd, char *res);
char	*get_next_line(int fd);
char	*ft_line(char *buffer);
size_t	ft_strlen(const char *s);
char	*ft_next(char *buffer);

#endif
