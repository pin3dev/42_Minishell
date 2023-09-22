/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clima-fr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:50:22 by clima-fr          #+#    #+#             */
/*   Updated: 2023/09/19 21:28:53 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdarg.h>
# include <signal.h>
# define BUFFER_SIZE 1024
# define WRITE 1
# define READ 0

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define RESET   "\x1b[0m"

extern int	g_status;

typedef enum s_div
{
	CMD,
	REDIR,
	PIPE
}t_div;

typedef enum type_token
{
	NDA,
	IN_R,
	OUT_R,
	HEREDOC,
	APPEND,
	SPACES,
	QUOTES,
	PIPES,
	REDIRECTION
}t_type_token;

typedef struct s_cmd
{
	char	*name;
	char	*param[49];
	char	*full_cmd[50];
}t_cmd;

typedef struct s_redir
{
	int				fd;
	int				mode;
	char			*file;
	struct s_token	*next_tok;
}t_redir;

typedef struct s_pipe
{
	struct s_token	*left;
	struct s_token	*right;
}t_pipe;

typedef struct s_token
{
	t_div			type;
	t_cmd			*cmd;
	t_pipe			*pipe;
	t_redir			*redir;
	struct s_token	*next;
}t_token;

typedef enum e_sig
{
	STATIC,
	INTERACTV,
	EXT,
	REDO
}t_sig;

typedef struct s_envp
{
	char			*name;
	char			*value;
	char			*full;
	struct s_envp	*next;
}t_envp;

typedef struct s_expo
{
	char			*prefix;
	char			*name;
	struct s_expo	*next;
}t_expo;

typedef struct s_global
{
	int			fd_in;
	int			fd_out;
	int			prompt;
	char		**paths;
	char		**envp;
	char		*line;
	char		*input;
	char		**tokens;
	t_envp		**l_envp;
	t_token		**head_list;
	t_token		**head_ast;
	t_expo		**l_expo;
}t_global;

t_expo	*find_prev_expo_node(char *name, t_expo **list);
t_expo	*ft_lstnew_export(char *name);
t_expo	*find_expo_node(char *name, t_expo **list);

int		cat_status(int status);
int		ft_strlen(char *str);
int		nbr_len(int nbr);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		abs_nbr(int nbr);
int		init_len_nbr(int nbr);
int		ft_isalpha(int c);
int		ft_isalnum(int x);
int		ft_lstsize_envp(t_envp *lst);
int		ft_strcmp(char *s1, char *s2);
int		cmp_sort_str(char *s1, char *s2);
int		ft_strncmp(char *str1, char *str2, int n);
int		redir_type(char *redir);
int		token_type(char token);
int		echo_quotes_aux(char *input, int index);
int		verify_closed_quotes(char *input, char quote, int i);
int		find_index(char *str, char *word);
int		count_quote_to_split(char *full_cmd, int c);
int		split_quote(char *full_cmd, char **str, int flag, int *s);
int		count_rest_to_split(char *full_cmd, int *c, int count);
int		index_char(char *str, char c);
int		copy_tokens(char *full_cmd, char **str, int *s, int *heredoc_flag);
int		check_biggest_str(char *token, char *line);
int		heredoc(char *input, int index, t_global *global, char *delimiter);
int		verify_heredoc(char *input, t_global *global, int i, int exit);
int		count_tokens(char *str, int flag);
int		count_param(char **param);
int		forknize(void);
int		status_here(t_global *global, char *input, char *prev_line, int index);
int		duplicate(int fd_dest, int fd_src);
int		set_pipe(int fds[2]);
int		count_dollar(char *heredoc_line);

void	exec_export(char **params, t_global *global, int i);
void	go_to_home(t_global *global);
void	update_pwd(char *pwd, t_global *global);
void	set_new_status(int exit_status);
void	clear_memory(int flag, t_global *global);
void	print_error(char *s1, char *s2, char *s3);
void	interactive_mode_slash(int sig);
void	interactive_mode_c(int sig);
void	prompt_reopen(int sig);
void	set_sig(t_sig sig, t_global *global);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t nitems, size_t size);
void	ft_lstadd_back_envp(t_envp **head, t_envp *new);
void	ft_lstadd_back_list_ast(t_token **head, t_token *new);
void	split_spaces(char *full_cmd, char **str, int *c, int *s);
void	split_pipes_n_redir(char *full_cmd, char **str, int *c, int *s);
void	heredoc_size(char *full_cmd, int *count, int *c, int *heredoc_flag);
void	skip_spaces(char *str, int *c);
void	split_tokens_no_quotes(char *full_cmd, char **str2, int flag, int *s);
void	split_tokens_w_quotes(char *full_cmd, char **str2, int c, int *s);
void	end_status_heredoc(t_global *global, char *line, char *delimiter);
void	create_envp_list(char *str, t_envp **list);
void	modify_envp_node(char *value, t_envp *node);
void	copy_envp(char **o_envp, t_envp **list);
void	copy_paths(t_envp **list, t_global *global);
void	clear_array(char **str);
void	execve_command(t_cmd *cmd, t_global *global, char *path);
void	free_array(char **array, bool flag);
void	update_envp_array(t_global *global);
void	out_exit(int n, t_global *global);
void	mini_exit(char **param, t_global *global);
void	mini_cd(char **path, t_global *global);
void	mini_pwd(t_global *global, t_cmd *cmd);
void	mini_env(t_envp **head, t_cmd *cmd);
void	print_expo_list(t_expo **l_expo, t_envp **l_envp);
void	insert_sorted(t_expo **head, char *name);
void	create_export_list(t_expo **l_expo, t_envp **l_envp);
void	export_var(char *new_var, t_global *global);
void	mini_export(char **new_var, t_global *global);
void	remove_expo_node(char *name_var, t_expo **l_expo);
void	remove_envp_node(char *name_var, t_envp *to_free, t_global *global);
void	mini_unset(char **name_var, t_global *global);
void	no_new_line(int *i, int *new_line, int *flag_n);
void	skip_n(char *str, int *c);
void	print_character(char *str, int *i, int *new_line, int *flag_n);
void	start_echo(char **split, int i);
void	count_quote_token(char *str, int flag, int *i, int *tokens);
void	count_special_tokens(char *str, int flag, int *i, int *tokens);
void	count_rest_tokens(char *str, int *i, int *tokens, int *heredoc);
void	mini_echo(t_global *global, char *new_param);
void	exec_builts(t_cmd *cmd, t_global *global);
void	finish_cmd_node(t_token *node, int index);
void	free_envp_lst(t_envp **head);
void	free_expo_lst(t_expo **head);
void	clear_enviroment(t_global *global);
void	clear_exit(t_global *global);
void	clear_redo(t_global *global);
void	free_pipe(t_token *cur);
void	free_redir(t_token *cur);
void	free_cmd(t_token *cur);
void	clear_ast(t_token **head);
void	init_minixhell(t_global *global);
void	init_lexer(t_global *global);
void	run_minixhell(t_global *global);
void	fill_type_redir_node(t_redir *redir, int fd, int mode);
void	end_pipe(char **str, int *s, t_token **head);
void	create_cmd_list(char **str, t_token **head, int s, int i);
void	priority_reorder(t_token *tmp, t_token *cur, t_token **side);
void	priority_pass(t_token *cur, t_token *end, t_token **side);
void	organize_ast(t_token *begin, t_token *end, t_token **side);
void	find_pipes(t_token *begin);
void	create_ast(t_token **head_list, t_token **head_ast);
void	pipenizer(t_token *cur, t_global *global);
void	heredocnizer(t_token *cur, t_global *global);
void	check_redirs(t_token *first);
void	redinizer(t_token *cur, t_global *global);
void	run_ast(t_token **token, t_global *global);
void	create_new_line(t_global *global, char *line, char *new, char **split);
void	print_list(t_token **head);
void	print_strings(char **array);

char	*concatenate_export_name(char **params, int *i);
char	*ext_cases(int nbr);
char	*ft_itoa(int nbr);
char	*ft_substr(char *s, int start, int len);
char	**ft_split(char *s, char c);
char	*ft_strcpy2(char *dest, char *src, int size);
char	*ft_strcpy(char *dest, char *src);
char	*get_next_line(int fd, int i, char *line);
char	*ft_strdup_be(const char *s, int begin, int end);
char	*ft_strdup(const char *s);
char	*concatenate_string(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*find_delimiter(char *input);
char	*cat_exec(t_cmd *cmd, t_global *global);
char	**split_tokens(char *full_cmd, int flag);
char	*find_word(char *prev_word);
char	*create_begin_line(t_global *global, char *prev_word, char *line);
char	*replace_word(t_global *global, char *prev_w, char *line, char **split);
char	*new_line(t_global *global, char *to_find, char *copy_line, int mark);
char	*word_to_find(char *copy_line, int index, int *mark, char quote);
char	*replace_dollar(t_global *global, char *dollar_line);
char	*new_command_param(t_global *global, char *command);
char	*heredoc_case(t_global *global, char *heredoc_l, char *full, int final);
char	*dollar_heredoc(t_global *global, char *heredoc_l, char *line, int *i);

bool	verify_pipes(char *input, int i);
bool	verify_redirections(char *input, int i);
bool	verify_pipes_redir_quotes(char *input);
bool	alpha_arg(char *str);
bool	digit_arg(char *str);
bool	verify_empty_str(char *str, int c);
bool	dollar_sign(t_global *global, char *line, int index, int i);

t_envp	*find_envp_node(char *name, t_envp **list);
t_envp	*find_prev_envp_node(char *name, t_envp **list);
t_envp	*ft_lstnew_envp(char *name, char *value, char *full);

t_token	*fill_cmd_node(char *str, int index, int finish, t_token *node);
t_token	*fill_redir_node(char **str);
t_token	*fill_pipe_node(char **str);
t_token	*begin_cmd_or_redir(char **str, int *s, int *i, t_token **head);
t_token	*find_div_node(t_div type, t_token *begin, t_token *end);
t_token	*ft_lstlast_ast(t_token *lst);
t_token	*ft_lstnew_list_ast(t_div type);

const char	*get_prompt(int status);

#endif
