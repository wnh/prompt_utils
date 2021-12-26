#include <string.h>
#include <stdlib.h>

#include "scanner.h"

const int DEFAULT_BUFFER_SIZE = 8 * 1024;

void
ScanInitBuf(Scanner *scan, char *input, char *sep, char *lineBuf, int lineBufSize)
{
  scan->input = input;
  scan->inputLen = strlen(input);
  scan->cursor = 0;
  scan->sep   = sep;
  scan->isEof = 0;
  scan->lineBuf = lineBuf;
  scan->lineBufSize = lineBufSize;
}

void
ScanInit(Scanner *scan, char *input, char *sep)
{
  char * lineBuf = (char*)calloc(sizeof(char), DEFAULT_BUFFER_SIZE);
  return ScanInitBuf(scan, input, sep, lineBuf, DEFAULT_BUFFER_SIZE);
}

bool
_InSep(char x, const char *h) {
  int nn = strlen(h);
  for(int i =0; i<nn; i++) {
    if(h[i] == x) return true;
  }
  return false;
}

bool
ScanHasNext(Scanner *scan)
{
  if (scan->isEof) {
    return false;
  }
  int bufCursor = 0;
  // TODO: Break at sequence of characters or a set, or maybe even a set of sequences :o
  while(scan->input[scan->cursor] && !_InSep(scan->input[scan->cursor], scan->sep)) {
    //if(0 == scan->input[scan->cursor]) {
    //  scan->isEof = 1;
    //  return 0;
    //}
    // TODO - is it big enough?
    scan->lineBuf[bufCursor] = scan->input[scan->cursor];
    bufCursor++;
    (scan->cursor)++;
  }
  // we've hit a sep char
  scan->lineBuf[bufCursor++] = 0; // slap a null in the buffer

  // walk to the end of the seps
  while(scan->input[scan->cursor] && _InSep(scan->input[scan->cursor], scan->sep)) {
    (scan->cursor)++;
  }
  // if we're at the end
  if (scan->cursor >= scan->inputLen) {
    scan->isEof = 1;
  }
  // if we never moved from the start.
  if (scan->cursor == 0) {
    return false;
  }
  return true;
}

char*
ScanNext(Scanner *scan)
{
  return scan->lineBuf;
}
