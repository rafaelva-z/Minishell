/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:44:29 by scosta-j          #+#    #+#             */
/*   Updated: 2024/01/07 20:45:07 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_pwd(char *oldpwd)
{
	char	*cwd;
	t_envp	*shell;

	shell = get_env_struct();
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		shell->set("PWD", cwd);
		free(cwd);
	}
	if (oldpwd)
		shell->set("OLDPWD=", oldpwd);
}

static int	count_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

/**
 * @brief change the working directory
*/
void	cd(char **cmds)
{
	int		r;
	char	*home;
	char	*oldpwd;
	
	if (count_cmds(cmds) > 1)
	{
		perror("cd: too many arguments\n");
		return ;
	}
	home = get_env_struct()->get_value("HOME");
	r = -1;
	if (!cmds[0] && !home)
		return ;
	oldpwd = getcwd(NULL, 0);
	if (!cmds[0])
		r = chdir(home);
	else
		r = chdir(cmds[0]);
	if (r < 0)
		perror(""); // how do i make this work properly?
	else if (oldpwd)
		set_pwd(oldpwd);
	if (oldpwd)
		free(oldpwd);
}

/**
 * 	CD =============================
 * 
 * 	No args				->	cd to home				DONE
 * 	Empty args			->	do nothing				DONE
 *  Args 				->	cd to arg				DONE
 *	Args.Arg not found	->	error					NOT SIMILAR
 * 	
 *  HOME not set		->	"~" Doesn't work & no args does nothing
 * 	PWD/OLDPWD not set	->	everything works normally when changing
 * 							directories always updates PWD/OLDPWD
*/