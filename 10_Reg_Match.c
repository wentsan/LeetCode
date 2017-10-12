#include <stdio.h>
#include <string.h>

#ifndef bool
typedef enum {
  false,
  true
}bool;
#endif

#define LENGTH 256

bool isMatch1(const char *s, const char *p){
  if (!*p)
    return (!*s);
    
  if ('*' == *(p + 1)) {
    // x* matches empty string or at least one character: x* -> xx*
    // *s is to ensure s is non-empty
    return (isMatch1(s, p + 2) || *s && (*s == *p || '.' == *p) && isMatch1(s + 1, p));
  } else {
    if (!*s)
      return false;
    return (*s == *p || '.' == *p) ? isMatch1(s + 1, p + 1) : false;
  }
}

bool isMatch2(const char *s, const char *p) {
  int i, j;
  int m = strlen(s);
  int n = strlen(p);

  /**
   * b[i + 1][j + 1]: if s[0..i] matches p[0..j]
   * if p[j] != '*'
   * b[i + 1][j + 1] = b[i][j] && s[i] == p[j]
   * if p[j] == '*', denote p[j - 1] with x,
   * then b[i + 1][j + 1] is true iff any of the following is true
   * 1) "x*" repeats 0 time and matches empty: b[i + 1][j -1]
   * 2) "x*" repeats 1 time and matches x: b[i + 1][j]
   * 3) "x*" repeats >= 2 times and matches "x*x": s[i] == x && b[i][j + 1]
   * '.' matches any single character
   */
  bool b[m + 1][n + 1];
  b[0][0] = true;
  for (i = 0; i < m; i++) {
      b[i + 1][0] = false;
  }
  // p[0..j - 2, j - 1, j] matches empty iff p[j] is '*' and p[0..j - 2] matches empty
  for (j = 0; j < n; j++) {
      b[0][j + 1] = j > 0 && '*' == p[j] && b[0][j - 1];
  }

  for (i = 0; i < m; i++) {
      for (j = 0; j < n; j++) {
          if (p[j] != '*') {
              b[i + 1][j + 1] = b[i][j] && ('.' == p[j] || s[i] == p[j]);
          } else {
              b[i + 1][j + 1] = b[i + 1][j - 1] && j > 0 || b[i + 1][j] ||
                          b[i][j + 1] && j > 0 && ('.' == p[j - 1] || s[i] == p[j - 1]);
          }
      }
  }
  return b[m][n];
}

int main(int argc, char *argv[])
{
  char s[LENGTH], p[LENGTH], t[16];
  bool result1 = false, result2 = false;
  
  while (true){
    printf ("Enter a string: ");
    fgets(s, LENGTH, stdin);
    printf ("Enter a pattern: ");
    fgets(p, LENGTH, stdin); 
     
    result1 = isMatch1(s, p);
    result2 = isMatch2(s, p);
    printf ("result1: %s\n", result1 == true ? "true" : "false");
    printf ("result2: %s\n", result2 == true ? "true" : "false");
    printf ("continue?[y/n]: ");
    fgets(t, 16, stdin);
    if (t[0] == 'n')
      break;
  }
  
  return 0;
}
