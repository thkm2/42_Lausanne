/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:33:46 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/12 13:28:49 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_stack_node **stack)
{
	t_stack_node	*head;
	t_stack_node	*last_node;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	head = *stack;
	last_node = find_last_node(*stack);
	*stack = last_node;
	last_node->prev->next = NULL;
	last_node->prev = NULL;
	last_node->next = head;
	head->prev = last_node;
}

void	rra(t_stack_node **stack_a)
{
	reverse_rotate(stack_a);
	write(1, "rra\n", 4);
}

void	rrb(t_stack_node **stack_b)
{
	reverse_rotate(stack_b);
	write(1, "rrb\n", 4);
}

void	rrr(t_stack_node **stack_a, t_stack_node **stack_b)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	write(1, "rrr\n", 4);
}
