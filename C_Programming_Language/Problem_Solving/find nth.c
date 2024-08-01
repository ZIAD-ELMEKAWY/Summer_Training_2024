#include <stdio.h>
#include <stdlib.h>

int find_nth_term(int n, int a, int b, int c) {
  int res = a+b+c;
  if (n!=0)
  {
      find_nth_term(res+n, a ,b , c);
  }
  else
  {
      return res;
  }
}

int main() {
    int n, a, b, c;

    scanf("%d %d %d %d", &n, &a, &b, &c);
    int ans = find_nth_term(n, a, b, c);

    printf("%d", ans);
    return 0;
}
