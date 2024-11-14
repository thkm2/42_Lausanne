/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:49:50 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/12 13:24:35 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

///
/* void print_stack(t_stack_node *stack)
{
	if (!stack)
		return ;
	t_stack_node *current = stack;
	printf("Stack from start to end:\n");
	while (current)
	{
		printf("Value: %d\n", current->value);
		current = current->next;
	}
} */

int	main(int ac, char **av)
{
	t_stack_node	*stack_a;
	t_stack_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (ac < 2)
		return (1);
	if (ac == 2)
		stack_init(&stack_a, ft_split(av[1], ' '), 1);
	else
		stack_init(&stack_a, av + 1, 0);
	if (!stack_is_sorted(stack_a))
	{
		if (stack_len(stack_a) == 2)
			sa(&stack_a);
		else if (stack_len(stack_a) == 3)
			tiny_sort(&stack_a);
		else
			push_swap(&stack_a, &stack_b);
	}
	free_stack(&stack_a);
	return (0);
}
