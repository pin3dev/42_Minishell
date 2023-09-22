/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_prompt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivbatist <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:17:35 by ivbatist          #+#    #+#             */
/*   Updated: 2023/09/22 19:18:37 by ivbatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

const char	*get_prompt(int status)
{
	if (status)
		return (YELLOW "cliva_minixHell⚠️ >" RESET);
	else
		return (GREEN "cliva_minixHell😈 >" RESET);
}
