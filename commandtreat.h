#ifndef __COMMANDTREAT__
#define __COMMANDTREAT__

void PreSet(arguments_t *ARGUMENTS);
void SetInputs(arguments_t *ARGUMENTS);
void TreatArgs(int argc, char *argv[], char *POSSIBLE_ARGS, arguments_t *ARGUMENTS, float *Setting1, float *Setting2);

#endif