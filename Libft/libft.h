/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktintim- <ktintim-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:37:30 by ktintim-          #+#    #+#             */
/*   Updated: 2024/11/26 11:11:52 by ktintim-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1234
# endif

# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int				ft_atoi(char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_strlen(const char *str);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_iterative_power(int nb, int power);
int				ft_lstsize(t_list *lst);
int				ft_printf(const char *str, ...);
void			*ft_memset(void *ptr, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, \
							size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t num, size_t size);
void			ft_putnbr_fd(int n, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_unsignedputnbr_fd(unsigned int n, int fd, int *length);
void			ft_putnbrbase_printf(unsigned int nbr, \
						const char *base, int *length);
void			ft_putchar_printf(char c, int fd, int *length);
void			ft_putstr_printf(char *s, int fd, int *length);
void			ft_putnbr_printf(int n, int fd, int *length);
void			ft_pointer_printf(size_t nbr, const char *base, int *length);
char			*ft_strnstr(char *str, char *to_find, int n);
char			*ft_strdup(char const *src);
char			*ft_strchr(char *str, char c);
char			*ft_strrchr(char *str, char c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strcat(char *dest, char *src);
char			*ft_strcpy(char *dest, char *src);
char			**ft_split(char const *s, char c);
char			*get_next_line(int fd);
unsigned int	ft_strlcat(char *src, char *dest, unsigned int size);
unsigned int	ft_strlcpy(char *dest, char const *src, unsigned int size);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
							void (*del)(void *));

#endif
