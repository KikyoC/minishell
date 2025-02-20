#include "../h_files/minishell.h"

void	close_node(t_list *lst)
{
	printf("It will close %i and %i\n", lst->input, lst->output);
	if (lst->input > 2)
		close(lst->input);
	if (lst->output > 2)
		close(lst->output);
}
