CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = minishell

LINKREADLINELIB = $(shell brew --prefix readline)/lib
LINKREADLINELIB1 = $(shell brew --prefix readline)/include

SRC = minishell.c  signals.c \
	expand/expanding_1.c  expand/shell_level.c \
	expand/put_env.c expand/expanding.c \
	expand/pars_env.c expand/expanding_0.c \
	pars_utils/ft_free_0.c \
	pars_utils/pars_utils.c pars_utils/ft_free.c \
	edit_list/put_new_info_1.c \
	edit_list/join_all.c edit_list/del_quot.c \
	edit_list/edit_list.c edit_list/put_new_info.c \
	libft/ft_itoa.c libft/libft_str.c libft/libft_ptr.c \
	creat_list/put_type.c \
	creat_list/put_node_info_0.c creat_list/word_node.c \
	creat_list/creat_list.c creat_list/put_node_info_1.c \
	creat_exec_list/put_rd.c creat_exec_list/put_rd_0.c \
	creat_exec_list/creat_toexec.c creat_exec_list/put_cmd.c \
	creat_exec_list/set_in_output.c creat_exec_list/heredoc.c \
	syntax_error/check_rd.c syntax_error/open_here.c \
	syntax_error/syntax_error.c syntax_error/check_pipe_quot.c \
	libft/minishell_utils.c libft/ft_split.c  builtins/ft_cd.c builtins/ft_env.c \
	builtins/ft_export.c builtins/ft_unset.c builtins/ft_echo.c builtins/ft_exit.c \
	builtins/ft_pwd.c builtins/command_type.c builtins/syntax_error.c \
	execute/execute_cmd.c execute/pid_save.c execute/cmd_loop.c execute/redirect_cmd.c \
	execute/std_handler.c libft/ft_strtrim.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L $(LINKREADLINELIB) -lreadline

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c -o $@ $< -I $(LINKREADLINELIB1)

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)
	
re : fclean all

.PHONY : all clean fclean re