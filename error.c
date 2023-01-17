/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 12:43:39 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/17 21:04:51 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "pipex.h"

long long	free_splitted(char **splitted, long long ret)
{
	char	**tmp;

	if (splitted == NULL)
		return (ret);
	tmp = splitted;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(splitted);
	return (ret);
}

int	free_cmds(char ***cmds, int num)
{
	int	idx;

	idx = 0;
	while (idx < num)
	{
		free_splitted(cmds[idx], FAILURE);
		idx++;
	}
	free(cmds);
	return (FAILURE);
}

int	free_fds(int **fds, int size)
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		free(fds[idx]);
		idx++;
	}
	free(fds);
	return (FAILURE);
}

int	error_msg(char *str)
{
	perror(str);
	return (1);
}
