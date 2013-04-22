#include<stdio.h>

void writeCodeByRs( int col, int row, int bl, int rs[]  )
{
	FILE *fp,*fpc;
	int i,j,k;
	char fn[128];
	char fc[128];
	int len=col*7/row;
	int c=0;
	sprintf(fn,"data/code%dX%d.bin",col*bl,row*bl);	
	sprintf(fc,"data/code%dX%d.code",col*bl,row*bl);	
	
	printf("write to %s\n",fn);

	fp=fopen(fn,"wb");
	fpc=fopen(fc,"wt");
	
	fprintf(fpc,"%d\n",col*bl);
	fprintf(fpc,"%d\n",row*bl);
	fprintf(fpc,"%d\n",len);
	
	char *buf = (char *)malloc(sizeof(char)*col*bl);
	
	for( i=0;i<row;i++ )
	{
		for( k=0;k<bl;k++ )
		{
			memset( buf,0,col*bl);
			c=0;
			for( j=0;j<col;j++ )
			{
				int pos = rs[i*col+j];
				if( pos!=bl )
				{
					pos+=k;
					pos%=bl;
					buf[j*bl+pos]=1;
					fprintf(fpc,"%d ",j*bl+pos+1);
					c++;			
				}	
			}
			fwrite(buf,1,col*bl,fp);
			for(;c<len;c++)
				fprintf(fpc,"0 ");
			fprintf(fpc,"\n");
				
		}
	}

	fclose(fp);
	fclose(fpc);
	free(buf);
}

int main( int argc, char *argv[] )
{
  FILE *fpCode;
	int i,j,k;
	int col,row,blockLength;
	int *code;

	fpCode = fopen(argv[1],"rt");
	if( fpCode==NULL )
	{
		fprintf(stderr,"can not open code file\n");
		return -1;	
	}	
	
	fscanf(fpCode,"%d",&row);
	fscanf(fpCode,"%d",&col);
	fscanf(fpCode,"%d",&blockLength);
	
	code = (int *)malloc(sizeof(int)*row*col);
	
	for( i=0;i<row*col;i++ )
		fscanf(fpCode,"%d",code+i);
	writeCodeByRs( row, col, blockLength, code  );	
	free(code);
	return 0;
}