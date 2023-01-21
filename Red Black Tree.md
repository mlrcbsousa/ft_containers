# Red Black Tree

Is a specific type of Balanced Search Tree.

## Binary Search Trees review

1.	Ordered, or sorted, binary trees.
2.	Nodes can have 2 subtrees.
3.	Items to the left of a given node are smaller.
4.	Items to the right of a given node are larger.

## Balanced Search Trees review

Guaranteed height of **O(log n)** for **n** items.

# Rules

1.	A node is either `red` or `black`.
2.	The root and leaves (`NIL`) are `black`.
3.	If a node is `red`, then its children are `black`.
4.	All paths from a node to its `NIL` descendants contain the same number of
		`black` nodes.

## Extra notes

1.	Nodes require one storage bit to keep track of color.
2.	The longest path (`root` to farthest `NIL`) is more than twice the length of
		the shortest path (`root` to nearest `NIL`)
		- Shortest path: all `black` nodes
		- Longest path: alternating `red` and `black`

## Operations

1.	Search *O(log n)*
2.	Insert *O(log n)*
3.	Remove *O(log n)*

Insert and Remove require rotation to maintain Rules

Space complexity: *O(n)*

# Rotations

1.	Alters the structure of a tree by rearranging subtrees.
2.	Goal is to decrease the height of the tree.
		- Red-Black trees: maximum height of *O(log n)*
		- larger subtrees up, smaller subtrees down
3.	Does not affect the order of elements.

Complexity `O(1)`, just changing a few pointers.

# Relationships

Parent, Grandparent and Uncle relationships.

```py
parent = z.p
grandparent = z.p.p
uncle = parent == grandparent.left ? grandparent.right : grandparent.left
```

# Insertions

## Strategy

1.	Insert Z and color it `red`
2.	Recolor and rotate nodes to fix violation

Coloring `red` from start makes for easier violation fixes. Doing this might
break Rules 2 & 3 which are easier to fix.

## 4 Scenarios

0.	Z == root 										-> color `black`
1.	Z.uncle == `red`							-> recolor
2.	Z.uncle == `black` (triangle) -> rotate Z.parent
3.	Z.uncle == `black` (line)			-> rotate Z.grandparent & recolor

# Delete

1.	transplant
		- helps us move subtrees within the tree
2.	delete
		- deletes the node
3.	delete_fixup
		- fixes any red-black violations

## transplant(u, v)

Like a swap between 2 nodes.

1.	**u** is root
2.	**u** is left child
2.	**u** is right child

## delete

1.	**left** child is `NIL`
2.	**right** child is `NIL`
3.	**neither** is `NIL`

## delete fixup

If original color is black call `delete_fixup(x)`

W = X.sibling

1.	**w** is `red`
2.	**w** is `black`, and w.left & w.right are `black`
3.	**w** is `black`, and w.left is `red` & w.right is `black`
4.	**w** is `black`, and w.right is `red`

Not exclusive, may do more than one fix per invocation.

Fixes only done if node passed (x) is `black`.

Function always ends with X becoming `black`.