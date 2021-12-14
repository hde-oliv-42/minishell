/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-oliv <hde-oliv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:08:31 by hde-oliv          #+#    #+#             */
/*   Updated: 2021/11/09 21:41:22 by hde-oliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUFFER_SIZE 10

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* libc */
/**
 * ft_memset - Fills the first n bytes of the
 * area pointed by s with the int c.
 * 
 * @b: Pointer to the area.
 * @len: Number of bytes to fill.
 * @c: What to write.
 *
 * Return: Pointer to b.
 */
void		*ft_memset(void *b, int c, size_t len);

/**
 * ft_bzero - Fills the first n bytes of the
 * area pointed by s with zeroes.
 * 
 * @s: Pointer to the area.
 * @n: Number of bytes to fill.
 */
void		ft_bzero(void *s, size_t n);

/**
 * ft_memcpy - Copies a memory area to another but
 * only n bytes.
 *
 * Description: Doesn't handle memory overlap.
 * 
 * @dst: Pointer to the area to receive.
 * @src: Pointer to the area to copy.
 * @n: Number of bytes to fill.
 * 
 * Return: Pointer to dst.
 */
void		*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * ft_memccpy - Copies a memory area to another but
 * stops on n bytes or when it founds c.
 *
 * @dst: Pointer to the area to receive.
 * @src: Pointer to the area to copy.
 * @c: Char to use as brake.
 * @n: Number of bytes to fill.
 * 
 * Return: Pointer to dst.
 */
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);

/**
 * ft_memmove - Copies a memory area to another but
 * only n bytes.
 *
 * Description: Handle memory overlap.
 * 
 * @dst: Pointer to the area to receive.
 * @src: Pointer to the area to copy.
 * @n: Number of bytes to fill.
 * 
 * Return: Pointer to dst.
 */
void		*ft_memmove(void *dst, const void *src, size_t len);

/**
 * ft_memchr - Searches for a char in a memory area but
 * only n bytes.
 *
 * @s: Pointer to the area to search.
 * @c: Char to find.
 * @n: Number of bytes to search.
 * 
 * Return: Pointer to the occurrence if finds, NULL if not.
 */
void		*ft_memchr(const void *s, int c, size_t n);

/**
 * ft_memmcmp - Compares two memory areas but only
 * n bytes.
 *
 * @s1: Pointer to first area
 * @s2: 
 * @n: Number of bytes to search.
 * 
 * Return: A pointer to the occurrence if finds, NULL if not.
 */
int			ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * ft_strlen - Process the length of a string.
 *
 * @s: A string.
 *
 * Return: Its length.
 */
size_t		ft_strlen(const char *s);

/**
 * ft_strlcpy - Copies a string to a buffer
 *
 * @dst: The buffer to receive the string.
 * @src: The original string.
 * @dstsize: How many bytes the buffer has.
 *
 * Description: Copies a string to another buffer, the copy is
 * only made on true C strings and it is a safer alternative
 * to strncpy and strcpy, because the result is always null
 * terminated as it copies dstsize - 1 bytes.
 *
 * Return: The size of the string it tried to create.
 */
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * ft_strlcat - Concatenate two strings
 *
 * @dst: The buffer were the concatenation will occur.
 * @src: The string.
 * @dstsize: How many bytes the buffer has.
 *
 * Description: Concatenate a string to another buffer, this process is
 * only made on true C strings and it is a safer alternative
 * to strncat and strcat, because the result is always null
 * terminated as it transfers dstsize - 1 bytes.
 *
 * Return: The size of the string it tried to create.
 */
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * ft_strchr - Searches for the first incidence of a
 * char in a string.
 *
 * @s: String to search.
 * @c: Char to find.
 * 
 * Return: Pointer to the occurrence if finds, NULL if not.
 */
char		*ft_strchr(const char *s, int c);

/**
 * ft_strchr - Searches for the last incidence of a
 * char in a string.
 * 
 * @s: String to search.
 * @c: Char to find.
 * 
 * Return: Pointer to the occurrence if finds, NULL if not.
 */
char		*ft_strrchr(const char *s, int c);

/**
 * ft_strchr - Searches for a substring in a string, but
 * it searches only n bytes.
 * 
 * @haystack: String to search on.
 * @needle: Substring to search.
 * @len: Number of bytes to search.
 * 
 * Return: Pointer to the occurrence if finds, NULL if not.
 */
char		*ft_strnstr(const char *haystack, char *needle, size_t len);

/**
 * ft_strchr - Compares two strings, but only n bytes.
 * 
 * @haystack: String to search on.
 * @needle: Substring to search.
 * @n: Number of bytes to search.
 * 
 * Return: 0 if equal, non-zero if different.
 */
int			ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * ft_atoi - Converts a string to a integer.
 * 
 * @str: String to convert.
 * 
 * Return: Integer resulted from conversion.
 */
int			ft_atoi(const char *str);

/**
 * ft_isalpha - Checks if c is a letter.
 * 
 * @c: Char to check.
 * 
 * Return: 1 if true, 0 if false.
 */
int			ft_isalpha(int c);

