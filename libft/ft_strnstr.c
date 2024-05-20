#include "libft.h"

// char	*ft_strnstr(const char *big, const char *little, size_t len)
// {
// 	size_t	i;
// 	size_t	j;

// 	if (!little && len < 1)
// 		return ((char *)big);
// 	i = 0;
// 	while (big[i])
// 	{
// 		j = 0;
// 		while (little[j] && big[i + j] == little[j] && i + j < len)
// 			++j;
// 		if (little[j] == 0)
// 			return ((char *)(big + i));
// 		++i;
// 	}
// 	return (NULL);
// }

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	n;

	if (*little == 0)
		return ((char *)big);
	n = ft_strlen(little);
	while (*big && n <= len)
	{
		if (*big == *little && ft_strncmp(big, little, n) == 0)
			return ((char *)big);
		++big;
		--len;
	}
	return (NULL);
}
