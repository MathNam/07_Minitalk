/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fr_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:53:01 by maaliber          #+#    #+#             */
/*   Updated: 2023/02/02 15:36:38 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	del_arg(t_arg_spec *spec)
{
	free(spec->param);
	spec->param = NULL;
	free(spec);
	return ;
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*rst;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	rst = ft_strjoin(s1, s2);
	return (free(s1), free(s2), rst);
}

void	*ft_setalloc(size_t size, char c, int null_terminated)
{
	void	*arr;
	size_t	i;

	arr = malloc(size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
		((char *)arr)[i++] = c;
	if (null_terminated)
		((char *)arr)[size - 1] = 0;
	return (arr);
}

char	*ft_strinsert(char const *s, char const *to_insert, size_t pos)
{
	char	*rst;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	if (pos == 0)
		return (ft_strjoin(to_insert, s));
	if (pos > len)
		return (ft_strjoin(s, to_insert));
	rst = malloc(len + ft_strlen(to_insert) + 1);
	if (!rst)
		return (NULL);
	i = 0;
	while (i < pos)
		rst[i++] = *s++;
	while (*to_insert)
		rst[i++] = *to_insert++;
	while (*s)
		rst[i++] = *s++;
	rst[i] = 0;
	return (rst);
}

char	*ft_strinsert_free(char const *s, char const *to_insert, size_t pos)
{
	char	*rst;

	rst = ft_strinsert(s, to_insert, pos);
	free((void *)s);
	free((void *)to_insert);
	return (rst);
}
