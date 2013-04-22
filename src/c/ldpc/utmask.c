/* PRINT-PCHK.C - Print the parity check matrix for a code. */

/* Copyright (c) 2000, 2001 by Radford M. Neal 
 *
 * Permission is granted for anyone to copy, use, modify, or distribute this
 * program and accompanying programs and documents for any purpose, provided 
 * this copyright notice is retained and prominently displayed, along with
 * a note saying that the original programs are available from Radford Neal's
 * web page, and note is made of any changes made to the programs.  The
 * programs and documents are distributed without any warranty, express or
 * implied.  As the programs were written for research purposes only, they have
 * not been tested to the degree that would be advisable in any important
 * application.  All use of these programs is entirely at the user's own risk.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rand.h"
#include "alloc.h"
#include "open.h"
#include "mod2sparse.h"
#include "mod2dense.h"
#include "mod2convert.h"
#include "rcode.h"


int main
( int argc,
  char **argv
)
{
  mod2dense *D,*Z,*G;
  mod2sparse *T;
	int *a_col,*a_row;
	int *cols2;
  char *pchk_file;
 	char fn[128];
 	char *code;
 	FILE *fp;
 	
 	int i,j,n;
 	int a,b,c;
 	
 	int codeLen,checkLen, outCodeLen;
 	
 	pchk_file = argv[3];
	
	sscanf(argv[1],"%ld",&codeLen);
	sscanf(argv[2],"%ld",&checkLen);
	sscanf(argv[3],"%ld",&outCodeLen);
	
  sprintf(fn,"data/code%dX%d.bin",codeLen,checkLen);
  
  
  D = mod2dense_allocate( checkLen, outCodeLen );
  
  code=malloc((codeLen+outCodeLen)*checkLen);
	
	printf(" read from %s\n",fn);
	fp=fopen(fn,"rb");
	if( fp==NULL )
	{
		printf("open file error\n");
		return -1;
	}
	fread(code,codeLen*checkLen,1,fp);
	fclose(fp);
	
	outCodeLen-=checkLen;
	
	for( i=0;i<checkLen;i++ )
		for( j=0;j<outCodeLen;j++ )
		{
			code[i*outCodeLen+j]=code[i*codeLen+j];
		}
		

  mod2dense_clear( D );
  for( i=0;i<checkLen;i++ )
  	for( j=0;j<outCodeLen;j++ )
  	{
  		if( code[i*outCodeLen+j] )
  			mod2dense_set( D, i, j+checkLen, 1 );
  	}
  for( i=0;i<checkLen;i++ )
  	mod2dense_set( D, i, i, 1);
  j=0;
  for( i=checkLen/2;i<checkLen;i++ )
  {
  	mod2dense_set( D, j, i, 1);
  	j++;
  }	
  for( i=0;i<checkLen/2;i++ )
  {
  	mod2dense_set( D, j, j+1, 1);
  	j++;
  	if( j==checkLen-1 )
  		break;
  }

	outCodeLen=outCodeLen+checkLen;
	codeLen=outCodeLen;
  Z = mod2dense_allocate( checkLen, checkLen );
  G = mod2dense_allocate( checkLen, checkLen );
  cols=chk_alloc (codeLen, sizeof(int));
  cols2=chk_alloc (codeLen, sizeof(int));
  rows=chk_alloc (checkLen, sizeof(int));
  n=1;
  j=0;
  
	{
		mod2dense_print(stdout,D);
		for( i=0;i<checkLen;i++ )
  	for( j=0;j<codeLen;j++ )
  	{
  		code[i*codeLen+j]=mod2dense_get( D, i, j );
  	}	
  	sprintf(fn,"data/mask%dX%d.bin",codeLen,checkLen);
  	printf(" write to %s\n",fn);
		fp=fopen(fn,"wb");
		if( fp==NULL )
		{
			printf("open file error\n");
			return -1;
		}
		fwrite(code,codeLen*checkLen,1,fp);
		fclose(fp);

	}  	
  T = mod2sparse_allocate( checkLen, codeLen );
  mod2dense_to_sparse( D , T );	
  
 	printf(" sparse:\n");
 	mod2sparse_print(stdout,T); 
 	printf(" end\n");
 	
  free(code);
  
  return 0;
}


