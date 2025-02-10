#include "../h_files/minishell.h"

void	close_node(t_list *lst)
{
	if (lst->input > 2)
		close(lst->input);
	if (lst->output > 2)
		close(lst->output);
}
