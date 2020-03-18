/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   music.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: xamartin <xamartin@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/27 17:08:16 by cmerel       #+#   ##    ##    #+#       */
/*   Updated: 2019/05/08 23:40:52 by xamartin    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	init_sound(t_mem *mem)
{
	int i;

	i = 0;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	mem->level->sounds.music1.music = Mix_LoadMUS("sound/doom-song.mp3");
	Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
	mem->level->sounds.shoot1.sound = Mix_LoadWAV("sound/sg552-2.wav");
	mem->level->sounds.reload.sound = Mix_LoadWAV("sound/m3_pump5.wav");
	mem->level->sounds.jump.sound = Mix_LoadWAV("sound/jump2.wav");
	mem->level->sounds.mobshoot.sound = Mix_LoadWAV("sound/gunshot.wav");
	mem->level->sounds.hurt.sound = Mix_LoadWAV("sound/hurt.wav");
	mem->level->sounds.shoot1.channel = ++i;
	mem->level->sounds.reload.channel = ++i;
	mem->level->sounds.jump.channel = ++i;
	mem->level->sounds.mobshoot.channel = ++i;
	mem->level->sounds.hurt.channel = ++i;
}

void	play_music(t_audio m)
{
	Mix_PlayMusic(m.music, -1);
}

void	play_audio(t_audio m)
{
	Mix_PlayChannel(m.channel, m.sound, 0);
}

void	free_audio(t_mem *mem)
{
	Mix_FreeMusic(mem->level->sounds.music1.music);
	Mix_FreeChunk(mem->level->sounds.shoot1.sound);
	Mix_FreeChunk(mem->level->sounds.reload.sound);
	Mix_FreeChunk(mem->level->sounds.jump.sound);
	Mix_FreeChunk(mem->level->sounds.hurt.sound);
	Mix_FreeChunk(mem->level->sounds.mobshoot.sound);
	Mix_CloseAudio();
}
