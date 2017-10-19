//Lucas Sulzbach
//GRR20171595
#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define OPTS "ilot"

int main(int argc, char *argv[])
{
    audio_t AUDIO;
    float Delay = 1000;
    float Aten = 0.5;

    AUDIO.INPUT = stdin;
    AUDIO.OUTPUT = stdout;

    TreatArgs(argc, argv, OPTS, &AUDIO.INPUT, &AUDIO.OUTPUT, &Aten, &Delay);

    LoadAudio(&AUDIO);

    Echo(&AUDIO, Aten, Delay);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}