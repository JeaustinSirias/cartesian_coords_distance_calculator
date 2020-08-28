#Jeaustin Sirias Chacon
#Aug 2020


#commands to run

all: build run


build:
	g++ -o lab_2 cardinals.cc

run:	
	./lab_2


####### clear 

.PHONY: clean
clean:
	rm lab_2*
