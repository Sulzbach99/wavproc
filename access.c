#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "access.h"

// Função que chama um 'malloc' simples, mas verifica se a operação foi bem sucedida antes de prosseguir:
void *Malloc(unsigned int size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        fprintf(stderr, "Erro ao alocar memoria\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// Função que lê o arquivo de áudio, armazenando os dados em seus respectivos campos:
void LoadAudio(audio_t *AUDIO)
{
    signed short Aux;

    AUDIO->ChunkID[4] = AUDIO->Format[4] = AUDIO->SubChunk1ID[4] = AUDIO->SubChunk2ID[4] = 0;

    // Leitura do cabeçalho do arquivo de áudio:
    fread(AUDIO->ChunkID, sizeof(char), 4, AUDIO->INPUT);
    fread(&AUDIO->ChunkSize, sizeof(int), 1, AUDIO->INPUT);
    fread(AUDIO->Format, sizeof(char), 4, AUDIO->INPUT);
    fread(AUDIO->SubChunk1ID, sizeof(char), 4, AUDIO->INPUT);
    fread(&AUDIO->SubChunk1Size, sizeof(int), 1, AUDIO->INPUT);
    fread(&AUDIO->AudioFormat, sizeof(short), 1, AUDIO->INPUT);
    fread(&AUDIO->ChannelNr, sizeof(short), 1, AUDIO->INPUT);
    fread(&AUDIO->SampleRate, sizeof(int), 1, AUDIO->INPUT);
    fread(&AUDIO->ByteRate, sizeof(int), 1, AUDIO->INPUT);
    fread(&AUDIO->BlockAlign, sizeof(short), 1, AUDIO->INPUT);
    fread(&AUDIO->BitsPerSample, sizeof(short), 1, AUDIO->INPUT);
    fread(AUDIO->SubChunk2ID, sizeof(char), 4, AUDIO->INPUT);
    fread(&AUDIO->SubChunk2Size, sizeof(int), 1, AUDIO->INPUT);
    AUDIO->SamplesPerChannel = AUDIO->SubChunk2Size / AUDIO->BlockAlign;

    // Verificação:
    if (strcmp(AUDIO->ChunkID, "RIFF")     ||
        strcmp(AUDIO->Format, "WAVE")      ||
        strcmp(AUDIO->SubChunk1ID, "fmt ") ||
        AUDIO->SubChunk1Size != 16         ||
        AUDIO->AudioFormat != 1             )
    {
        fprintf(stderr, "Arquivo corrompido ou nao suportado\n");
        exit(EXIT_FAILURE);
    }

    // Alocação dinâmica de uma matriz onde cada linha é um canal e cada coluna é uma amostra:
    AUDIO->Data = Malloc(AUDIO->ChannelNr * sizeof(int*));
    for (unsigned int k = 0; k < AUDIO->ChannelNr; k++)
        AUDIO->Data[k] = Malloc(AUDIO->SubChunk2Size / AUDIO->ChannelNr * 2);

    // Leitura de cada elemento da matriz:
    for (unsigned int j = 0; j < AUDIO->SamplesPerChannel; j++)
        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
        {
            fread(&Aux, AUDIO->BitsPerSample / 8, 1, AUDIO->INPUT);
            AUDIO->Data[i][j] = (signed int)Aux;
        }

    fclose(AUDIO->INPUT);
}

// Função que escreve o áudio na saída desejada:
void Write(audio_t *AUDIO)
{
    fwrite(AUDIO->ChunkID, sizeof(char), 4, AUDIO->OUTPUT);
    fwrite(&AUDIO->ChunkSize, sizeof(int), 1, AUDIO->OUTPUT);
    fwrite(AUDIO->Format, sizeof(char), 4, AUDIO->OUTPUT);
    fwrite(AUDIO->SubChunk1ID, sizeof(char), 4, AUDIO->OUTPUT);
    fwrite(&AUDIO->SubChunk1Size, sizeof(int), 1, AUDIO->OUTPUT);
    fwrite(&AUDIO->AudioFormat, sizeof(short), 1, AUDIO->OUTPUT);
    fwrite(&AUDIO->ChannelNr, sizeof(short), 1, AUDIO->OUTPUT);
    fwrite(&AUDIO->SampleRate, sizeof(int), 1, AUDIO->OUTPUT);
    fwrite(&AUDIO->ByteRate, sizeof(int), 1, AUDIO->OUTPUT);
    fwrite(&AUDIO->BlockAlign, sizeof(short), 1, AUDIO->OUTPUT);
    fwrite(&AUDIO->BitsPerSample, sizeof(short), 1, AUDIO->OUTPUT);
    fwrite(AUDIO->SubChunk2ID, sizeof(char), 4, AUDIO->OUTPUT);
    fwrite(&AUDIO->SubChunk2Size, sizeof(int), 1, AUDIO->OUTPUT);

    for (unsigned int j = 0; j < AUDIO->SamplesPerChannel; j++)
        for (unsigned int i = 0; i < AUDIO->ChannelNr; i++)
            fwrite(&AUDIO->Data[i][j], AUDIO->BitsPerSample / 8, 1, AUDIO->OUTPUT);
    
    fclose(AUDIO->OUTPUT);
}