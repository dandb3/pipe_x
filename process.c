/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:20:59 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/17 19:22:16 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>
#include <unistd.h>

static void	close_all(t_info *info, int size)
{
	int	idx;

	idx = -1;
	while (++idx < size)
	{
		if (close(info->fds[idx][0]) == FAILURE)
			exit(error_msg(NULL));
		if (close(info->fds[idx][1]) == FAILURE)
			exit(error_msg(NULL));
	}
}

static void	close_except_io(t_info *info, int pos)
{
	int	idx;

	idx = -1;
	while (++idx < info->pid_num + 1)
	{
		if (idx != pos && close(info->fds[idx][0]) == FAILURE)
			exit(error_msg(NULL));
		if (pos + 1 != idx && close(info->fds[idx][1]) == FAILURE)
			exit(error_msg(NULL));
	}
}

static int	parent_process(t_info *info)
{
	int	idx;

	idx = 0;
	close_all(info, info->pid_num + 1);
	while (idx < info->pid_num)
	{
		wait(NULL);
		idx++;
	}
	return (SUCCESS);
}

static void	child_process(t_info *info, int idx)
{
	close_except_io(info, idx);
	if (dup2(info->fds[idx][0], STDIN_FILENO) == FAILURE
		|| dup2(info->fds[idx + 1][1], STDOUT_FILENO) == FAILURE)
		exit(error_msg(NULL));
	execve(info->cmds[idx][0], info->cmds[idx], info->envp);
	exit(error_msg(info->cmds[idx][0]));
}

void	manage_process(t_info *info)
{
	pid_t	pid;
	int		idx;

	pid = 1;
	idx = 0;
	while (idx < info->pid_num && pid != 0)
	{
		pid = fork();
		if (pid == FAILURE)
			exit(error_msg(NULL));
		if (pid == 0)
			break ;
		idx++;
	}
	if (pid != 0)
		parent_process(info);
	else
		child_process(info, idx);
}