/**
 * ft_isdigit - Checks if c is a digit.
 * 
 * @c: Char to check.
 * 
 * Return: 1 if true, 0 if false.
 */
int			ft_isdigit(int c);

/**
 * ft_isalnum - Checks if c is a alphanumeric.
 * 
 * @c: Char to check.
 * 
 * Return: 1 if true, 0 if false.
 */
int			ft_isalnum(int c);

/**
 * ft_isascii - Checks if c is in ascii table.
 * 
 * @c: Char to check.
 * 
 * Return: 1 if true, 0 if false.
 */
int			ft_isascii(int c);

/**
 * ft_isprint - Checks if c is a printable character.
 * 
 * @c: Char to check.
 * 
 * Return: 1 if true, 0 if false.
 */
int			ft_isprint(int c);

/**
 * ft_toupper - Converts a char to uppercase.
 * 
 * @c: Char to convert.
 * 
 * Return: Converted char.
 */
int			ft_toupper(int c);

/**
 * ft_tolower - Converts a char to lowercase.
 * 
 * @c: Char to convert.
 * 
 * Return: Converted char.
 */
int			ft_tolower(int c);

/**
 * ft_calloc - Allocates memory and sets it
 * to zero.
 * 
 * @count: How many items to allocate.
 * @size: Size of each item in bytes.
 * 
 * Return: Pointer to allocated memory.
 */
void		*ft_calloc(size_t count, size_t size);

/**
 * ft_strdup - Allocates a copy of a string.
 *
 * @s1: The string to copy.
 *
 * Return: The new string.
 */
char		*ft_strdup(const char *s1);

/* Additional functions */

/**
 * ft_substr - Allocates a substring.
 *
 * @s: The string to copy part of.
 * @start: Index to begin.
 * @len: Number of bytes to copy. 
 *
 * Return: The new string.
 */
char		*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * ft_strjoin - Allocates a new string that results from
 * the concatenation of two strings.
 *
 * @s1: The first string.
 * @s2: The second string.
 *
 * Return: The new string resulted of the concatenation of
 * the two previous strings.
 *
 * Example:
 *        ft_strjoin("Hello, ", "World!"); --> "Hello, World!"
 */
char		*ft_strjoin(char const *s1, char const *s2);

/**
 * ft_strtrim - Trims off the string all chars in set.
 *
 * @s1: String to trim.
 * @set: A set of chars to trim off.
 *
 * Return: The new allocated string resulted of trimming.
 *
 * Example:
 *        ft_strjoin("abcdHellocabd", "abdc"); --> "Hello"
 */
char		*ft_strtrim(char const *s1, char const *set);

/**
 * ft_split - Splits a string using a delimitator.
 *
 * @s: String to split.
 * @c: Delimitator.
 *
 * Return: An allocated array of allocated substrings.
 *
 * Example:
 *        ft_split("Here comes!", ' '); --> {"Here", "comes!", "\0"}
 */
char		**ft_split(char const *s, char c);

/**
 * ft_itoa - Transforms a integer to a string.
 *
 * @n: Number to transform.
 *
 * Return: An allocated string.
 */
char		*ft_itoa(int n);

/**
 * ft_strmapi - Iterates a string to apply a function.
 *
 * @s: String.
 * @f: Function to apply.
 *
 * Return: A new allocated string.
 */
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * ft_putchar_fd - Sends a char to a fd.
 *
 * @c: Char to send.
 * @fd: Where to send.
 */
void		ft_putchar_fd(char c, int fd);

/**
 * ft_putstr_fd - Sends a string to a fd.
 *
 * @s: String to send.
 * @fd: Where to send.
 */
void		ft_putstr_fd(char *s, int fd);

/**
 * ft_putendl_fd - Sends a string and a \n to a fd.
 *
 * @s: String to send.
 * @fd: Where to send.
 */
void		ft_putendl_fd(char *s, int fd);

/**
 * ft_putendl_fd - Sends an integer to a fd.
 *
 * @n: Number to send.
 * @fd: Where to send.
 */
void		ft_putnbr_fd(int n, int fd);

/* Linked List functions */

/**
 * ft_lstnew - Creates a node.
 *
 * @content: Content to insert.
 *
 * Return: Pointer to the new node.
 */
t_list		*ft_lstnew(void *content);

/**
 * ft_lstadd_front - Put a node in the front of
 * the list.
 *
 * @lst: Pointer to the pointer of the first node.
 * @new: New node to insert.
 */
void		ft_lstadd_front(t_list **lst, t_list *new);

/**
 * ft_lstsize - Counts how many nodes the list
 * has.
 *
 * @lst: Pointer to the first node.
 *
 * Return: How many nodes the list has.
 */
int			ft_lstsize(t_list *lst);

/**
 * ft_lstlast - Finds the last node.
 *
 * @lst: The first node.
 *
 * Return: Pointer to the last node.
 */
t_list		*ft_lstlast(t_list *lst);

/**
 * ft_lstadd_front - Put a node in the end of the
 * list.
 *
 * @lst: Pointer to the pointer of the first node.
 * @new: New node to insert.
 */
void		ft_lstadd_back(t_list **lst, t_list *new);

