/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lloyet <lloyet@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/03 17:56:31 by lloyet       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/03 17:56:31 by lloyet      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../inc/payload.h"

static void				secret_destroy(void *content)
{
	t_secret			*secret;

	secret = (t_secret*)content;
	ft_memdel((void**)&secret);
	return ;
}

static void				secret_show(void *content)
{
	t_secret			*secret;

	secret = (t_secret*)content;
	ft_putstr(secret->msg);
	ft_putstr("\n");
	return ;
}

static t_secret			*new_secret(char *str)
{
	t_secret			*secret;

	if (!(secret = (t_secret*)ft_memalloc(sizeof(t_secret))))
		return (0);
	secret->msg = str;
	return (secret);
}

int						main(void)
{
	t_payload			*p;
	t_node				*iterator;
	t_secret			*secret;

	secret = new_secret("Coucou");
	p = new_payload((void*)secret, &secret_destroy);
	iterator = new_iterator(p);

	secret = new_secret("ca ");
	payload_add(p, iterator, (void*)secret);
	payload_next(p, &iterator);

	secret = new_secret("va ");
	payload_add(p, iterator, (void*)secret);
	payload_next(p, &iterator);

	secret = new_secret("?\n");
	payload_add(p, iterator, (void*)secret);
	payload_next(p, &iterator);

	payload_remove(p, &iterator);

	secret = new_secret("et");
	payload_add(p, iterator, (void*)secret);
 
	secret = new_secret("toi?");
	payload_add(p, iterator, (void*)secret);
	
	payload_iter(p, secret_show);

	ft_putstr("iterator =");
	secret_show(iterator->content);
	ft_putstr("\n");

	payload_remove(p, &iterator);
	payload_remove(p, &iterator);
	payload_remove(p, &iterator);
	payload_remove(p, &iterator);
	payload_remove(p, &iterator);
	payload_remove(p, &iterator);
	payload_remove(p, &iterator);

	ft_putstr("iterator =");
	secret_show(iterator->content);
	ft_putstr("\n");

	printf("size = %d\n", payload_size(p));
	payload_iter(p, secret_show);
	payload_destroy(p);
	return (0);
}
