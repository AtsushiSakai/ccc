#include<stdio.h>

extern int mymain(void);

int main(int argc, char **argv){
  int val=mymain();
  /* printf("aaa\n"); */
  printf("%d\n",val);//$B$3$NI=<($5$l$?CM$,!"JV$jCM(B
  return 0;
}
