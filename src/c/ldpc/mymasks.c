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

#define MAXROW 2200

void printCode( char *c,int i, int j, int w,int h, int codeLen, int *cols)
{
	int a,b;
	for( a=j;a<j+h;a++ )
	{
		for( b=i;b<i+w;b++ )
			printf("%d",c[a*codeLen+cols[b]]);
			
		printf("\n");
	}
	printf("\n");
}

int findCode( char *c,int codeL,int checkL,int cur,int find,int *cols)
{
	int i,j,k,l;
	int *count0 = chk_alloc (checkL, sizeof(int));
	int *count1 = chk_alloc (checkL, sizeof(int));
	double min=1024*1024*1024;
	int pos=-1;
	
	memset(	count0,0,sizeof(int)*checkL);
	for( i=0;i<checkL;i++ )
		for( l=0;l<cur;l++ )
			count0[i]+=c[i*codeL+cols[l]];
		for( j=cur;j<codeL;j++ )
		{
			int r=cols[j];
			if( c[find*codeL+r]!=0 )
			{
				memcpy(	count1,count0,sizeof(int)*checkL);
				for( i=0;i<checkL;i++ )
					count1[i]+=c[i*codeL+r];
				int ci[MAXROW];
				for( l=0;l<MAXROW;l++ )
					ci[l]=0;
				for( l=0;l<checkL;l++ )
				{
					ci[count1[l]]++;
				}
				
				double sum=0;
				for( l=0;l<MAXROW;l++ )
					sum+=l*l*ci[l];
				if( pos==-1 )
				{
					min=sum;
					pos=j;	
				}
				if( sum<min )
				{
					min=sum;
					pos=j;
				}
			}		
		}
		return pos;
}

int selectCode( char *c,int codeL,int checkL,int *cols, char *ref)
{
	int i,j,k,r,t,l;
	for( i=0;i<codeL;i++ )
		cols[i]=i;
	for( i=0;i<checkL;i++ )
	{
		
		j=findCode( ref, codeL, checkL, i, i, cols );		
		t=cols[i];
		cols[i]=cols[j];
		cols[j]=t;

		printf("swap %d %d\n",i,j);
				
		for( j=0;j<checkL;j++ )
		{
			if( j==i ) continue;
			if( c[j*codeL+cols[i]]==0 ) continue;
				
			for( k=0;k<codeL;k++ )
			{
				c[j*codeL+cols[k]]^=c[i*codeL+cols[k]];	
			}
		}	
	}
	

	return 0;
}

void eq( char *c, int codeL,int checkL,int *cols )
{
	int i,j;
	int *count = chk_alloc (checkL, sizeof(int));
	for( i=0;i<checkL;i++ )
	{
		count[i]=0;
	}
	for( i=0;i<checkL;i++ )
		for( j=0;j<checkL;j++ )
			count[i]+=c[i*codeL+cols[j]];
	int ci[MAXROW];
	
	
	for( i=checkL;i<codeL;i++ )
	{
		int min=10;
		int pos=-1;
		int r,t;
		for( j=0;j<checkL;j++ )
		{
			if( pos==-1 )
			{
				pos=j;
				min=count[j];
			}
			if( count[j]<min )
			{
				pos=j;
				min=count[j];
			}
		}	
		j=findCode( c, codeL, checkL, i, pos, cols );			
		t=cols[i];
		cols[i]=cols[j];
		cols[j]=t;
		
		for( j=0;j<checkL;j++ )
			count[j]+=c[j*codeL+cols[i]];
		int l;
		for( l=0;l<MAXROW;l++ )
			ci[l]=0;
		for( l=0;l<checkL;l++ )
		{
			ci[count[l]]++;
		}
	}	
}

void changeCode( char *in,char *o, int codeL, int checkL, int *cols)
{
	int i,j,l,k;
	int *count = chk_alloc (checkL, sizeof(int));
	for( i=0;i<checkL;i++ )
	{
		count[i]=0;
	}
	for( i=0;i<checkL;i++ )
		for( j=0;j<checkL;j++ )
			count[i]+=in[i*codeL+cols[j]];
	l=0;
	for( k=6;k>=0;k-- )
	{
		for( i=0;i<checkL;i++ )
		{
			if( count[i]==k )
			{
				memcpy( o+l*codeL,in+i*codeL,codeL );
				l++;	
			}	
		}	
	}
}

void randCode( char *in,char *o, int codeL, int checkL, int seed )
{
	int i,j,l,k;
	if(seed==-1)
	{
		memcpy(o,in,codeL*checkL);
		return;
	}
	rand_seed( seed );
	int *rows = chk_alloc( checkL, sizeof(int) );
	for( i=0;i<checkL;i++ )
		rows[i]=i;
	for( i=0;i<checkL;i++ )
	{
		j=rand_int( checkL );
		l=rows[i];
		rows[i]=rows[j];
		rows[j]=l;
	}	
	for( i=0;i<checkL;i++ )
	{
		memcpy( o+rows[i]*codeL,in+i*codeL,codeL );
	}
}

