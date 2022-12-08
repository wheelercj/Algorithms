import heapq


def dijkstra(
    graph: dict[str, list[tuple[str | int]]], start_node: str, target_node: str
) -> tuple[int | list[str]]:
    """Returns a tuple of (0) the cost of and (1) a list of names of the shortest path.

    Here, "shortest" means cheapest, not necessarily fewest edges. Returns an empty
    tuple if a path is not found. Dijkstra's Shortest Path Algorithm requires each edge
    to have a nonnegative cost.

    Parameters
    ----------
    graph : dict[str, list[tuple[str | int]]]
        A graph with weighted edges. The keys are the names of the nodes in the graph,
        and each value is a list of tuples. Each tuple represents one neighbor and has
        two elements: a string of the neighboring node's name, and an integer of the
        cost to go there.
    start_node : str
        The name of the node to start from.
    target_node : str
        The name of the node to go to.
    """
    # This function traverses the graph in kind of a breadth-first way, so a data
    # structure is needed to temporarily hold some data about nodes.
    min_heap: list[tuple[int | str | list[str]]] = [(0, start_node, [start_node])]
    # min_heap is a list of tuples, each with three elements:
    #   1. the total minimum cost to reach a node from the start node (an integer)
    #   2. that node's name (a string)
    #   3. the shortest path up to and including that node (a list of strings)
    # Although it is a list, it is being changed only by the heapq.heappush and
    # heapq.heappop functions so that it behaves like a min heap prioritized by
    # the first element of each tuple (the cost).
    visited_nodes: set[str] = set()
    while min_heap:
        cost, cheapest_node, path = heapq.heappop(min_heap)
        visited_nodes.add(cheapest_node)
        if cheapest_node == target_node:
            return (cost, path)
        for neighbor, neighbor_cost in graph[cheapest_node]:
            if neighbor in visited_nodes:
                continue
            next_cost = cost + neighbor_cost
            next_path = list(path)
            next_path.append(neighbor)
            heapq.heappush(min_heap, (next_cost, neighbor, next_path))
    return ()


graph = {
    "A": [("A", 0), ("B", 3), ("C", 4)],
    "B": [("A", 3), ("B", 0), ("D", 6), ("E", 5)],
    "C": [("A", 4), ("C", 0), ("E", 1)],
    "D": [("B", 6), ("D", 0), ("E", 2), ("Z", 7)],
    "E": [("B", 5), ("C", 1), ("D", 2), ("E", 0), ("Z", 12)],
    "Z": [("D", 7), ("E", 12), ("Z", 0)],
}

distance, path = dijkstra(graph, "A", "Z")
print(f"{distance = }")
assert distance == 14
print(f"{path = }")
assert path == ["A", "C", "E", "D", "Z"]
