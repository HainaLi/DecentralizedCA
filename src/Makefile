all: ./dca.out ./setup.out
testName=oblivCA

CILPATH=/home/ubuntu/Desktop/obliv-c
ACKPATH=/home/ubuntu/Desktop/absentminded-crypto-kit
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3
./dca.out: $(testName).oc $(testName).c util.c oblivECC.oc $(ACKPATH)/build/lib/liback.a $(CILPATH)/_build/libobliv.a 
	$(CILPATH)/bin/oblivcc $(CFLAGS) -I . -I $(ACKPATH)/src/ $(testName).oc $(testName).c util.c oblivECC.oc $(ACKPATH)/src/obig.oc 
./setup.out: setup.c sha256.c
	gcc -o setup.out -std=c99 setup.c sha256.c -lgmp
clean:
	rm -f a.out setup.out
