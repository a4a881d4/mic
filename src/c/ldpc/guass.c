/* TRANSMIT.C - Simulate transmission of bits through a channel. */

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

#include "channel.h"
#include "open.h"
#include "rand.h"

void usage(void);


/* MAIN PROGRAM. */

int main()
{

	FILE *fpNoise;
	fpNoise=fopen("data/guass.dat","wb");
	float *buf = malloc(sizeof(float)*240*256);
	rand_seed(13);
	int blk,i;
	for( blk=0;blk<1000;blk++ )
	{
		for( i=0;i<240*256;i++ )
			buf[i]=rand_gaussian();
		fwrite(buf,sizeof(float),240*256,fpNoise);
	}
	fclose(fpNoise);

  return 0;
}


