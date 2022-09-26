#include "EdgeWeightedGraph.h"
#include <fstream>
#include <assert.h>
#include <iostream>

/**
 * Erstellt einen Kantengewichteten-Gaph mit V Knoten
 *
 * \param[in]  V		Anzahl der Knoten
 */
EdgeWeightedGraph::EdgeWeightedGraph(int V)
	: V{ V }
	, E{ 0 }
{
	adj.resize(V);
}

/**
* Erstellt einen Kantengewichteten-Gaph anhand der Kantenliste in fname
*
* \param[in]  fname		Dateiname der Kantenliste
*/
EdgeWeightedGraph::EdgeWeightedGraph(std::string filename)
{
	std::ifstream infile(filename);
	int tmp_e = 0;
	infile >> this->V >> tmp_e;

	this->E = 0;

	this->adj.resize(this->V, std::vector<Edge>());

	int v, w;
	double weight;
	while (infile >> v >> w >> weight)
	{
		this->add(Edge(v, w, weight));
	}

	assert(("Missing edges!", tmp_e == this->E));
}
/**
 * Erstellt einen Kantengewichteten-Gaph mit V Knoten und den Kanten in edges
 *
 * \param[in]  V	Anzahl der Knoten
 * \param[in]  E	Kantenliste
 */
EdgeWeightedGraph::EdgeWeightedGraph(int V, std::vector<Edge> E)
{
	this->V = V;
	this->adj.resize(V);

	for (Edge e : E)
	{
		this->add(e);
	}
}

/**
 * Gibt zurueck ob der Knoten v ein gueltiger Knoten im Graph ist
 *
 * \param[in]  v		Knoten
 * \return Gueltigkeit des Knoten
 */
bool EdgeWeightedGraph::validateVertex(int v) const
{
	return v >= 0 && v < this->V;
}

/**
 * Gibt eine Fehlermeldung aus, wenn der Knoten v im Graph nicht gueltig ist
 *
 * \param[in]  v		Knoten
 */
void EdgeWeightedGraph::validateVertexWithError(int v) const
{
	assert(("Vertex is out of bounds!", this->validateVertex(v)));
}

/**
 * Gibt die Anzahl der Knoten zurueck
 *
 * \return Anzahl der Knoten
 */
int EdgeWeightedGraph::getV() const
{
	return this->V;
}

/**
 * Gibt die Anzahl der Kanten zurueck
 *
 * \return Anzahl der Kanten
 */
int EdgeWeightedGraph::getE() const
{
	return this->E;
}

/**
 * Fuegt die Kante e zum Graphen hinzu
 *
 * \param[in]  e	neue Kante
 */
void EdgeWeightedGraph::add(Edge e)
{
	this->validateVertexWithError(e.either());
	this->validateVertexWithError(e.other(e.either()));

	this->adj[e.either()].push_back(e);
	this->adj[e.other(e.either())].push_back(e);

	this->E++;
}

/**
 * Liefert alle benachbarten Kanten zu v
 *
 * \param[in] v Knoten von dem aus gesucht wird
 * \return Vektor mit allen benachbarten Kanten
 */
std::vector<Edge> EdgeWeightedGraph::getAdj(int v) const
{
	std::vector<Edge> neighbors;
	for (auto const& n : adj[v]) {
		neighbors.push_back(n);
	}
	return neighbors;
}

std::vector<std::vector<Edge>> EdgeWeightedGraph::getAdj() const
{
	return this->adj;
}

/**
 * Gibt alle Kanten im Graph zurueck
 *
 * \return Vektor mit allen Kanten im Graph
 */
std::vector<Edge> EdgeWeightedGraph::edges() const
{
	std::vector<Edge> edgeList;
	for (int v = 0; v < this->V; v++)
	{
		int selfLoops = 0;
		for (Edge e : this->adj[v])
		{
			if (e.other(v) > v) {
				edgeList.push_back(e);
			}
			// add only one copy of each self loop (self loops will be consecutive)
			else if (e.other(v) == v) {
				if (selfLoops % 2 == 0) edgeList.push_back(e);
				selfLoops++;
			}
		}
	}
	return edgeList;
}

bool EdgeWeightedGraph::del_Edge(Edge e)
{
	bool del = false;
	std::vector<Edge> list1;
	std::vector<Edge> list2;

	int from = e.either();

	for (int i = 0; i < adj[from].size(); i++) {
		if (from == adj[from][i].either() && e.other(from) != adj[from][i].other(from)) {
			list1.push_back(adj[from][i]);
		}
	}

	adj[from].clear();
	adj[from] = list1;

	int to = e.other(from);

	for (int i = 0; i < adj[to].size(); i++) {
		if (to == adj[to][i].either() && e.other(to) != adj[to][i].other(to)) {
			list2.push_back(adj[to][i]);
		}
	}

	adj[to].clear();
	adj[to] = list2;

	if (list1.size() < adj[from].size() && list2.size() < adj[to].size()) {
		del = true;
	}

	return del;
}

/**
 * Gibt die verbunden Knoten eines Knoten v zurueck
 *
 * \param[in]  v		Knoten
 * \return Verbundene Knoten des Knoten v
 */
const std::vector<Edge> EdgeWeightedGraph::operator[](int v) const
{
	this->validateVertexWithError(v);
	return this->adj[v];
}

/**
	* Gibt den Graphen G auf der Console als Adjazenzliste aus
	*/
void EdgeWeightedGraph::printGraph()
{
	std::vector<std::vector<Edge>> adjList = this->getAdj();
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
