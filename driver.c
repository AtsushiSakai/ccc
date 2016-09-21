#include<stdio.h>

#define WEAK __attribute__((weak))
//weak$B$rF~$l$k$H<BAu$5$l$F$$$J$$;~$K(B0$B$K$J$k(B

extern int intfn(void) WEAK;
extern char *stringfn(void) WEAK;

int main(int argc, char **argv){

  if(intfn){
    printf("%d\n",intfn());//$B$3$NI=<($5$l$?CM$,!"JV$jCM(B
  }
  else if(stringfn){
    printf("%s\n",stringfn());
  }
  else{
    printf("Should not happen");
  }

  return 0;
}
