testName=oblivCA

CILPATH=/home/hannah/Desktop/obliv-c
ACKPATH=/home/hannah/Desktop/absentminded-crypto
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3
./a.out: $(testName).oc $(testName).c $(CILPATH)/test/oblivc/common/util.c $(ACKPATH)/build/lib/liback.a $(CILPATH)/_build/libobliv.a 
	$(CILPATH)/bin/oblivcc $(CFLAGS) -I . -I $(ACKPATH)/src/ -I $(CILPATH)/test/oblivc/common/ $(testName).oc $(testName).c $(CILPATH)/test/oblivc/common/util.c
clean:
	rm -f a.out