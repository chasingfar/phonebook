CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99
CFLAGS_orig = -O0
CFLAGS_opt  = -O0

EXEC = phonebook_orig phonebook_opt_256 phonebook_opt_512 phonebook_opt_1024 phonebook_opt_2048 phonebook_opt_4096

GIT_HOOKS := .git/hooks/applied
.PHONY: all
all: $(GIT_HOOKS) $(EXEC)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

SRCS_common = main.c

phonebook_orig: $(SRCS_common) phonebook_orig.c phonebook_orig.h
	$(CC) $(CFLAGS_common) $(CFLAGS_orig) \
        -DOUT_FILE="\"$@.txt\""\
		-DIMPL="\"$@.h\"" -o $@ \
		$(SRCS_common) $@.c

phonebook_opt_256: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
	    -DINDEX_SIZE="256"\
        -DOUT_FILE="\"$@.txt\""\
		-DIMPL="\"phonebook_opt.h\"" -o $@ \
		$(SRCS_common) phonebook_opt.c

phonebook_opt_512: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
	    -DINDEX_SIZE="512"\
        -DOUT_FILE="\"$@.txt\""\
		-DIMPL="\"phonebook_opt.h\"" -o $@ \
		$(SRCS_common) phonebook_opt.c

phonebook_opt_1024: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
	    -DINDEX_SIZE="1024"\
        -DOUT_FILE="\"$@.txt\""\
		-DIMPL="\"phonebook_opt.h\"" -o $@ \
		$(SRCS_common) phonebook_opt.c

phonebook_opt_2048: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
	    -DINDEX_SIZE="2048"\
        -DOUT_FILE="\"$@.txt\""\
		-DIMPL="\"phonebook_opt.h\"" -o $@ \
		$(SRCS_common) phonebook_opt.c

phonebook_opt_4096: $(SRCS_common) phonebook_opt.c phonebook_opt.h
	$(CC) $(CFLAGS_common) $(CFLAGS_opt) \
	    -DINDEX_SIZE="4096"\
        -DOUT_FILE="\"$@.txt\""\
		-DIMPL="\"phonebook_opt.h\"" -o $@ \
		$(SRCS_common) phonebook_opt.c

run: $(EXEC)
	echo 3 | sudo tee /proc/sys/vm/drop_caches
	watch -d -t "./phonebook_orig && echo 3 | sudo tee /proc/sys/vm/drop_caches"

cache-test: $(EXEC)
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_orig
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt_256
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt_512
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt_1024
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt_2048
	perf stat --repeat 100 \
		-e cache-misses,cache-references,instructions,cycles \
		./phonebook_opt_4096

output.txt: cache-test calculate
	./calculate $(EXEC)

plot: output.txt
	gnuplot scripts/runtime.gp

calculate: calculate.c
	$(CC) $(CFLAGS_common) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o perf.* \
	      	calculate orig.txt opt.txt output.txt runtime.png
