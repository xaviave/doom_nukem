/*********************************************[ -- LIBHOOK --]**********************************************************/

Description: 

	- This library is a minilibx_macos(made by Olivier Crouzet) extend lib which trigger a customizable keyboard composed by keys and mouse buttons.

Requirements:

	- libft --> (git clone https://lloyet@bitbucket.org/lloyet/libft.git)
	- minilibx_macos --> (git clone https://lloyet@bitbucket.org/lloyet/minilibx.git)

Features:

	- Trigger key statement AND NOW rising + falling edge.
	- 64 bits register is using to trigger 64 keys at the same time.
	- Speed optimatized with low-level binary operations (especially for on-board 8/16 bits systems).
	- Support Multi-Threading, multi-tasks and could be implement with interrupt system (ISR).

How To:

	1) - Initialize the keyboard's device (which containing all the MACOS keys and mouse buttons) by using:

		t_keyboard			*new_keyboard(void);

	2) - Initalize the mouse's device (which storing all the mouse's movements) by using:

		t_mouse				*new_mouse(t_keyboard *keyboard);

	3) - Register new keys (keyboard, mouse) with the actual keyboard by using:

		void				register_new_key(t_keyboard *keyboard, int key);
	
	4) - Check the current key's statement of the acutal keyboard by using:

		int					key_is_pressed(t_keyboard *keyboard, int key);

	5) - Check the current key's edge of the acutal keyboard by using:

		int					key_is_rising(t_keyboard *keyboard, int key);
		int					key_is_falling(t_keyboard *keyboard, int key);

	6) - DON'T FORGET to initalize keyboard and mouse hooks by using correct EVENT_ID and EVENTMASK_ID:

		mlx_hook(*mlx_win, MOTIONNOTIFY, POINTERMOTIONMASK, mouse_motion_hook, *mouse);
		mlx_hook(*mlx_win, KEYPRESS, KEYPRESSMASK, key_press_hook, *keyboard);
		mlx_hook(*mlx_win, BUTTONPRESS, BUTTONPRESSMASK, mouse_press_hook, *mouse);
		mlx_hook(*mlx_win, KEYRELEASE, KEYRELEASEMASK, key_release_hook, *keyboard);
		mlx_hook(*mlx_win, BUTTONRELEASE, BUTTONRELEASEMASK, mouse_release_hook, *mouse);

How It Works:

	During keyboard's initalization, a 285 array will be initalize and set as 0.
	This static array will works as an ID directory which store all the registered key's you have.
	When register_new_key funcion is called, an ID counter is automatically increment and store to index
	associated to the registered key.

	Exemple:		
		Key_registered:
			# define KEY_W		13
			# define KEY_Q		12
		
		(ID initalize to 0 at begin)
		Array of ID:
		reg_id[13] = 1; 
		reg_id[12] = 2;
		reg_id[X] = ID + 1;

	When the USER press a key, the function create a mask with this static array of key's ID by moving left side
	'1' to ID's N byte.
	All the check will be perform on a 64 bits REGISTER (uint64_t reg_key).

	Mouse Button are directly link to the keyboard.
