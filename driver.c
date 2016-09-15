#include<stdio.h>

extern int mymain(void);

int main(int argc, char **argv){
  int val=mymain();
  /* printf("aaa\n"); */
  printf("%d\n",val);//この表示された値が、返り値
  return 0;
}
