#include "../minishell_prec.h"

int	get_cmdline_len(char **cmdline)
{
	int	i;

	i = 0;
	if (cmdline == NULL)
		return (i);
	while (cmdline[i] != NULL)
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL)
	{
		if (s2 == NULL)
			return (1);
		else
			return (0);
	}
	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (0);
		}
		i++;
	}
	if (s1[i] == s2[i])
		return (1);
	else
		return (0);
}

int	ft_strcmp2(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
