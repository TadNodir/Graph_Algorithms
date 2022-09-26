#include "KruskalMST.h"
#include "PriorityQueue.h"
#include <iostream>

/**
 * Erstellt einen MST zum Graph G mit dem Kruskal Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 */
KruskalMST::KruskalMST(EdgeWeightedGraph G)
{
	treeID.resize(G.getV());
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
	std::vector<Edge> e = G.edges(); // liefert alle Kanten von G
	for (int i = 0; i < e.size(); i++) pq.push(e[i]);
	// zu Beginn ist jeder Knoten ein eigener Baum
	for (int i = 0; i < G.getV(); i++) treeID[i] = i;

	while (!pq.empty()) {
		Edge e = pq.top();
		pq.pop();
		int v = e.either(); int w = e.other(v);
		// Wenn Knoten v und w zu unterschiedlichen Bäumen gehört,
			// können diese mit der Kante e ohne Zykel verbunden werden
		if (treeID[v] != treeID[w]) {
			mst.push_back(e);
			int treeID_w = treeID[w];
			for (int i = 0; i < G.getV(); i++) { // BaumID von v und w
				if (treeID[i] == treeID_w) // angleichen
					treeID[i] = treeID[v];
			}

		}
	}
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> KruskalMST::edges() const
{
	return this->mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double KruskalMST::weight() const
{
	double sum = 0;
	for (int i = 0; i < mst.size(); i++)
	{
		int wei = mst[i].weight();
		sum += wei;
	}
	return sum;
}

/*
* Gibt den minimalen Spannbaum nach Kruskal aus
*/
void KruskalMST::print()
{
	std::vector<std::vector<Edge>> adjList;
	adjList.resize(edges().size(), std::vector<Edge>());
	for (int i = 0; i < edges().size(); i++) {
		int v = edges()[i].either();
		int w = edges()[i].other(v);
		int wei = edges()[i].weight();
		Edge e(v, w, wei);
		adjList[v].push_back(e);
	}
	int v = 0;
	int w = 0;
	for (int i = 0; i < adjList.size() - 1; i++)
	{
		std::cout << i;
		for (int j = 0; j < adjList[i].size(); j++)
		{
			v = adjList[i][j].either();
			w = adjList[i][j].other(v);
			if (v >= i) {
				std::cout << "  -> " << w << " [" << adjList[i][j].weight() << "]";
			}
		}
		std::cout << std::endl;
	}
}