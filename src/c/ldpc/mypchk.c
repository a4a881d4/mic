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
 	
 	long int codeLen,checkLen;
 	
 
 	
 	pchk_file = argv[3];
	
	sscanf(argv[1],"%ld",&codeLen);
	sscanf(argv[2],"%ld",&checkLen);
	
  sprintf(fn,"data/code%dX%d.bin",codeLen,checkLen);
  
  T = mod2sparse_allocate( checkLen, codeLen );
    
  code=malloc(codeLen);
	
	printf(" read from %s\n",fn);
	fp=fopen(fn,"rb");
	if( fp==NULL )
	{
		printf("open file error\n");
		return -1;
	}
	
  mod2sparse_clear( T );
  for( i=0;i<checkLen;i++ )
  {
  	fread(code,1,codeLen,fp);
  	for( j=0;j<codeLen;j++ )
  	{
  		if( code[j] )
  			mod2sparse_insert( T, i, j );
  	}
  }
  fclose(fp);

  
  fp = open_file_std(pchk_file,"wb");
  if (fp==NULL) 
  { fprintf(stderr,"Can't create parity check file: %s\n",pchk_file);
    exit(1);
  }

  intio_write(fp,('P'<<8)+0x80);
  
  if (ferror(fp) || !mod2sparse_write(fp,T) || fclose(fp)!=0)
  { fprintf(stderr,"Error writing to parity check file %s\n",pchk_file);
    exit(1);
  }
  
  free(code);
  
  
  return 0;
}


