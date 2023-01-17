/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:53:32 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/17 20:35:50 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

static void	malloc_fds(t_info *info)
{
	int	idx;

	info->fds = (int **) malloc(sizeof(int *) * (info->pid_num + 1));
	if (info->fds == NULL)
		exit(error_msg(NULL));
	idx = 0;
	while (idx < info->pid_num + 1)
	{
		info->fds[idx] = (int *) malloc(sizeof(int) * 2);
		if (info->fds[idx] == NULL)
			exit(error_msg(NULL));
		idx++;
	}
}

static void	open_fds(t_info *info)
{
	int	idx;

	info->fds[0][1] = dup(0);
	info->fds[info->pid_num][0] = dup(0);
	if (info->fds[0][1] == FAILURE || info->fds[info->pid_num][0] == FAILURE)
		exit(error_msg(NULL));
	info->fds[0][0] = open(info->input, O_RDONLY);
	info->fds[info->pid_num][1] = open(info->output, O_WRONLY | O_CREAT, 0644);
	if (info->fds[0][0] == FAILURE || info->fds[info->pid_num][1] == FAILURE)
		exit(error_msg(NULL));
	idx = 0;
	while (++idx < info->pid_num + 1)
	{
		if (pipe(info->fds[idx]) == FAILURE)
			exit(error_msg(NULL));
	}
}

void	info_init(t_info *info, int argc, char *argv[], char *envp[])
{
	ft_memset(info, 0, sizeof(t_info));
	info->envp = envp;
	info->pid_num = argc - 3;
	info->input = argv[1];
	info->output = argv[argc - 1];
	malloc_fds(info);
	open_fds(info);
}
