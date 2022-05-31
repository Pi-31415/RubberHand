#define SPTR_SIZE   20
char   *sPtr [SPTR_SIZE];

int
separate (
  String str,
  char   **p,
  int    size )
{
  int  n;
  char s [100];

  strcpy (s, str.c_str ());

  *p++ = strtok (s, " ");
  for (n = 1; NULL != (*p++ = strtok (NULL, " ")); n++)
    if (size == n)
      break;

  return n;
}

String  str = "m1 a300 s220 d500";

void
setup (void) {
  Serial.begin (115200);

  Serial.println (str);

  int N = separate (str, sPtr, SPTR_SIZE);
  for (int n = 0; n < N; n++)
    Serial.println (sPtr [n]);
}

void
loop (void) {
}