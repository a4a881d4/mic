
#site=10.0.64.18:8080

site=10.0.64.18:8080

curl -X POST http://${site}/cmd/0 -d "encP=work/encode
	&pchk=work/code6048X4032.pchk
	&gen=work/code6048X4032.gen
	&src=work/source2016.src
	&encodeO=-
	&order=encP,pchk,gen,src,encodeO
	"
curl -X POST http://${site}/cmd/1 -d "transP=work/transmit
	&encodeO=-
	&transO=-
	&seed=1
	&channel=awgn
	&sigm=0.650198
	&punch=0.5
	&order=transP,encodeO,transO,seed,channel,sigm,punch
	"
curl -X POST http://${site}/cmd/2 -d "decP=work/decode
	&pchk=work/code6048X4032.pchk
	&transO=-
	&decodeO=-
	&channel=awgn
	&sigm=0.650198
	&method=prprp
	&maxI=32
	&order=decP,pchk,transO,decodeO,channel,sigm,method,maxI
	"
curl -X POST http://${site}/cmd/3 -d "verP=work/verify
	&pchk=work/code6048X4032.pchk
	&decodeO=-
	&gen=work/code6048X4032.gen
	&src=work/source2016.src
	&order=verP,pchk,decodeO,gen,src
	"
curl -X POST http://${site}/cmd/4 -d "outP=awk
	&swith=-f
	&awkfile=src/bash/an.awk
	&order=outP,swith,awkfile
	&pipe=stderr
	"	
