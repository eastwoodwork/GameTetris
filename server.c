#include"server.h"
#include"PublicDef.h"

void clearArray(unsigned char *arr, unsigned char length){
  unsigned char i;
  for(i=0;i<length;i++)
    *(arr+i) = 0;
  
}

void copyArray(unsigned char *desArr,unsigned char *srcArr,unsigned char length){
  unsigned char i;
  for(i=0;i<length;i++)
    *(desArr+i) = *(srcArr+i);
  
}
unsigned char mergeArray(unsigned char *arr,unsigned char length){
  unsigned char i,temp=0;
  for(i=0;i<length;i++){
    temp |= *(arr+i);
  }
  
  return temp;
  
}

void delay_x2(unsigned char x){
	unsigned char i,j;
	for(i=0;i<x;i++)
		for(j=0;j<x;j++);
}