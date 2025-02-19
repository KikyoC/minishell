/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togauthi <togauthi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:22:13 by cmorel            #+#    #+#             */
/*   Updated: 2025/02/19 10:40:40 by cmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h> 

int		ft_isdigit(int c);

char	*ft_strchr(const char *s, int c);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_isalnum(int c);

int		ft_isprint(int c);

void	*ft_memcpy(void *dest, const void *src, size_t n);

char	*ft_strnstr(const char *big, const char *little, size_t len);

int		ft_tolower(int c);

int		ft_isalpha(int c);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

size_t	ft_strlen(const char *s);

int		ft_atoi(const char *nptr);

void	*ft_memset(void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

int		ft_isascii(int c);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strrchr(const char *s, int c);

void	*ft_memmove(void *dest, const void *src, size_t n);

void	ft_bzero(void *s, size_t n);

size_t	ft_strlcat(char *dst, char *src, size_t size);

int		ft_toupper(int c);

void	*ft_calloc(size_t nmemb, size_t size);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strtrim(char const *s1, char const *set);

char	**ft_split(char *s, char *splitter);	

char	*ft_itoa(int n);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_striteri(char *s, void (*f)(unsigned int, char*));

void	ft_putchar_fd(char c, int fd);

void	ft_putstr_fd(char *s, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strdup(const char *s);

void	*ft_free_split(char **split);

typedef struct s_list
{
	void			*content;
	struct s_list	*prev;
	struct s_list	*next;
	int				type;
	char			**flags;
	char			*command;
	int				been_quoted;
	int				input;
	int				output;
}	t_list;

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *n);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *n);

void	ft_lstdelone(t_list *lst, void (*del)(void*));

void	ft_lstclear(t_list **lst, void (*del)(void*));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	*ft_free_split(char **split);

int		count_words(char *str, char *splitter);

#endif
