make: compressT_LOLS.c rle.c
	gcc -o compressT_LOLS compressT_LOLS.c -pthread -lm
	gcc -o compressR_LOLS compressR_LOLS.c -lm
	gcc -o compressR_worker_LOLS compressR_worker_LOLS.c -lm
	
tar:
	tar --exclude-vcs-ignores -cvf asst2.tar
untar:
	tar -xvf asst2.tar