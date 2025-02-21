
#include "../h_files/minishell.h"

t_list	*check_until(char *line, int *j, char ch, char op)
{
	t_list	*node;
	int		i;
	char	*str;

	i = 0;
	while ((line[i] == op || line[i] == ch) && line[i])
		i++;
	str = ft_calloc(i + 1, sizeof(char));
	*j += i;
	while (--i >= 0)
		str[i] = line[i];
	node = ft_lstnew(str);
	return (node);
}
