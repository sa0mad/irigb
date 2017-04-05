all: irigb sinetest irigbcap \
 tb_fft \
 tb_time tb_time.splint tb_time.log time.c.gcov tb_time.c.gcov tb_time.valgrind \
 tb_irigb tb_irigb.splint tb_irigb.log irigb.c.gcov tb_irigb.c.gcov tb_irigb.valgrind

sine: sine.c
	gcc -Wall -lm -o sine sine.c

sintab.c: sine
	./sine > sintab.c

sinetest: sinetest.c sintab.h sintab.c irigb.c
	gcc -Wall -lm -o sinetest sinetest.c sintab.c time.c irigb.c

irigb: time.c irigb.c sintab.h sintab.c irigbtest.c
	gcc -Wall -lm -g -o irigb time.c irigb.c irigbtest.c sintab.c

irigbcap: irigbcap.c time.c irigb.c
	gcc -Wall -Wextra -g -lm irigbcap.c time.c irigb.c sintab.c -lasound -o irigbcap

# Test benches

tb_fft: tb_fft.c fft.c fft.h
	gcc -Wall -lm -g -fprofile-arcs -ftest-coverage -o tb_fft tb_fft.c fft.c

tb_time: tb_time.c time.c time.h tb.h
	gcc -Wall -lm -g -fprofile-arcs -ftest-coverage -o tb_time time.c tb_time.c

tb_time.splint: tb_time.c time.c time.h
	splint -exportlocal time.h time.c tb_time.c > tb_time.splint

tb_time.log: tb_time
	./tb_time > tb_time.log
	cat tb_time.log

time.c.gcov: tb_time.log
	gcov time.c

tb_time.c.gcov: tb_time.log
	gcov tb_time.c

tb_time.valgrind: tb_time
	valgrind --log-file=tb_time.valgrind ./tb_time

tb_irigb: tb_irigb.c irigb.c irigb.h time.c time.h sintab.h sintab.c tb.h
	gcc -Wall -lm -g -fprofile-arcs -ftest-coverage -o tb_irigb irigb.c tb_irigb.c time.c sintab.c

tb_irigb.splint: tb_irigb.c irigb.c irigb.h
	splint -exportlocal -temptrans -mustfreefresh irigb.h irigb.c tb_irigb.c > tb_irigb.splint

tb_irigb.log: tb_irigb
	./tb_irigb > tb_irigb.log
	cat tb_irigb.log

irigb.c.gcov: tb_irigb.log
	gcov irigb.c

tb_irigb.c.gcov: tb_irigb.log
	gcov tb_irigb.c

tb_irigb.valgrind: tb_irigb
	valgrind --log-file=tb_irigb.valgrind ./tb_irigb

# Maintenance

clean:
	rm -f *~ sine sinetest irigb *.log *.splint *.gcda *.gcno *.gcov *.valgrind