int main
( int argc,
  char **argv
)
{
  mod2dense *D,*Z,*G,*D0,*D2;
  mod2sparse *T;
	int *a_col,*a_row;
	int *cols2;
  char *pchk_file;
 	char fn[128];
 	char *code0,*code1;
 	FILE *fp;
 	
 	int i,j,n;
 	int a,b,c;
 	
 	int codeLen,checkLen, outCodeLen,seed;
 	int t;
 	
 	pchk_file = argv[3];
	
	sscanf(argv[1],"%d",&codeLen);
	sscanf(argv[2],"%d",&checkLen);
	sscanf(argv[3],"%d",&outCodeLen);
	sscanf(argv[4],"%d",&seed);
	
  sprintf(fn,"data/code%dX%d.bin",codeLen,checkLen);
  
  
  D = mod2dense_allocate( checkLen, outCodeLen );
  
  code0=malloc(codeLen*checkLen);
  code1=malloc(codeLen*checkLen);
  	
	printf(" read from %s\n",fn);
	fp=fopen(fn,"rb");
	if( fp==NULL )
	{
		printf("open file error\n");
		return -1;
	}
	fread(code0,codeLen*checkLen,1,fp);
	fclose(fp);

	randCode(code0, code1,codeLen,checkLen, seed );
	memcpy(code0,code1,codeLen*checkLen);	
		
	cols=chk_alloc (codeLen, sizeof(int));
  cols2=chk_alloc (codeLen, sizeof(int));
  rows=chk_alloc (checkLen, sizeof(int));
  	n=0;
  	selectCode( code1,codeLen,checkLen,cols,code0 );
		
  	while(0)
	{
		selectCode( code1,codeLen,checkLen,cols,code0 );
		int *count = chk_alloc (checkLen, sizeof(int));
		memset(	count,0,sizeof(int)*checkLen);
		int l;
		for( i=0;i<checkLen;i++ )
			for( l=0;l<checkLen;l++ )
				count[i]+=code0[i*codeLen+cols[l]];
		int ci[10];
		for( l=0;l<10;l++ )
			ci[l]=0;
		for( l=0;l<checkLen;l++ )
		{
			ci[count[l]]++;
		}
		for( l=0;l<7;l++ )
			printf("count(%d)=%d\n",l,ci[l]);		
		printf("\n");
		if( (ci[6]+ci[5])==0 )
			break;
		changeCode( code0, code1,codeLen,checkLen,cols);
		memcpy(code0,code1,codeLen*checkLen);
		n++;
		printf("change one %d\n",n);	
	};
	
	if( n>0 )
	{
		printf("this code is single %d .",n);
	}
	eq(code0,codeLen,checkLen,cols );
	
  mod2dense_clear( D );
  for( i=0;i<checkLen;i++ )
  	for( j=0;j<outCodeLen;j++ )
  	{
  		if( code0[i*codeLen+cols[j]] )
  			mod2dense_set( D, i, j, 1 );
  	}
  T = mod2sparse_allocate( checkLen, outCodeLen );
  mod2dense_to_sparse( D , T );	
  
	printf(" sparse:\n");
 	mod2sparse_print(stdout,T); 
	for( i=0;i<outCodeLen;i++ )
		printf("%4d ",cols[i]);


  for( i=0;i<codeLen;i++ )
  	cols[i]=i;
	  
  Z = mod2dense_allocate( checkLen, checkLen );
  G = mod2dense_allocate( checkLen, checkLen );
  n=1;
  j=0;
    
	mod2dense_copycols(D,Z,cols);
	printf("after copy to Z\n");
	
	n=mod2dense_invert_selected(Z,G,rows,cols2);
	printf("inv\n");
	if( n>0 )
	{
		printf("the code is %d singled\n",n);
	}
	for( i=0;i<checkLen;i++ )
  	for( j=0;j<outCodeLen;j++ )
  	{
  		code0[i*outCodeLen+j]=mod2dense_get( D, i, j );
  	}	
  
  sprintf(fn,"data/mask%dX%d.bin",outCodeLen,checkLen);
  printf(" write to %s\n",fn);
	fp=fopen(fn,"wb");
	if( fp==NULL )
	{
		printf("open file error\n");
		return -1;
	}
	fwrite(code0,outCodeLen*checkLen,1,fp);
	fclose(fp);

  free(code0);
  free(code1);
  
  return 0;
}


