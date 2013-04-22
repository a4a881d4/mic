include ldpc.make
include C.make
ldpc:	$(LDPCEXE) $(CEXE)

clean:
	rm -rf work/*;
	rm -f *.stackdump
	rm -f src/c/*.bak
	rm -f *.bak
	rm -f src/c/ldpc/*.bak
	rm -f src/bash/*.bak
	rm $(find . | grep bak)
	rm $(find . | grep ~)
	
