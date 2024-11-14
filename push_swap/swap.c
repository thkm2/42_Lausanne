/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgiraud <kgiraud@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:32:41 by kgiraud           #+#    #+#             */
/*   Updated: 2024/11/12 13:26:18 by kgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack_node **stack)
{
	t_stack_node	*head;
	t_stack_node	*next;

	if (!stack || !*stack || stack_len(*stack) < 2)
		return ;
	head = *stack;
	next = head->next;
	*stack = next;
	head->next = next->next;
	head->prev = next;
	next->prev = NULL;
	if (next->next)
		next->next->prev = head;
	next->next = head;
}

void	sa(t_stack_node **stack_a)
{
	swap(stack_a);
	write(1, "sa\n", 3);
}

void	sb(t_stack_node **stack_b)
{
	swap(stack_b);
	write(1, "sb\n", 3);
}

void	ss(t_stack_node **stack_a, t_stack_node **stack_b)
{
	swap(stack_a);
	swap(stack_b);
	write(1, "ss\n", 3);
}
