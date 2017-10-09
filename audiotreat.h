#ifndef __AUDIOTREAT__
#define __AUDIOTREAT__

void TreatAudio(audio_t *AUDIO);
audio_t *CatAudios(audio_t *AUDIO, char AudNum);
audio_t *MixAudios(audio_t *AUDIO, char AudNum);

#endif