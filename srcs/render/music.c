/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   music.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: cmerel <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 17:08:16 by cmerel       #+#   ##    ##    #+#       */
/*   Updated: 2019/02/27 17:37:50 by cmerel      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		music(char *path)
{
	t_audio	m;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	m.music = Mix_LoadMUS(path);
	Mix_VolumeMusic(MIX_MAX_VOLUME/5);
	Mix_PlayMusic(m.music, -1);
}

void        audio(char *path)
{
	t_audio   m;

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	m.sound = Mix_LoadWAV(path);
	Mix_VolumeChunk(m.sound, MIX_MAX_VOLUME/1);
	Mix_PlayChannel(1, m.sound, 0);
}

void        free_audio(void)
{
	t_audio m;

	Mix_FreeMusic(m.music);
	Mix_FreeChunk(m.sound);
	Mix_CloseAudio();
}
