/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:41:07 by agrun             #+#    #+#             */
/*   Updated: 2023/05/17 12:41:09 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_token
{
	int				token_code;
	int				index;
	char			*token;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_command
{
	char				**com;
	char				*sep;
	char				*arg;
	struct s_command	*nx;
}	t_command;

typedef struct s_data
{
	int					i;
	char				**split;
	int					pipefd[2];
	int					in_fd;
	int					out_fd;
	t_command			*cur;
}	t_data;

typedef struct s_valid
{
	int		result;
	int		i;
	char	*com_s;
	int		com_len;
	char	*com;
	char	*path;
	char	*full;
}t_valid;

typedef struct s_hrdoc
{
	int			pfd[2];
	char		*str;
	char		*line;
	size_t		str_len;
	ssize_t		bytes_written;
	size_t		new_len;
	char		*new_str;
}t_hrdoc;

//main.c

char		**check_commands(char *str, char **env);

//sigint_handler.c

void		sigint_handler(int sig);

//check_printout_1.c

void		apply_string(char *buffer, char *str, int i);
char		*e_print(char *str, int mode, int i, int extra);
char		*check_printout(char c, char *str, int mode, int i);

//check_printout_2.c

void		complex_errors(char *buf, char *str, int extra, int i);

//check_for_operators_1.c

int			check_for_operators(char *prompt, char **env, int i, int flag);

//check_for_operators_2.c

void		replace_found_flag(char *buff_1, char *buff_2, char **env, int *i);
void		conv_prompt_string(char *str, char **env, char *bf_1, char *bf_2);

//check_for_operators_3.c

void		final_conversion(char *prompt, char *buf, int *i);
void		skip_through_string(char *buff_1, char *buff_2, int *i, int *q);
void		extract_last_return_value(char *bf_1, char *bf_2, int *i, int x);
int			check_qm_prompt_flag(char *prompt, int i, int *qm);
int			check_potential_filenames(char *str, int flag, int i);

//check_for_operators_4.c

int			check_prompt_prefix(char *str, int *i, int *qm);
int			check_prompt_cmd(char *dst, char *str, int *i, char **env);

//brackets.c

void		check_for_brackets(char *str, char *new, int i, int j);

//utils_1.c

void		print_env(char **env, int n);
int			ft_strncmp(char *ref, char *input, int i, int j);
int			empty_check(char *str, int i);
int			ft_exit(char *str, char **env);
int			ft_error(int error, char *prompt, char **env);

//utils_2.c

char		**change_directory(char *str, char **env, int i, int j);

//utils_3.c

int			ft_return(int r, int mode);
void		rewrite_prompt(char *str, char *buffer, int i, int j);
int			ft_find_word(char *str, char *ref, int i, int j);
int			ft_find_bracketed_flag(char *str);
int			check_echo_prefix(char *str);

//utils_4.c

int			check_alpha_num(char *echo, int *i, int *q);
void		adjust_flag_string(char *str, char *buf, int i);
int			check_qm_prompt(char *str, int hide_error);
int			skip_flags(char *str, int i);
int			skip_spaces(char *str, int i);

//utils_5.c

int			check_command_access(char *str, char **env, int i, int j);
void		manage_main(char *buf, char *prompt, char **env, int i);

//utils_6.c

int			check_empty_field(char *str, int i);
int			check_correct_input(char *str, char *ref, int i, int j);
void		remove_path(char *str);
int			check_standalone_export(char *str);

//utils_7.c

size_t		ft_strcspn(const char *str, const char *reject);
int			is_valid_command(char *str);

//utils_8.c

int			skip_command_paths(char *str, int i);
int			skip_spaces_and_paths(char *str);

//ft_itoa.c

char		*ft_itoa(int n, char *str);

//shell_commands.c

char		**check_shell_commands(char *str, char **envp, int hide_error);
int			check_extended_shell(char *ref, char *s, int mode);
void		define_format(char *str, char **env, int i, int j);

//flag_commands_1.c

void		skip_quotes_and_brackets(char *str, int *flag, int *i, int n);
int			check_flag_commands(char *str, char **env, int hide_e);

//flag_commands_2.c

int			display_found_flag(char *buf, char **env, int flag, int hide_e);
void		convert_all_flags(char *s, char *b, char **env);

//flag_commands_3.c

void		extract_last_return(char *bf_1, int *i, int x);
int			check_flag_conditions(char *s, int *i, int *q);

//export_unset_1.c

char		*add_new_str(char *ref, int i, int j);
char		*add_env_str(char **env, int i, int j);
char		**update_env(char **env, char *ref, int mode);

//export_unset_2.c

int			ft_array_len(char **str);
char		**rem_env(char **env, char *ref);
char		**copy_env(char **envp, int i, int mode);
int			check_valid_export_unset(char **env, char *ref, int i, int mode);

//export_unset_3.c

char		**check_export_unset(char *str, char **env);

//export_unset_4.c

void		sort_by_alpha(char **buf, char **buf2, int *x, char **ref);
char		*add_new_export_str(char *ref, int i, int j, int flag);
void		print_export_list(char **env, int n);

//echo_1.c

int			check_next_quotation_mark(char *echo, int i, int mode);
int			print_echo(char *str, int i, int j, char **envp);

//echo_2.c

void		handle_echo_rules(char *echo, int *i, int *quote_flag, char **envp);

//echo_3.c

int			check_echo_errors(char *echo, int *x);

//echo_4.c

int			handle_qm(int *i);
int			check_available_commands(char *buf);
void		display_echo_errors(char *echo, int i, int flag);

//echo_5.c

int			ft_format_error(char *str, int code, int i, int j);
int			display_known_flags(char *str, int *i, int special, char **env);

//free.c

int			ft_free_array(char **array);
int			ft_free(char **str);

//run_built_in_1.c

void		run_pwd_env(char **envp, int mode);
char		**run_built_in_echo_export(char **tmp, char **envp, int mode);
char		**run_built_in(char **tmp, char **envp);

//run_built_in_2.c

void		rewrite_buffer(char **tmp, char *buffer, int i, int x);

//access_utils_1.c

size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t destsize);
void		*ft_memcpy(void *dest, const void *src, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*join_strings(const char *str1, const char *str2, const char *str3);

//access_utils_2.c

char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_word_count(const char *str, char c);
int			ft_size_word(const char *s, char c, int i);
char		*ft_substr(char const *s, unsigned int start, size_t len);

//access_utils_3.c

char		**ft_free_str(char **strs, int j);
char		**ft_split(char const *s, char c);
int			ft_og_strncmp(const char *s1, const char *s2, size_t n);
void		valid_remove(char *str);

//access.c

char		**find_path(char **envp);
char		*valid_cmd(char **path, char *cmd);
void		valid_for_lexing(char *buf);
void		lexer_parcer(char *buf, char **env, t_token *head);

//lexer.c

void		set_token(t_token *node, char *token, int code);
void		check_symbols(t_token *node);
void		is_keyword(t_token *node);
t_token		*create_token_list(char *input, t_token *head);

//lexer_utils_1.c: 2.

int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strncpy(char *dest, const char *src, int n);
int			ft_word_count2(const char *str);
void		ft_copy_words(char **out, char *str);
char		**ft_split3(char *str);

//parser.c

void		handle_redirection(t_command *current, int *in_fd, int *out_fd);
void		tree(t_command *commands, char **envp);
void		parser(char **envp, t_token *head);

//redirect_utils_1.c

void		redirect_stdout_to_file(char *file_name, int *out_fd);
void		redirect_stdin_from_file(char *file_name, int *in_fd);
void		append_stdout_to_file(char *file_name, int *out_fd);
void		read_stdin_from_string(const char *delimiter, int *in_fd);

//parser_utils_1.c

void		add_command_node(t_command **current, t_token **tmp, char **path);
void		add_separator_node(t_command **current, t_token *tmp);
void		add_argument_node(t_command **current, t_token *tmp);
void		exit_with_error(const char *error_message);

//parser_utils_2.c

t_command	*build_command_list(t_token *head, char **path);

//parser_utils_3.c

void		execute_built_in(char **cmd, char **envp, int in_fd, int out_fd);
void		execute_command(char **cmd, char **envp, int in_fd, int out_fd);
void		select_built_or_exe(char **cmd, char **envp, int in_fd, int out_fd);
int			store_fd_flag(int i, int m);
int			check_flaggable_commands(const char *cmd, int i, int success);

//free_tools.c

void		ft_free2(char **split);
void		free_t_token(t_token *head);
void		free_t_command(t_command *head);
void		print_list(t_token *head);
void		print_command_list(t_command *head);

#endif
