#pragma once
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

namespace Dijkstra
{
	// A graph vertex.
	template <class Name, class Cost>
	struct Node
	{
		Name name{};  // The node's identifier.
		Cost cost{};  // The minimum cost/weight/distance to reach this node from the start node.
		std::vector<Name> path;  // The names of the shortest path's nodes up to and NOT including this node.
		Node() {}
		Node(Name name, Cost cost) : name{ name }, cost{ cost } {}
		Node(Name name, Cost cost, std::vector<Name> path) : name{ name }, cost{ cost }, path{ path } {}
	};

	// A comparator that determines whether one node has a greater cost than another.
	template <class Name, class Cost>
	struct IsGreater
	{
		bool operator()(Node<Name, Cost> left, Node<Name, Cost> right)
		{
			return left.cost > right.cost;
		}
	};

	// A type alias for describing a graph using a map.
	template <class Name, class Cost>
	using GraphMap = std::map<Name, std::vector<Node<Name, Cost>>>;

	// A type alias for a priority queue implemented as a min heap prioritizing lower cost.
	template <class Name, class Cost>
	using MinHeap = std::priority_queue<Node<Name, Cost>, std::vector<Node<Name, Cost>>, IsGreater<Name, Cost>>;

	// The total cost and vertex names of a path through a graph.
	template <class Name, class Cost>
	struct Path
	{
		std::vector<Name> path;
		Cost cost;
		Path(std::vector<Name> path, Cost cost) : path{ path }, cost{ cost } {}
	};

	// Finds the shortest path between two vertexes in a graph.
	// Returns the shortest path's vertex names and total cost.
	// Throws std::invalid_argument if there is no valid path.
	// Each edge must have a nonnegative cost.
	template <class Name, class Cost>
	Path<Name, Cost> dijkstra(GraphMap<Name, Cost> graph, Name start, Name end)
	{
		MinHeap<Name, Cost> min_heap{};
		min_heap.push(Node<Name, Cost>(start, 0));
		std::set<Name> visited_nodes;
		while (min_heap.size())
		{
			Node<Name, Cost> closest_node = min_heap.top();
			min_heap.pop();
			visited_nodes.insert(closest_node.name);
			if (closest_node.name == end)
			{
				Path<Name, Cost> result(closest_node.path, closest_node.cost);
				result.path.push_back(closest_node.name);
				return result;
			}
			for (Node<Name, Cost>& neighbor : graph[closest_node.name])
			{
				if (visited_nodes.count(neighbor.name) != 0)
					continue;
				neighbor.cost += closest_node.cost;
				neighbor.path = closest_node.path;
				neighbor.path.push_back(closest_node.name);
				min_heap.push(neighbor);
			}
		}
		throw std::invalid_argument("No path found.");
	}
}
