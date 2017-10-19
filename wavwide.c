//Lucas Sulzbach
//GRR20171595
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define OPTS "ilo~"

int main(int argc, char *argv[])
{
    audio_t AUDIO;
    float k = 1.0;

    AUDIO.INPUT = stdin;
    AUDIO.OUTPUT = stdout;

    TreatArgs(argc, argv, OPTS, &AUDIO.INPUT, &AUDIO.OUTPUT, &k, NULL);

    LoadAudio(&AUDIO);

    if (AUDIO.ChannelNr != 2)
    {
        fprintf(stderr, "O efeito de estereo ampliado so pode ser usado em audios com 2 canais\n");
        exit(EXIT_FAILURE);
    }

    Wide(&AUDIO, k);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}