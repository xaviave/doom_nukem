/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   music.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mel-akio <mel-akio@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 17:08:16 by cmerel       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/07 15:10:38 by mel-akio    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		init_sound(t_mem *mem)
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	mem->level->sounds.music1.music = Mix_LoadMUS("sound/doom-song.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
	mem->level->sounds.shoot1.sound = Mix_LoadWAV("sound/sg552-2.wav");
	mem->level->sounds.reload.sound = Mix_LoadWAV("sound/m3_pump5.wav");
	mem->level->sounds.jump.sound = Mix_LoadWAV("sound/jump2.wav");
}

void		play_music(t_audio m)
{
	Mix_PlayMusic(m.music, -1);
}

void		play_audio(t_audio m)
{
	Mix_PlayChannel(1, m.sound, 0);
}

void		free_audio(t_mem *mem)
{
	Mix_FreeMusic(mem->level->sounds.music1.music);
	Mix_FreeChunk(mem->level->sounds.shoot1.sound);
	Mix_FreeChunk(mem->level->sounds.reload.sound);
	Mix_FreeChunk(mem->level->sounds.jump.sound);
	Mix_CloseAudio();
}
