all: solution.o clique.o graph.o vertex.o main.cpp
	g++ -o main main.cpp solution.o clique.o graph.o vertex.o -w -std=c++11 -Ofast

solution.o: Solution.hpp Solution.cpp 
	g++ -o solution.o -c Solution.cpp -w -std=c++11 -Ofast
	
clique.o: Clique.hpp Clique.cpp 
	g++ -o clique.o -c Clique.cpp -w -std=c++11 -Ofast

graph.o: Graph.hpp Graph.cpp
	g++ -o graph.o -c Graph.cpp -w -std=c++11 -Ofast

vertex.o: Vertex.hpp Vertex.cpp
	g++ -o vertex.o -c Vertex.cpp -w -std=c++11 -Ofast

clean:
	rm -f *.o main

	

1:
	@echo "G=(125, 6963) C125.9.clq"
	./main instancias/C125.9.clq solucoes/C125_res.txt
	gprof main > solucoes/prof_C125.txt

2:
	@echo "G=(200, 17910) gen200_p0.9_44.clq"
	./main instancias/gen200_p0.9_44.clq solucoes/gen200_res.txt
	gprof main > solucoes/prof_gen200.txt
		
3:
	@echo "G=(250, 27984) C250.9.clq"
	./main instancias/C250.9.clq solucoes/C250_res.txt
	gprof main > solucoes/prof_C250.txt

4:
	@echo "G=(378, 70551) MANN_a27.clq"
	./main instancias/MANN_a27.clq solucoes/MANN_a27_res.txt
	gprof main > solucoes/prof_MANN_a27.txt

5:
	@echo "G=(500, 112332) C500.9.clq"
	./main instancias/C500.9.clq solucoes/C500_res.txt
	gprof main > solucoes/prof_C500.txt
	
6:
	@echo "G=(1000, 450079) C1000.9.clq"
	./main instancias/C1000.9.clq solucoes/C1000_res.txt
	gprof main > solucoes/prof_C1000.txt
	
7:
	@echo "G=(1500, 284923) p_hat1500-1.clq"
	./main instancias/p_hat1500-1.clq solucoes/hat1500_res.txt
	gprof main > solucoes/prof_hat1500.txt

8:
	@echo "G=(2000, 1799532) C2000.9.clq"
	./main instancias/C2000.9.clq solucoes/C2000_res.txt
	gprof main > solucoes/prof_C2000.txt	

9:
	@echo "G=(3321,	5506380) MANN_a81.clq"
	./main instancias/MANN_a81.clq solucoes/MANN_a81_res.txt
	gprof main > solucoes/prof_MANN_a81.txt
	
10:
	@echo "G=(4000,	4000268) C4000.5"
	./main instancias/C4000.5.clq  solucoes/C4000_res.txt
	gprof main > solucoes/prof_C4000.txt
	
	
	
	
run: 1 2 3 4 5 6 7 8 9 10