/**
 * ft_lstdelone - Deletes a node.
 *
 * @lst: Pointer to the node.
 * @del: Function used to delete the content.
 */
void		ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * ft_lstdelone - Deletes the entire list.
 *
 * @lst: Pointer to the pointer of the first node.
 * @del: Function used to delete the content.
 */
void		ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * ft_lstiter - Iterates the list applying a function
 * to every content.
 *
 * @lst: Pointer of the first node.
 * @f: Function used to modify the content.
 */
void		ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * ft_lstmap - Iterates the list applying a function
 * to every content. It creates another one.
 *
 * @lst: Pointer of the first node.
 * @f: Function used to modify the content.
 * @del: Function used to delete the old content.
 */
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* My functions */

/**
 * ft_dfree - Frees an allocated array of allocated arrays.
 *
 * @a: Pointer to allocated array of array.
 * @i: How many arrays it has.
 */
void		ft_dfree(char **a, size_t i);

/**
 * ft_intlen - How many decimal cases a integer has.
 *
 * @i: A number.
 *
 * Return: How many decimal cases it has.
 */
size_t		ft_intlen(int i);

/**
 * ft_isprint - Checks if c is a space character.
 * 
 * @c: Char to check.
 * 
 * Return: 1 if true, 0 if false.
 */
int			ft_isspace(char c);

/**
 * ft_range - Creates an array of numbers
 * between min and max.
 * 
 * @min: Small number.
 * @max: Bigger number.
 * 
 * Return: Allocated integer array.
 */
int			*ft_range(int min, int max);

/**
 * ft_abs - The absolute value of a number.
 * 
 * @n: Number to convert.
 * 
 * Return: Absolute value of n.
 */
int			ft_abs(int n);

/**
 * ft_atoll - Converts a string to a long long integer.
 * 
 * @str: String to convert.
 * 
 * Return: Long long integer resulted from conversion.
 */
long long	ft_atoll(const char *str);

/**
 * get_next_line - Reads a line from a file descriptor
 *
 * @fd: File descriptor to read.
 * @line: A pointer to a string to store the line.
 *
 * Description: Reads an fd and returns a line from it.
 * If it's called in a loop, it'll print the entire file.
 *
 * Return: 1 on success, 0 on EOF, -1 on error.
 */
int			get_next_line(int fd, char **line);

/**
 * ft_printf - Prints a formatted string.
 *
 * @format: The base string.
 *
 * Description: It can handle the following arguments
 * (converter flags) such as c, s, p, d, i, u, x
 * and X, but no flags.
 *
 * Return: The number of chars printed.
 */
int			ft_printf(const char *format, ...);

/**
 * send_output - Send a string to STDOUT.
 *
 * @string: A string.
 *
 * Return: The number of chars printed.
 */
int			send_output(char *string);

/**
 * tag_handler - Deals with the incidence of % in a string.
 *
 * Description: Especific to ft_printf, it's a bad idea to
 * use it on other things.
 *
 * @string: Pointer to a string.
 * @args: A va_list.
 *
 * Return: The number of chars printed.
 */
int			tag_handler(char **string, va_list args);

/**
 * char_handler - Deals with the incidence of the c converter in a string.
 *
 * Description: Especific to ft_printf, it's a bad idea to
 * use it on other things.
 *
 * @args: A va_list.
 *
 * Return: The number of chars printed.
 */
int			char_handler(va_list args);

/**
 * str_handler - Deals with the incidence of the s converter in a string.
 *
 * Description: Especific to ft_printf, it's a bad idea to
 * use it on other things.
 *
 * @args: A va_list.
 *
 * Return: The number of chars printed.
 */
int			str_handler(va_list args);

/**
 * int_handler - Deals with the incidence of the i or d converter in a string.
 *
 * Description: Especific to ft_printf, it's a bad idea to
 * use it on other things.
 *
 * @args: A va_list.
 *
 * Return: The number of chars printed.
 */
int			int_handler(va_list args);

/**
 * uint_handler - Deals with the incidence of the u converter in a string.
 *
 * Description: Especific to ft_printf, it's a bad idea to
 * use it on other things.
 *
 * @args: A va_list.
 *
 * Return: The number of chars printed.
 */
int			uint_handler(va_list args);

/**
 * ptr_handler - Deals with the incidence of the p converter in a string.
 *
 * Description: Especific to ft_printf, it's a bad idea to
 * use it on other things.
 *
 * @args: A va_list.
 *
 * Return: The number of chars printed.
 */
int			ptr_handler(va_list args);

/**
 * hex_handler - Deals with the incidence of the x converter in a string.
 *
 * Description: Especific to ft_printf, it's a bad idea to
 * use it on other things.
 *
 * @args: A va_list.
 *
 * Return: The number of chars printed.
 */
int			hex_handler(char converter, va_list args);

/**
 * percent_handler - Deals with the incidence of double % converters in a string.
 *
 * Description: Especific to ft_printf, it's a bad idea to
 * use it on other things.
 *
 * @args: A va_list.
 *
 * Return: The number of chars printed.
 */
int			percent_handler(void);

#endif
