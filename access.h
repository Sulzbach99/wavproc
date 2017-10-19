//Lucas Sulzbach
//GRR20171595
#ifndef __ACCESS__
#define __ACCESS__

#include <string.h>
#include "common.h"

void *Malloc(unsigned int size);
void LoadAudio(audio_t *AUDIO);
void Write(audio_t *AUDIO);

#endif