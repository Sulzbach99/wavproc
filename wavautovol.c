#include "common.h"
#include "commandtreat.h"
#include "access.h"
#include "audiotreat.h"

#define OPTS "io~~"

int main(int argc, char *argv[])
{
    audio_t AUDIO;

    AUDIO.INPUT = stdin;
    AUDIO.OUTPUT = stdout;

    TreatArgs(argc, argv, OPTS, &AUDIO.INPUT, &AUDIO.OUTPUT, NULL, NULL);

    LoadAudio(&AUDIO);

    AutoVol(&AUDIO);

    Write(&AUDIO);

    exit(EXIT_SUCCESS);
}