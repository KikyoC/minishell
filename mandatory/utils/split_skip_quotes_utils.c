
#include "../h_files/minishell.h"

t_list	*check_until(char *line, int *j)
{
	t_list	*node;
	int		i;
	char	*str;

	i = 0;
	while (is_operator(line[i]) && line[i])
		i++;
	str = ft_calloc(i + 1, sizeof(char));
	*j += i;
	while (--i >= 0)
		str[i] = line[i];
	node = ft_lstnew(str);
	return (node);
}
