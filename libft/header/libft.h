/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: tduverge <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/28 18:12:07 by tduverge     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/14 15:17:34 by tduverge    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# define MAX(a,b) b & ((a - b) >> 31) | a & (~(a - b) >> 31)

# define BUFF_SIZE 1000

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_lastbuf
{
	int					fd;
	char				*lastbuf;
	struct s_lastbuf	*next;
}						t_lastbuf;

int						get_next_line(const int fd, char **line);
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
		size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strdup(const char *s1);
char					*ft_strndup(char *s1, int len);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
int						ft_atoi(char const *str);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
		char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int start,
		size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strnjoin(char const *s1, char const *s2,
		size_t len);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa(int n);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst,
		void (*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *neww);
void					ft_lstpush(t_list **alst, t_list *neww);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					ft_lstprint_nb(t_list *lst);
unsigned int			ft_lstlen(t_list *lst);
void					ft_del(void *content, size_t content_size);
void					ft_swap(char *a, char *b);
char					*ft_strrev(char *s);
char					*ft_strtoupper(char *s);
char					*ft_strtolower(char *s);
int						ft_isupper(char c);
int						ft_islower(char c);
int						ft_pow(int n, int pow);
int						*ft_bubble_sort(int *tab, int length);
int						*ft_merge_sort(int *tab, int length);
long					ft_atol(const char *str, int *check);
int						ft_strisdigit(char *str);

typedef enum			e_modif
{
	null,
	hh,
	h,
	l,
	ll,
	j,
	z
}						t_modif;

typedef struct			s_flags
{
	t_modif				modif;
	int					width;
	int					size;
	char				type;
	unsigned			hashtag : 1;
	unsigned			zero : 1;
	unsigned			less : 1;
	unsigned			more : 1;
	unsigned			space : 1;
	unsigned			prec : 1;
}						t_flags;

int						ft_printf(const char *format, ...);
int						fd_printf(const char *format, ...);
int						pf_str(char **format, char **str, int len);
int						pf_special(char **format, va_list ap, char **str,
		int len);
int						pf_flags(char **format, t_flags *flags);
int						pf_d(va_list ap, t_flags *flags, char **str, int len);
int						pf_u(va_list ap, t_flags *flags, char **str, int len);
int						pf_s(va_list ap, t_flags *flags, char **str, int len);
int						pf_upper_s(va_list ap, t_flags *flags, char **str,
		int len);
int						pf_c(va_list ap, t_flags *flags, char **str, int len);
int						pf_no(t_flags *flags, char **str, int len,
		char **format);
int						pf_p(va_list ap, t_flags *flags, char **str, int len);
int						pf_upper_c(va_list ap, t_flags *flags, char **str,
		int len);
int						pf_base(va_list ap, t_flags *flags, char **str,
		int len);
int						pf_percent(t_flags *flags, char **str, int len);
char					*pf_litoa_base(long n, char *base);
char					*pf_luitoa_base(unsigned long n, char *base);
int						pf_applyflags_nb(char **str, t_flags *flags);
int						pf_applyflags_str(char **str, t_flags *flags);
int						pf_applyflags_x(char **str, t_flags *flags);
int						pf_applyflags_o(char **str, t_flags *flags);
char					*pf_unicode(unsigned int i);

# define GRN			"\e[32m"
# define MAG			"\e[35m"
# define CYN			"\e[36m"
# define GREY			"\e[38;5;246m"
# define ORANGE			"\e[38;5;208m"
# define RED			"\e[38;5;196m"
# define YEL			"\e[38;5;11m"
# define BLUE			"\e[38;5;4m"
# define DBLUE			"\e[38;5;21m"
# define PINK			"\e[38;5;13m"
# define RESET			"\e[0m"

#endif
