
#include <stdbool.h>

typedef struct Scanner Scanner;
struct Scanner {
  char    *input;
  size_t   inputLen;
  size_t   cursor;
  char    *sep;
  bool     isEof;
  char    *lineBuf;
  size_t   lineBufSize;
};

void  ScanInitBuf(Scanner *scan, char *input, char *sep, char *lineBuf, int lineBufSize);
void  ScanInit(Scanner *scan, char *input, char *sep);
bool  ScanHasNext(Scanner *scan);
char* ScanNext(Scanner *scan);
