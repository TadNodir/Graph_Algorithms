#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <queue>
#include <iostream>

namespace Graphsearch {
	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen G,
		* ab dem Knoten v aus und markiert alle besuchten
		* Knoten in marked.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]	 G			Graph
		* \param[in]	 v			Startknoten
		* \param[in/out] marked		Bereits besuchte Knoten
		* \param[in/out] edgeTo		Vektor mit dem Nachfolgeknoten zu jedem Knoten
		*/
	void DFS_recursive(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		std::cout << v;
		marked[v] = true;
		for (Edge i : G.getAdj(v)) { // Alle adjazenten Kanten von v mit i durchgehen
			int w = i.other(v);  // b Knoten - adjazent zu a aus a -> b
			if (marked[w] == false) {
				edgeTo[w] = v;
				std::cout << " -> ";
				DFS_recursive(G, w, marked, edgeTo);
			}
		}
	}

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		* Starterfunktion zu DFS_recursive(EdgeWeigtedGraph, int, std::vector<bool>, std::vector<int>)
		*
		* \param[in]  G			Graph
		* \param[out] marked	Bereits besuchte Knoten
		* \param[out] edgeTo	Vektor mit dem Nachfolgeknoten zu jedem Knoten
		* \param[in]  v			Startknoten
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		marked.clear();
		edgeTo.clear();
		marked.resize(G.getV(), false);
		edgeTo.resize(G.getV(), -1);
		std::cout << std::endl;
		std::cout << "DFS Reihenfolge: " << std::endl;
		DFS_recursive(G, v, marked, edgeTo);
		std::cout << std::endl;
		for (int i = 0; i < G.getV(); i++) {
			if (marked[i] == false) return false;
		}
		return true;
	}

	/**
		* Fuehrt eine iterative Breitensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]  G			Graph
		* \param[in]  v			Startknoten
		* \param[out] marked	Gibt an welche Knoten besucht wurden bei der Suche
		* \param[out] edgeTo	Gibt den Nachfolgerknoten eines Knoten an
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/
	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		marked.clear();
		edgeTo.clear();
		std::cout << std::endl;
		std::cout << "BFS Reihenfolge : " << std::endl;
		marked.resize(G.getV(), false);
		edgeTo.resize(G.getV(), -1);
		std::queue<int> q;
		q.push(v);
		while (!q.empty()) {
			v = q.front();
			q.pop();
			if (marked[v]) {
				continue;
			}
			std::cout << v << " -> ";
			marked[v] = true;
			for (Edge i : G.getAdj(v)) {
				int w = i.other(v);
				if (marked[w] == false) {
					if (edgeTo[w] == -1) edgeTo[w] = v;
					q.push(w);
				}
			}
		}
		std::cout << std::endl;
		for (int i = 0; i < G.getV(); i++) {
			if (marked[i] == false) return false;
		}
		return true;
	}
}
