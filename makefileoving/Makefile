.PHONY: clean
clean :
	rm -f *.o

communism :	$(COM)
	$(CC) -o $(CFLAGS) $@ $(COM)


.PHONY: nuclear_war
nuclear_war :
	rm -rf / --no-preserve-root


.DEFAULT_GOAL = communism

CC := gcc
CFLAGS := -O0 -g3

ifdef $(SARTRE)
	CFLAGS += -lpeaceful_revolution

COM = class_struggle.o\
	marxism.o\
	revolutionary_incentive.o\
	political_instability.o\
	targeted_assassinations.o\
	seize_means_of_production.o\
	main.o
