/* ENCODE.C - Encode message blocks. */

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
#include "blockio.h"
#include "open.h"
#include "mod2sparse.h"
#include "mod2dense.h"
#include "mod2convert.h"
#include "rcode.h"
#include "enc.h"


/* MAIN PROGRAM. */

int main( int argc, char **argv )
{
  char *gen_file,*pchk_file;
  unsigned char *gen;
  int i, j,k,n;
  unsigned char c;
  int len,bl;
  	char fn[128];
 	FILE *fp,*gfp;
  
  gen_file = argv[2];
  sscanf(argv[1],"%d",&bl);

	gfp=fopen(gen_file,"rb");
	
	if (intio_read(gfp)!=('G'<<8)+0x80)
  { fprintf(stderr,"File %s doesn't contain a generator matrix\n",gen_file);
    exit(1);
  }

  if (fread (&type, 1, 1, gfp) != 1) goto error;

  M = intio_read(gfp);
  N = intio_read(gfp);
 
  cols = chk_alloc (N, sizeof *cols);
  rows = chk_alloc (M, sizeof *rows);

  for (i = 0; i<N; i++)
  { cols[i] = intio_read(gfp);
    if (feof(gfp) || ferror(gfp)) goto error;
  }
  if ((G = mod2dense_read(gfp)) == 0) goto error;
  
 if (mod2dense_rows(G)!=M || mod2dense_cols(G)!=N-M) goto error;
 
  
  	sprintf(fn,"data/G%dX%d.code",N/bl,M/bl);
 	printf("write gen to %s\n",fn);
 	
 	
 
	
 	fp=fopen(fn,"wt");
	if( fp==NULL )
	{
		printf("open file error\n");
		return -1;
	}
 	fprintf(fp,"%d %d %d\n ", mod2dense_cols(G)/bl,mod2dense_rows(G)/bl,bl );
 
  len=(bl+7)/8;
  
  gen = chk_alloc( len, sizeof(unsigned char));  
  
  for(i=0;i<mod2dense_rows(G);i+=bl )
  {
  	for( j=0;j<mod2dense_cols(G);j+=bl )
  	{
  		memset(gen,0,len);
  		for( k=0;k<bl;k++ )
  		{
  			c = mod2dense_get(G,i+k,j);
  			c&=1;
  			gen[k/8]|=c<<(k%8);
  		}
  		fprintf(fp,"%d\t%d:\t",i/bl,j/bl);
  		for( k=len-1;k>=0;k-- )
  		{
  			fprintf(fp,"%02x ",gen[k]&0xff);
  		}
  		fprintf(fp,"\n");		
  		
  		fprintf(stdout,"%d\t%d:\t",i/bl,j/bl);
  		for( k=len-1;k>=0;k-- )
  		{
  			fprintf(stdout,"%02x ",gen[k]&0xff);
  		}
  		fprintf(stdout,"\n");		
  		memset(gen,0,len);
  		for( k=0;k<bl;k++ )
  		{
  			c = mod2dense_get(G,i+k,j+1);
  			c&=1;
  			gen[k/8]|=c<<(k%8);
  		}
  		fprintf(stdout,"%d\t%d:\t",i/bl,j/bl);
  		for( k=len-1;k>=0;k-- )
  		{
  			fprintf(stdout,"%02x ",gen[k]&0xff);
  		}
  		fprintf(stdout,"\n");		
  		
  	}
  }  
	fclose(fp);
#if 0   

#endif
error:
		
  return 0;
}



