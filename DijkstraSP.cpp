#include <assert.h>
#include "DijkstraSP.h"
#include <iostream>

/**
 * Füge eine Kante mit minimalen Kosten hinzu, die von einem
 * Baumknoten zu einem Nicht-Baumknoten verläuft und deren
 * Ziel w dem Startknoten s am nächsten ist.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  v		Zielknoten
 */
void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
	std::vector<DirectedEdge> edges = G[v]; // adjazente Knoten zum Knoten v
	for (DirectedEdge e : edges)
	{
		int w = e.to();
		if (distToVect[w] > distToVect[v] + e.weight())
		{
			distToVect[w] = distToVect[v] + e.weight();
			edgeTo[w] = e;
			if (pq.contains(w)) pq.change(w, distToVect[w]);
			else pq.push(w, distToVect[w]);
		}
	}
}

/**
 * Fuert den Dijkstra Algorithmus von s, im Graph G aus.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  s		Startknoten
 */
DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
	this->s = s;
	distToVect.resize(G.getV());
	for (int v = 0; v < G.getV(); v++) {
		distToVect[v] = DBL_MAX;
	}
	distToVect[s] = 0.0;

	pq.push(s, 0.0);
	while (!pq.empty()) {
		// Füge immer eine Kante mit minimalen Pfadkosten zu s hinzu
		int min_node = pq.top().value;
		pq.pop();
		// Füge immer eine Kante mit minimalen Pfadkosten zu s der PQ hinzu
		relax(G, min_node);
	}
}

/**
 * Gibt die Distanz von s zum Knoten v zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Summe der Gewichte auf dem Pfad zu v
 */
double DijkstraSP::distTo(int v)
{
	int start = -1, ziel;
	double wei = 0.0;
	while (start != s) {
		ziel = edgeTo[v].to();
		wei += edgeTo[v].weight();
		start = edgeTo[v].from();
		v = start;
	}
	return wei;
}

/**
 * Gibt zurueck ob es einen Pfad zu v von s aus gibt
 *
 * \param[in]  v		Zielknoten
 * \return true, wenn es einen Pfad von s nach v gibt, sonst false
 */
bool DijkstraSP::hasPathTo(int v)
{
	int start, ziel;
	for (int i = 0; i < edgeTo.size(); i++) {
		ziel = edgeTo[v].to();
		start = edgeTo[v].from();
		v = start;
		if (start == s) return true;
	}
	return false;
}

/**
 * Gibt den Pfad von s nach v als Vektor zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Vektor mit allen Kanten des Pfades von s nach v
 */
std::vector<DirectedEdge> DijkstraSP::pathTo(int v)
{
	std::vector<DirectedEdge> path;
	if (!hasPathTo(v)) {
		std::cout << "NO PATH FROM " << s << " TO " << v << std::endl;
		return path;
	}
	int start = -1, ziel;
	double wei;
	while (start != s) {
		ziel = edgeTo[v].to();
		wei = (double) edgeTo[v].weight();
		start = edgeTo[v].from();
		v = start;
		DirectedEdge edge{ start, ziel, wei };
		path.push_back(edge);
	}
	std::reverse(path.begin(), path.end());
	return path;
}
