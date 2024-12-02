OUT=main

build:
	gcc ./main1.c -o ${OUT}
	
valgrind: build
	valgrind -s --track-origins=yes --leak-check=full ./${OUT}
