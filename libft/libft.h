/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:04:06 by lgarrosh          #+#    #+#             */
/*   Updated: 2021/10/27 16:00:50 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int ch);
int		ft_isdigit(int ch);
int		ft_isalnum(int ch);
int		ft_isascii(int ch);
int		ft_isprint(int ch);
//выводит колличество симвалов строки "ch"
size_t	ft_strlen(const char *ch);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *b1, size_t c);
void	*ft_memcpy(void *dest, const void *source, size_t count);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
//создает char с ромащю calloc и возвращает его
char	*ft_strdup(const char *s1);
//возвращает указатель на масив "s" начиная с "start" до "len" 
char	*ft_substr(char const *s, unsigned int start, size_t len);
//создает один массив из двух
char	*ft_strjoin(char const *s1, char const *s2);
//обрезает с краев "set" из "s1"
char	*ft_strtrim(char const *s1, char const *set);
//делит массив по "c" на масивы
char	**ft_split(char const *s, char c);
//обратная ft_atoi
char	*ft_itoa(int n);
//создает копию масива "s" применяя к каждому символу функцию "f"
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
//применяет функцию "f" к каждому символу "s"
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
//выводит один символ (c) в файловый дескриптор "fd"
void	ft_putchar_fd(char c, int fd);
//выводит строку "s" в файловый дескриптор "fd"
void	ft_putstr_fd(char *s, int fd);
//выводит строку "s" в файловый дескриптор "fd"
//после которого следует перенос строки
void	ft_putendl_fd(char *s, int fd);
//выводит  число "n" в файловый дескриптор "fd"
void	ft_putnbr_fd(int n, int fd);
//cоздает с помащю malloc t_list куда записывает "content"
t_list	*ft_lstnew(void *content);
//добавляет структуру в начало списка
void	ft_lstadd_front(t_list **lst, t_list *new);
//считает колличество элементов в списке
int		ft_lstsize(t_list *lst);
//возвращает последний элемент списка
t_list	*ft_lstlast(t_list *lst);
//добовляет элемент в конец списка 
void	ft_lstadd_back(t_list **lst, t_list *new);
//освобождает lst->content and lst using the function del
void	ft_lstdelone(t_list *lst, void (*del)(void *));
//применяет ft_lstdelone ко всем элементам начиная с lst до конца 
void	ft_lstclear(t_list **lst, void (*del)(void *));
//применяет функцию "f" к содиржимому каждого элемента 
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
