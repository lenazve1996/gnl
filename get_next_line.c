#include "get_next_line.h"
// #  define	BUFFER_SIZE 42

size_t	ft_strlen(const char *s)
{
	int	length;

	length = 0;
	if (!s)
		return (0);
	while (*s++ != '\0')
		length++;
	return (length);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_length;

	src_length = ft_strlen(src);
	if (dstsize != 0)
	{
		while (dstsize-- > 1 && *src)
		{
			*dst++ = *src++;
		}
		*dst = '\0';
	}
	return (src_length);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	l;
	size_t	m;

	l = 0;
	m = 0;
	while (dst[l] && l < dstsize)
	{
		l++;
	}
	while (src[m] && (l + m + 1) < dstsize)
	{
		dst[l + m] = src[m];
		m++;
	}
	if (l < dstsize)
	{
		dst[l + m] = '\0';
	}
	return (l + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		s2_size;
	int		s1_size;

	if (s2 == NULL)
		return ((char *)s1);
	s2_size = ft_strlen(s2);
	s1_size = ft_strlen(s1);
	new_str = (char *)malloc((s2_size + s1_size + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s1, s1_size + 1);
	ft_strlcat(new_str, s2, s2_size + s1_size + 1);
	return (new_str);
}

char	*ft_clearing_buffer(char *buffer)
{
	free(buffer);
	buffer = NULL;
	return (buffer);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	n;
	size_t			len_s;

	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	else if (len_s - start < len)
		len = len_s - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	n = 0;
	if (substr == NULL)
		return (NULL);
	while (n < len && s[start])
	{
		substr[n++] = s[start++];
	}
	substr[n] = '\0';
	return (substr);
}

char	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	n;
	size_t			len_s;

	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	else if (len_s - start < len)
		len = len_s - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	n = 0;
	if (substr == NULL)
		return (NULL);
	while (n < len && s[start])
	{
		substr[n++] = s[start++];
	}
	substr[n] = '\0';
	free(s);
	s = NULL;
	return (substr);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		n;
	char	*buf;

	len = ft_strlen(s1);
	buf = (char *)malloc(len + 1 * sizeof(char));
	n = 0;
	if (buf == NULL)
		return (NULL);
	while (n <= len)
	{
		buf[n] = s1[n];
		n++;
	}
	return (buf);
}

int		ft_strchr_int(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	//char		*tmp;
	int			read_result;
	int			index;

	line = NULL;
	if (buffer == NULL)
	{
		buffer = (char	*)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer == NULL)
			return(NULL);
		read_result = read(fd, buffer, BUFFER_SIZE);
		if (read_result == 0)
		{
			if (buffer != NULL)
			{
				free(buffer);
				buffer = NULL;
			}
			return (NULL);
		}
		else if (read_result == -1)
			return (NULL);
		buffer[read_result] = '\0';
	}
	index = ft_strchr_int(buffer, '\n');
	if (index == -1)
	{
		line = ft_strdup(buffer);
		free(buffer);
		buffer = NULL;
	}
	else
	{
		line = ft_substr(buffer, 0, index + 1);
		// tmp = ft_substr(buffer, index + 1, ft_strlen(buffer));
		buffer = ft_substr_free(buffer, index + 1, ft_strlen(buffer));
		// buffer = ft_clearing_buffer(buffer);
		// buffer = tmp;
		// tmp = ft_clearing_buffer(tmp);
	}
	if (index == -1)
	{
		line = ft_strjoin(line, get_next_line(fd));
	}
	return(line);
}

// int main()
// {
// 	int	fd;
// 	char	*line;

// 	line = (char *)malloc(1);
// 	fd = open("text.txt", O_RDONLY);
// 	if (fd == -1)
// 		printf("Open failed\n");
// 	while(line)
// 	{
// 		free(line);
// 		line = NULL;
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 	}
// 	free(line);
// 	line = NULL;
// 	close(fd);
// 	return(0);
// }