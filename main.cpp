#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"
using namespace std;

namespace Graphsearch {
    bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo);
    bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo);
}

int main() {
	// Starte Unit-Tests
	Catch::Session().run();

	unsigned int choice, g_num;
	
	cout << "=======================================" << endl;
	cout << "  Praktikum 5: Graphenalgorithmen:  " << endl;
	cout << "=======================================" << endl;
	cout << "Bitte Graphnummer eingeben(1, 2 oder 3): " << endl;
	while (!(cin >> g_num)) {
		cout << "Keine Graphnummer. Bitte nochmal versuchen: " << endl;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		break;
	}
	while (!(g_num > 0 && g_num < 4)) {
		cout << "Falsche Graphnummer. Bitte zwischen 1 und 3 auswaehlen: " << endl;
	}
	std::string s = std::to_string(g_num);
	EdgeWeightedGraph g("graph" + s + ".txt");
	cout << "1) Ausgabe der Adjazenzliste" << endl;
	cout << "2) Tiefensuche" << endl;
	cout << "3) Breitensuche" << endl;
	cout << "4) MST nach Prim (Eingabe: Startknoten)" << endl;
	cout << "5) MST nach Kruskal" << endl;
	cout << "6) Kuerzeste Wege nach Dijkstra (Eingabe: Startknoten)" << endl;
	cout << "7) Programm beenden" << endl;
	cout << endl;

	while (true) {
		cout << "?> ";
		while (!(cin >> choice)) {
			cout << "False input. Please try again: " << endl;
			cout << "?> ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		if (!(choice > 0 && choice < 8)) {
			cout << "Incorrect input. Please choose between 1 and 7." << endl;
		}
		if (choice == 1) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			g.printGraph();
		}
		else if (choice == 2) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			int startK = 0;
			vector<bool> marked;
			vector<int> edgeTo;
			bool connected = Graphsearch::DFS(g, startK, marked, edgeTo);
		}
		else if (choice == 3) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			int startK = 0;
			vector<bool> marked;
			vector<int> edgeTo;
			bool connected = Graphsearch::BFS(g, startK, marked, edgeTo);
		}
		else if (choice == 4) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			int startK = 0;
			cout << "Bitte Startknoten eingeben: ";
			cin >> startK;
			std::cout << "Minimaler Spannbaum (MST) nach Prim: " << std::endl;
			PrimMST prim(g, startK);
			std::cout << "Gewicht: " << prim.weight() << std::endl;
			std::cout << "Adjazenzliste: " << std::endl;
			prim.print();
		}
		else if (choice == 5) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			
			std::cout << "Minimaler Spannbaum (MST) nach Kruskal: " << std::endl;
			KruskalMST kruskal(g);
			std::cout << "Gewicht: " << kruskal.weight() << std::endl;
			std::cout << "Adjazenzliste: " << std::endl;
			kruskal.print();
		}
		else if (choice == 6) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			int startK, endK;
			cout << "Bitte Startknoten eingeben: ";
			cin >> startK;
			cout << "Bitte Endknoten eingeben: ";
			cin >> endK;
			std::string s = std::to_string(g_num);
			EdgeWeightedDigraph g_dir("graph" + s + ".txt");
			cout << "Gewichtete Kanten des Graphen: " << endl;
			DijkstraSP dijkstra(g_dir, startK);
			g_dir.printGraph();
			cout << "Kuerzester Weg (Dijkstra): " << endl;
			cout << "Start: " << startK << endl;
			cout << "Ziel: " << endK << endl;
			vector<DirectedEdge> path = dijkstra.pathTo(endK);
			cout << "Pfad: ";
			int countWei = 0;
			int last = 0;
			for (DirectedEdge e : path) {
				cout << e.from() << "[" << e.weight() << "] -> ";
				countWei += e.weight();
				last = e.to();
			}
			cout << last << endl;
			cout << "Kosten: " << countWei << endl;
		}
		else if (choice == 7) {
			system("PAUSE");
			return 0;
		}
	}
	return 0;
}