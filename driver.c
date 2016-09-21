#include<stdio.h>

#define WEAK __attribute__((weak))
//weakを入れると実装されていない時に0になる

extern int intfn(void) WEAK;
extern char *stringfn(void) WEAK;

int main(int argc, char **argv){

  if(intfn){
    printf("%d\n",intfn());//この表示された値が、返り値
  }
  else if(stringfn){
    printf("%s\n",stringfn());
  }
  else{
    printf("Should not happen");
  }

  return 0;
}
