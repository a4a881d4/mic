COMPILE = $(CC) -c -O   


LDPCEXE=	work/mypchk       \
					work/print-pchk   \
					work/make-gen     \
					work/rand-src     \
					work/encode       \
					work/transmit     \
					work/decode				\
					work/verify	\
					work/print-gen \
					work/make-ldpc \
					work/mymask \
					work/utmask \
					work/mymasks \
					work/mygen \
					work/mytransmit \
					work/guass
					
					
OBJ= work/rcode.o           \
     work/channel.o         \
     work/dec.o             \
     work/enc.o             \
     work/alloc.o           \
     work/intio.o           \
     work/blockio.o         \
     work/check.o           \
     work/open.o            \
     work/mod2dense.o       \
     work/mod2sparse.o      \
     work/mod2convert.o     \
     work/distrib.o         \
     work/rand.o

work/rcode.o: src/c/ldpc/rcode.c
	$(COMPILE) -o work/rcode.o src/c/ldpc/rcode.c

work/channel.o: src/c/ldpc/channel.c
	$(COMPILE) -o work/channel.o src/c/ldpc/channel.c

work/dec.o: src/c/ldpc/dec.c
	$(COMPILE) -o work/dec.o src/c/ldpc/dec.c

work/enc.o: src/c/ldpc/enc.c
	$(COMPILE) -o work/enc.o src/c/ldpc/enc.c

work/alloc.o: src/c/ldpc/alloc.c
	$(COMPILE) -o work/alloc.o src/c/ldpc/alloc.c

work/intio.o: src/c/ldpc/intio.c
	$(COMPILE) -o work/intio.o src/c/ldpc/intio.c

work/blockio.o: src/c/ldpc/blockio.c
	$(COMPILE) -o work/blockio.o src/c/ldpc/blockio.c

work/check.o: src/c/ldpc/check.c
	$(COMPILE) -o work/check.o src/c/ldpc/check.c

work/mod2dense.o: src/c/ldpc/mod2dense.c
	$(COMPILE) -o work/mod2dense.o src/c/ldpc/mod2dense.c

work/mod2sparse.o: src/c/ldpc/mod2sparse.c
	$(COMPILE) -o work/mod2sparse.o src/c/ldpc/mod2sparse.c

work/mod2convert.o: src/c/ldpc/mod2convert.c
	$(COMPILE) -o work/mod2convert.o src/c/ldpc/mod2convert.c

work/distrib.o: src/c/ldpc/distrib.c
	$(COMPILE) -o work/distrib.o src/c/ldpc/distrib.c

work/rand.o: src/c/ldpc/rand.c
	$(COMPILE) -DRAND_FILE=\"`pwd`/randfile\" -o work/rand.o src/c/ldpc/rand.c

work/open.o: src/c/ldpc/open.c 
	$(COMPILE) -o work/open.o src/c/ldpc/open.c

work/mypchk: src/c/ldpc/mypchk.c $(OBJ)
	$(CC) -o work/mypchk $(OBJ) src/c/ldpc/mypchk.c  -lm
	
work/print-pchk: src/c/ldpc/print-pchk.c $(OBJ)
	$(CC) -o work/print-pchk $(OBJ) src/c/ldpc/print-pchk.c -lm 

work/make-gen: src/c/ldpc/make-gen.c $(OBJ)
	$(CC) -o work/make-gen $(OBJ) src/c/ldpc/make-gen.c -lm 

work/rand-src: src/c/ldpc/rand-src.c $(OBJ)
	$(CC) -o work/rand-src $(OBJ) src/c/ldpc/rand-src.c -lm 

work/encode: src/c/ldpc/encode.c $(OBJ)
	$(CC) -o work/encode $(OBJ) src/c/ldpc/encode.c -lm 

work/transmit: src/c/ldpc/transmit.c $(OBJ)
	$(CC) -o work/transmit $(OBJ) src/c/ldpc/transmit.c  -lm

work/decode: src/c/ldpc/decode.c $(OBJ)
	$(CC) -o work/decode $(OBJ) src/c/ldpc/decode.c  -lm

work/verify: src/c/ldpc/verify.c $(OBJ)
	$(CC) -o work/verify $(OBJ) src/c/ldpc/verify.c  -lm

work/print-gen: src/c/ldpc/print-gen.c $(OBJ)
	$(CC) -o work/print-gen $(OBJ) src/c/ldpc/print-gen.c  -lm

work/make-ldpc: src/c/ldpc/make-ldpc.c $(OBJ)
	$(CC) -o work/make-ldpc $(OBJ) src/c/ldpc/make-ldpc.c  -lm

work/mymask: src/c/ldpc/mymask.c $(OBJ)
	$(CC) -o work/mymask $(OBJ) src/c/ldpc/mymask.c  -lm
	
work/utmask: src/c/ldpc/utmask.c $(OBJ)
	$(CC) -o work/utmask $(OBJ) src/c/ldpc/utmask.c  -lm

work/mymasks: src/c/ldpc/mymasks.c $(OBJ)
	$(CC) -o work/mymasks $(OBJ) src/c/ldpc/mymasks.c  -lm

work/mygen: src/c/ldpc/mygen.c $(OBJ)
	$(CC) -o work/mygen $(OBJ) src/c/ldpc/mygen.c -lm

work/mytransmit: src/c/ldpc/mytransmit.c $(OBJ)
	$(CC) -o work/mytransmit $(OBJ) src/c/ldpc/mytransmit.c -lm

work/guass: src/c/ldpc/guass.c $(OBJ)
	$(CC) -o work/guass $(OBJ) src/c/ldpc/guass.c  -lm
				
