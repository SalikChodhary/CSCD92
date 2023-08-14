CC := g++
CFLAGS := -std=c++11

# Targets
all: exercise1 exercise2 exercise3

exercise1:
	$(CC) $(CFLAGS) ex1/*.cpp -o ex1/output

exercise2:
	$(CC) $(CFLAGS) ex2/*.cpp -o ex2/output

exercise3:
	$(CC) $(CFLAGS) ex3/*.cpp -o ex3/output

exercise4:
	$(CC) $(CFLAGS) traffic-model/*.cpp -o traffic-model/output

clean:
	rm -f ex1/output ex2/output ex3/output traffic-model/output