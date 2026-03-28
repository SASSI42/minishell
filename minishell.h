/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaraou <hakaraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 21:39:36 by hakaraou          #+#    #+#             */
/*   Updated: 2024/06/14 11:05:43 by hakaraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_shell	t_shell;
typedef struct termios	t_termios;

typedef enum e_rd
{
	NO = 'N',
	YES = 'Y',
}	t_rd;

typedef enum e_class
{
	ENVT = 'E',
	GENERAL = 'G',
	DOUBLE_QUOTE = 'D',
	SINGLE_QUOTE = 'S',
}	t_class;

typedef enum e_type
{
	ENV = '$',
	WORD = 'W',
	PIPE = '|',
	APPEND = 'A',
	EXPORT = 'X',
	IN_RED = '<',
	OUT_RED = '>',
	HEREDOC = 'H',
	D_QUOTE = '"',
	FILE_IN = 'I',
	S_QUOTE = '\'',
	FILE_OUT = 'O',
	APPEND_F = 'F',
	E_STATUS = '?',
	HEREDOC_O = 'P',
	HEREDOC_E = 'E',
	WHITESPACE = 'S',
}	t_type;

typedef struct s_words
{
	enum e_rd		rd;
	enum e_type		type;
	char			*word;
	size_t			index;
	t_shell			*main;
	enum e_class	class;
	struct s_words	*prev;
	struct s_words	*next;
}					t_words;

typedef struct s_envt
{
	char			*name;
	struct s_envt	*next;
	char			*value;
}					t_envt;

typedef struct s_pid
{
	int				pid;
	struct s_pid	*next;
}					t_pid;

typedef struct s_rds
{
	char			**rd;
	struct s_rds	*next;
}					t_rds;

typedef struct s_toexec
{
	int				input;
	t_rds			*rds;
	t_envt			*envt;
	struct s_toexec	*prev;
	struct s_toexec	*next;
	int				output;
	char			**cmd;
}					t_toexec;

struct s_shell
{
	int			pipein;
	int			s_rd;
	char		*line;
	t_envt		*envt;
	t_words		*words;
	int			s_error;
	t_toexec	*toexec;
	char		**paths;
	int			std_in;
	int			std_out;
	int			s_export;
	int			s_export_1;
	int			exit_status;
	t_pid		*pid;
	t_termios	termios;
};

/*===========================================================================*/
								/*PARSING*/
/*===========================================================================*/
int		ft_pars(t_shell *main);

/*-------------------------------creat_exec_list-----------------------------*/
int		creat_toexec(t_shell *main);
void	put_class_0(t_words *words);
int		if_heredoc_del(char *str, char *word);
int		put_rd_toexec(t_words **words, t_toexec **toexec);
int		put_file_rd(t_rds *rds, t_words **words, size_t j);
int		put_cmd_toexec(t_words **words, t_toexec **toexec);
int		set_put_fd(t_words **words, t_toexec **toexec, t_shell *main);
int		open_heredoc(t_words *words, t_toexec *toexec, t_shell *main);

/*-------------------------------creat_list----------------------------------*/
void	ft_type(t_words *words);
int		word_node(t_shell *main);
int		creat_list(t_shell *main);
void	put_type(t_words **words);
void	put_class(t_words **words);
void	put_index(t_words **words);
int		if_all_space(t_words **words);
int		add_node(char *one_word, t_words **words, t_shell *main);
int		add_node_0(char *one_word, t_words **words, t_shell *main);

/*-------------------------------edit_list-----------------------------------*/
int		edit_list(t_shell *main);
void	type_space(t_words **words);
void	put_new_type(t_words **words);
void	del_double_quot(t_words **words);
int		del_quot_heredoc(t_words **words);
int		del_single_quotes(t_words *words);
int		join_quote_words(t_words **words);
int		join_double_quote(t_words **words);
void	ft_new_type_0(t_words *words, int i);

/*--------------------------------expand-------------------------------------*/

int		expand_0(t_words **words, t_shell *main);
int		expand_1(t_words **words, t_shell *main);
void	add_to_top(t_shell *main, t_words **tmp);
int		ft_expand(t_shell *main, t_words **words);
void	add_sub_list(t_shell *main, t_words **tmp);
int		ft_expand_2(t_words *words, t_shell *main);

/*--------------------------------pars_utils---------------------------------*/
int		meta_char_1(char c);
int		meta_char_2(char c);
int		meta_char_3(char c);
int		white_space(char c);
void	free_all_rds(t_rds **rds);
void	free_all_envt(t_envt **envt);
void	free_str(size_t i, char **str);
void	free_all_words(t_words **words);
void	free_all_toexec(t_toexec **toexec);
void	free_list_toexec(t_toexec **toexec);
void	next_cmd(t_shell *main, t_toexec **toexec);

/*--------------------------------syntax_error-------------------------------*/
int		check_quot(char *line);
void	open_here(t_words **words, t_shell *main);
int		check_rd1(char *line, int i);
int		check_rd2(char *line, int i);
int		check_pipe(char *line, int i);

/*===========================================================================*/
								/*SIGNALS*/
/*===========================================================================*/
void	ft_signal(void);
void	signal_handler(int sig);

/*===========================================================================*/
								/*LIBFT*/
/*===========================================================================*/
char	*ft_itoa(int n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(const char *s, char c);
char	**ft_split(const char *s, char c);
int		ft_atoi(const char *str, long *nbr);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*===========================================================================*/
								/*EXECUTION*/
/*===========================================================================*/

int		shell_level(t_envt **envt, char *name, char *value, t_envt *shelvl);
int		add_env_node(char *name, char *value, t_envt **envt);
int		remove_variable(char *name, t_envt **envt);
int		put_env(char **env, t_envt **envt, int i);
t_envt	*name_search(char *name, t_envt *envt);
t_envt	*find_l_node_0(t_envt *last);
char	*ft_value(char *env_line);
char	*ft_name(char *env_line);

int		ft_exit(t_shell *main, char **cmd, int exit_stat, int type);
int		ft_export(char **cmd, t_envt **envt);
int		ft_unset(char **cmd, t_envt **envt);
int		ft_env(t_envt *envt, char **cmd);
int		ft_cd(char **cmd, t_envt *envt);
int		dup_std(t_shell *node);
int		ft_echo(char **cmd);
void	ft_free(char **f);
int		ft_pwd(void);

int		export_syntax_error(char *str);
void	func_error(char *s);
void	cmd_error(char *s);
void	ft_error(char *s);

int		command_type(char **cmd);
char	*find_path(char **paths, char *cmd);
int		loop_on_cmd(t_shell *main, t_toexec *node);
int		redirect_cmd(t_shell *main, t_toexec *node);
void	execute_cmd(t_shell *main, t_toexec *node, t_envt *envt);
int		execute_builtins(t_shell *main, t_toexec *node, int type);

int		add_pid(t_pid **node, t_pid *new);
void	clear_pid(t_pid **pid);
t_pid	*new_pid(int pid);

int		reset_terminal(t_termios *termios, int flag);
void	free_main(t_shell *main);

int		restore_std(t_shell *main, int i);
void	ft_close(int *fd);
int		dup_in(int *fd);

#endif
