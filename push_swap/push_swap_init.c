/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:54:11 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/12 13:28:27 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_current_position(t_stack_node *stack)
{
	int	i;
	int	median;

	i = 0;
	median = stack_len(stack) / 2;
	while (stack)
	{
		stack->current_position = i;
		if (i <= median)
			stack->above_median = 1;
		else
			stack->above_median = 0;
		stack = stack->next;
		i++;
	}
}

void	set_target_node(t_stack_node *stack_a, t_stack_node *stack_b)
{
	t_stack_node	*current_a;
	t_stack_node	*target_node;
	long			best_match;

	while (stack_b)
	{
		current_a = stack_a;
		best_match = LONG_MAX;
		while (current_a)
		{
			if (current_a->value > stack_b->value
				&& current_a->value < best_match)
			{
				best_match = current_a->value;
				target_node = current_a;
			}
			current_a = current_a->next;
		}
		if (best_match == LONG_MAX)
			stack_b->target_node = find_smallest(stack_a);
		else
			stack_b->target_node = target_node;
		stack_b = stack_b->next;
	}
}

void	set_price(t_stack_node *stack_a, t_stack_node *stack_b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(stack_a);
	len_b = stack_len(stack_b);
	while (stack_b)
	{
		stack_b->push_price = stack_b->current_position;
		if (!stack_b->above_median)
			stack_b->push_price = len_b - (stack_b->current_position);
		if (stack_b->target_node->above_median)
			stack_b->push_price += stack_b->target_node->current_position;
		else
		{
			stack_b->push_price += len_a
				- (stack_b->target_node->current_position);
		}
		stack_b = stack_b->next;
	}
}

void	set_cheapest(t_stack_node *stack_b)
{
	t_stack_node	*cheapest_node;
	long			cheapest;

	cheapest = LONG_MAX;
	while (stack_b)
	{
		if (stack_b->push_price < cheapest)
		{
			cheapest = stack_b->push_price;
			cheapest_node = stack_b;
		}
		stack_b = stack_b->next;
	}
	cheapest_node->cheapest = 1;
}

void	init_nodes(t_stack_node *stack_a, t_stack_node *stack_b)
{
	set_current_position(stack_a);
	set_current_position(stack_b);
	set_target_node(stack_a, stack_b);
	set_price(stack_a, stack_b);
	set_cheapest(stack_b);
}
