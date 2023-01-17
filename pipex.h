/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdoh <jdoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 11:53:29 by jdoh              #+#    #+#             */
/*   Updated: 2023/01/17 21:05:07 by jdoh             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define FAILURE -1
# define SUCCESS 0

typedef struct s_info
{
	char	***cmds;
	int		**fds;
	char	*input;
	char	*output;
	char	**envp;
	int		pid_num;
}			t_info;

int			pipex(int argc, char *argv[], char *envp[]);
int			parsing(t_info *info, char *argv[], char *envp[]);
void		manage_process(t_info *info);

void		info_init(t_info *info, int argc, char *argv[], char *envp[]);

long long	free_splitted(char **splitted, long long ret);
int			free_cmds(char ***cmds, int num);
int			free_fds(int **fds, int size);
int			error_msg(char *str);

#endif