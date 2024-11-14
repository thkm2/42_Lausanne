/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:53:04 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/12 13:29:56 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_both(t_stack_node **stack_a, t_stack_node **stack_b,
					t_stack_node *cheapest_node)
{
	while (*stack_a != cheapest_node->target_node && *stack_b != cheapest_node)
		rr(stack_a, stack_b);
	set_current_position(*stack_a);
	set_current_position(*stack_b);
}

void	reverse_rotate_both(t_stack_node **stack_a, t_stack_node **stack_b,
							t_stack_node *cheapest_node)
{
	while (*stack_a != cheapest_node->target_node && *stack_b != cheapest_node)
		rrr(stack_a, stack_b);
	set_current_position(*stack_a);
	set_current_position(*stack_b);
}

void	finish_rotation(t_stack_node **stack, t_stack_node *top_node, char name)
{
	while (*stack != top_node)
	{
		if (name == 'a')
		{
			if (top_node->above_median)
				ra(stack);
			else
				rra(stack);
		}
		else if (name == 'b')
		{
			if (top_node->above_median)
				rb(stack);
			else
				rrb(stack);
		}
	}
}

void	move_nodes(t_stack_node **stack_a, t_stack_node **stack_b)
{
	t_stack_node	*cheapest_node;

	cheapest_node = return_cheapest(*stack_b);
	if (cheapest_node->above_median && cheapest_node->target_node->above_median)
		rotate_both(stack_a, stack_b, cheapest_node);
	else if (!(cheapest_node->above_median)
		&& !(cheapest_node->target_node->above_median))
		reverse_rotate_both(stack_a, stack_b, cheapest_node);
	finish_rotation(stack_a, cheapest_node->target_node, 'a');
	finish_rotation(stack_b, cheapest_node, 'b');
	pa(stack_a, stack_b);
}

void	push_swap(t_stack_node **stack_a, t_stack_node **stack_b)
{
	int				len_a;
	t_stack_node	*smallest_node;

	len_a = stack_len(*stack_a);
	while (len_a-- > 3)
		pb(stack_a, stack_b);
	tiny_sort(stack_a);
	while (*stack_b)
	{
		init_nodes(*stack_a, *stack_b);
		move_nodes(stack_a, stack_b);
	}
	set_current_position(*stack_a);
	smallest_node = find_smallest(*stack_a);
	if (smallest_node->above_median)
		while (*stack_a != smallest_node)
			ra(stack_a);
	else
		while (*stack_a != smallest_node)
			rra(stack_a);
}
