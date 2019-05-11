~~ [ -- PAYLOAD --] ~~

Description: 

	- This library is an extend linked list support ,add / remove / insert features, from multiple iterators and support cycling.

Requirements:

	- libft --> (git clone https://lloyet@bitbucket.org/lloyet/libft.git)

Features:

	- Handle only same type of struct from same paylaod
	- Support 2 directions from iterator
	- Supporte cycling linked list
	- Multi-iterator is handle and have to be declared outside of the payload (in your functions)
	- INSERT / REMOVE is support from an iterator.
	- NEXT / PREV iterations are handle (SEGFAULT from over-extend iterations are NOT protected)

How To:

	1) - Initialize the payload (with your first elem contain into) with function to desrtoy especially this type of element by using:

		t_payload			*new_payload(void *content, void (*destroy)(void *elem));

	2) - Initalize the iterator (which iterate throught the payload) by using:

		t_node				*new_iterator(t_payload *p);

	3) - Insert element to the payload with an iterator by using:

		void				payload_add(t_payload *p, t_node *iterator, void *content);
	
	4) - Remove element from the payload with an iterator by using:

		void				payload_remove(t_payload *p, t_node **iterator);

	5) - Complete iteration's processus from first element of the linked list can be handle by using:

		void				payload_iter(t_payload *p, void (*f)(void *content));

How It Works:

	Read main.c for more exemples.
