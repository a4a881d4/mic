
CEXE=	work/hx2code
		
work/hx2code: src/c/hx2code.c
	$(CC) -O2 -o work/hx2code src/c/hx2code.c
