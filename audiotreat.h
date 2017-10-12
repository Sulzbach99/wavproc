#ifndef __AUDIOTREAT__
#define __AUDIOTREAT__

void GetInfo(audio_t AUDIO);
void Rev(audio_t *AUDIO);
void Vol(audio_t *AUDIO, float Volume);
void AutoVol(audio_t *AUDIO);
void Echo(audio_t *AUDIO, float Aten, float Delay);
void Wide(audio_t *AUDIO, float k);
audio_t *CatAudios(audio_t *AUDIO, char AudNum);
audio_t *MixAudios(audio_t *AUDIO, char AudNum);

#endif