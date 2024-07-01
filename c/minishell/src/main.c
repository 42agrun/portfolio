/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:15:01 by agrun             #+#    #+#             */
/*   Updated: 2023/05/25 12:15:05 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	main.c: 1.	*/
/*	Checking if the declared "exit" command is being paired with arguments,
	display a custom notification instead. This is also to prevent the shell 
	from outputting "exit : command not found" otherwise.			*/

static void	check_for_exit_options(char *str, int i)
{
	i = skip_spaces(str, 0);
	if (!ft_find_word(str, "exit", 0, 0))
		return ;
	i += 4;
	if (empty_check(str, i))
		return ;
	e_print("minishell: exit: no options or arguments are supported\n", 0, 0, 0);
	str[0] = 0;
}

/*	main.c: 2.	*/
/*	It is imperative to add a complex strcmp-check for any custom flags
	featuring ($) which were added/created via the export-command.

	Example: $TEST should return the content of this flag.
	Bash hides unrecognized flags, so we'll do the same here.

	Currently the function only seems to support one command at a time,
	it should be fed multiple strings (containing single words/commands)
	to fullfill its purpose. Consider this for the finalization!

	IMPORTANT: "define_format" (check "shell_commands") should only 
	commentate on a single command and then halt any further interpretations. 
	Ignore further arguments/options. This is how bash behaves, we intend to 
	replicate this behavior.

	If the prompt starts with BRACKETS then you need to look inside and
	reformat the prompt-string before returning it to the function.
	Check "brackets.c" for further context.

	if (check_flag_commands(str, env, 0))	<= outdated function
		return (env);			  (previously on top)		*/

char	**check_commands(char *str, char **env)
{
	char	buffer[1024];
	char	new_str[1024];

	if (!check_echo_prefix(str))
		env = check_export_unset(str, env);
	check_for_brackets(str, new_str, 0, 0);
	check_for_exit_options(new_str, 0);
	if (!new_str[0])
		return (env);
	if (check_qm_prompt(new_str, 0))
		return (env);
	else if (ft_find_bracketed_flag(new_str))
	{
		rewrite_prompt(new_str, buffer, 0, 0);
		define_format(buffer, env, 0, -1);
	}
	else if (ft_find_word(new_str, "$(", 0, 0))
		define_format(new_str, env, 0, -1);
	else if (!ft_find_word(new_str, "$", 0, 0))
		env = check_shell_commands(new_str, env, 0);
	return (env);
}

/*	main.c: 3.	*/
/*	This function copies envp into env which will be used and edited
	by the various built-ins as well as the other commands. Signals
	from the user will be caught by the sigint_handler.			

	Triggering SIGQUIT at the start to make sure it never gets used again.
	Signals will be performed on their first press, this is inevitable.
	That's why they should be triggered at the very start before the
	sigint_handler can actually interprete them.				*/

static char	**initialize_main(char **envp)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	sigint_handler(SIGQUIT);
	return (copy_env(envp, 0, 0));
}

/*	main.c: 4.	*/
/*	ft_exit makes sure to free the prompt string, so no worries there.	
	ft_free does return 1, so that part of error-return is taken care of.

	In case of a malloc-fail we need to clear out everything and then
	shut down the program.

	To save lines I've included the malloc-check for prompt in the exit
	check function (ft_exit) which will shut down the program after
	clearing out everything.						*/

static int	main_ex(char *buf, char **env, t_token *head)
{
	char	*prompt;

	while (env)
	{
		prompt = readline("minishell: ");
		if (ft_exit(prompt, env))
			return (0);
		if (!empty_check(prompt, 0))
		{
			manage_main(buf, prompt, env, 0);
			if (check_for_operators(buf, env, 0, 0))
				lexer_parcer(buf, env, head);
			else
				env = check_commands(buf, env);
			if (!env)
				return (ft_error(1, prompt, env));
			check_printout(0, NULL, 2, 0);
		}
		ft_free(&prompt);
	}
	return (0);
}

/*	main.c: 5.	*/
/*	argc & argv are irrelevant but we still need them to extract envp!	*/

int	main(int argc, char **argv, char **envp)
{
	char		buf[5000];
	char		**env;
	t_token		*head;

	if (argc != 1 || argv[1] != NULL)
		return (1);
	env = initialize_main(envp);
	if (!env)
	{
		write (2, "Error\n", 6);
		write (2, "Malloc failed.\n", 15);
		return (1);
	}
	head = NULL;
	return (main_ex(buf, env, head));
}
