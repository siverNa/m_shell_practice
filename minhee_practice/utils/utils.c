#include "../minishell_prec.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

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