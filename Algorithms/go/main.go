package main

import (
	"fmt"
	"math"
	"math/rand"
	"sort"
	"time"
)

type Node struct {
	data  int
	left  *Node
	right *Node
}

func main() {
	rand.Seed(time.Now().UTC().UnixNano())
	// for i := 0; i <= 2; i++ {
	// 	PrintTree(MakeBinaryTree(6))
	// 	fmt.Println()
	// }
	PrintTree(MakeBST(15))
	fmt.Println()
	PrintTree(MakeBST(15))
}

// PrintTree displays a binary tree. The output is left-aligned and each nil is
// represented by a period.
func PrintTree(tree *Node) {
	maxLevelNodes := int(math.Pow(2, float64(GetDepth(tree)+1)))
	q := make(chan *Node, maxLevelNodes)
	q <- tree
	size := len(q)
	foundPtr := true
	done := false
	for foundPtr && !done {
		foundPtr = false
		fmt.Print("  ")
		for i := 0; i < size && !done; i++ {
			select {
			case node := <-q:
				if node == nil {
					fmt.Print(". ")
					q <- nil
					q <- nil
				} else {
					fmt.Print(node.data, " ")
					if node.left != nil || node.right != nil {
						foundPtr = true
					}
					q <- node.left
					q <- node.right
				}
			default:
				done = true
			}
		}
		fmt.Println()
		size = len(q)
	}
}

// GetDepth determines the depth of a binary tree. If given a tree with only
// one node, 1 will be returned.
func GetDepth(tree *Node) int {
	if tree == nil {
		return 0
	}
	return 1 + int(math.Max(
		float64(GetDepth(tree.left)),
		float64(GetDepth(tree.right)),
	))
}

// MakeBinaryTree creates a random binary tree with up to maxLevels levels (and
// 2^maxLevels-1 nodes). Each node holds a random integer in the range
// [0, maxLevels). `rand` must be seeded.
func MakeBinaryTree(maxLevels int) *Node {
	return makeBinaryTree(maxLevels + 1)
}

func makeBinaryTree(maxLevels int) *Node {
	if maxLevels <= 0 || rand.Intn(maxLevels) == 0 {
		return nil
	}
	return &Node{
		data:  rand.Intn(maxLevels),
		left:  makeBinaryTree(maxLevels - 1),
		right: makeBinaryTree(maxLevels - 1),
	}
}

// MakeBST creates a random binary search tree with up to maxNodes nodes. Each
// node holds a random integer in the range [0, maxNodes). `rand` must be
// seeded.
func MakeBST(maxNodes int) *Node {
	numbers := make([]int, rand.Intn(maxNodes))
	for i := 0; i < len(numbers); i++ {
		numbers[i] = rand.Intn(maxNodes)
	}
	sort.Ints(numbers)
	return makeBST(numbers)
}

func makeBST(numbers []int) *Node {
	if len(numbers) == 0 {
		return nil
	}
	i := rand.Intn(len(numbers))
	node := new(Node)
	node.data = numbers[i]
	node.left = makeBST(numbers[:i])
	node.right = makeBST(numbers[i+1:])
	return node
}
