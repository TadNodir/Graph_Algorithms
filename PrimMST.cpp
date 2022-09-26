#include "PrimMST.h"
#include <iostream>

/**
 * Erstellt einen MST zum Graph G mit dem Prim Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 * \param[in]  s		Startknoten
 */
PrimMST::PrimMST(EdgeWeightedGraph G, int s)
{
	marked.resize(G.getV(), false);
	// lege alle Kanten vom Startknoten 0 ausgehend in die Priority Queue (PQ)
	// setzt voraus, dass G zusammenhaengend ist
	visit(G, s);
	while (!pq.empty()) {
		Edge e = pq.top(); // Hole Kante mit geringstem Gewicht aus PQ
		pq.pop(); // entferne diese Kante aus PQ
		int v = e.either(); // Knoten 1 der Kante
		int w = e.other(v); // Knoten 2 der Kante

		// Überspringen, falls beide Knoten im Baum markiert sind
		if (marked[v] && marked[w]) continue; // Zykel-Detektion

		mst.push_back(e); // Füge Kante e zum MSP hinzu
		if (!marked[v]) visit(G, v); // Knoten v oder w zum MSP
		if (!marked[w]) visit(G, w); // hinzufügen
	}
}

/**
 * Markiert Knoten v im Graph G als markiert und fuegt alle Nachbarn zur pq hinzu
 *
 * \param[in]  G		Kantengewichteter-Graph
 * \param[in]  v		Knoten im Graph G
 */
void PrimMST::visit(EdgeWeightedGraph G, int v)
{
	// Markiere Knoten v als besucht
	marked[v] = true;
	std::vector<Edge> edges = G[v]; // liefert alle Kanten ausgehend vom Knoten v

	// Lege alle Kanten von v zu unmarkierten
	// (noch nicht besuchten) Knoten in die PQ ab
	for (int i = 0; i < edges.size(); i++) {
		if (!marked[edges[i].other(v)]) pq.push(edges[i]);
	}
}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> PrimMST::edges() const
{
	return this->mst;
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double PrimMST::weight() const
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
* Gibt den minimalen Spannbaum nach Prim aus
*/
void PrimMST::print()
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
