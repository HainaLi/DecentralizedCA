testName=oblivCA

CILPATH=/home/hannah/Desktop/obliv-c
ACKPATH=/home/hannah/Desktop/absentminded-crypto
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3
./a.out: $(testName).oc $(testName).c util.c $(ACKPATH)/build/lib/liback.a $(CILPATH)/_build/libobliv.a 
	$(CILPATH)/bin/oblivcc $(CFLAGS) -I . -I $(ACKPATH)/src/ $(testName).oc $(testName).c util.c $(ACKPATH)/src/obig.oc
clean:
	rm -f a.out
