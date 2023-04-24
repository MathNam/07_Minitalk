/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 16:38:38 by maaliber          #+#    #+#             */
/*   Updated: 2023/02/02 15:36:28 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	atoi_printf(const char *nstr, t_arg_spec *spec)
{
	int	n;

	n = 0;
	while (*nstr >= '0' && *nstr <= '9')
	{
		n = n * 10 + (*nstr++ - '0');
		spec->size++;
	}
	return (n);
}

const char	*find_next_fmt(const char *format)
{
	return (ft_strchr(format, '%'));
}

int	init_option(t_arg_spec	*spec, const char *fmt)
{
	fmt++;
	spec->param = malloc(sizeof(t_param));
	if (!(spec->param))
		return (0);
	spec->param->left = 0;
	spec->param->padded = 0;
	spec->param->showsign = 0;
	spec->param->space = 0;
	spec->param->alt = 0;
	while (ft_ischarset(*(fmt), "-0+ #"))
	{
		if (*fmt == '-')
			spec->param->left++;
		else if (*fmt == '0')
			spec->param->padded++;
		else if (*fmt == '+')
			spec->param->showsign++;
		else if (*fmt == ' ')
			spec->param->space++;
		else if (*fmt == '#')
			spec->param->alt++;
		spec->size++;
		fmt++;
	}
	return (1);
}

t_arg_spec	*init_arg(const char *fmt)
{
	t_arg_spec	*spec;

	spec = malloc(sizeof(t_arg_spec));
	if (!spec)
		return (NULL);
	spec->size = 1;
	if (!init_option(spec, fmt))
		return (free(spec), NULL);
	spec->param->width = atoi_printf(fmt + spec->size, spec);
	if (*(fmt + spec->size) == '.')
	{
		spec->size++;
		spec->param->prec = atoi_printf(fmt + spec->size, spec);
	}
	else
		spec->param->prec = -1;
	spec->type = *(fmt + spec->size++);
	return (spec);
}

t_lst_arg	*ft_parse_format(const char *fmt)
{
	t_lst_arg	*arg_list;
	t_arg_spec	*spec;
	const char	*f = (const char *) fmt;

	arg_list = NULL;
	f = find_next_fmt(fmt);
	while (f)
	{
		spec = init_arg(f);
		ft_lstadd_back_arg(&arg_list, ft_lstnew_arg(spec));
		f = find_next_fmt(f + spec->size);
	}
	return (arg_list);
}
