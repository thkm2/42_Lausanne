/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:11:05 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/12 13:25:44 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack_node	*find_highest_node(t_stack_node *stack)
{
	int				value;
	t_stack_node	*highest;

	value = INT_MIN;
	highest = stack;
	while (stack)
	{
		if (stack->value > value)
		{
			value = stack->value;
			highest = stack;
		}
		stack = stack->next;
	}
	return (highest);
}

t_stack_node	*find_first_node(t_stack_node *stack_node)
{
	while (stack_node->prev)
		stack_node = stack_node->prev;
	return (stack_node);
}

int	stack_is_sorted(t_stack_node *stack)
{
	if (!stack)
		return (0);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	tiny_sort(t_stack_node **stack)
{
	t_stack_node	*highest;

	highest = find_highest_node(*stack);
	if (*stack == highest)
		ra(stack);
	else if ((*stack)->next == highest)
		rra(stack);
	if ((*stack)->value > (*stack)->next->value)
		sa(stack);
}
