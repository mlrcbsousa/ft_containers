#pragma once

#include <iomanip>

#include "macros.hpp"
#include "tree/Tree.hpp"

#define V_SPACE ' '
#define V_HLINE '-'
#define V_VLINE '|'
#define V_CONTINUE '~'

#define V_DATA_SIZE 4
#define V_BLOCK_SIZE 1

#define V_COLOR_RED "\033[48;5;196;38;5;232m"
#define V_COLOR_BLACK "\033[48;5;232;38;5;231m"
#define V_COLOR_RESET "\033[38;5;220;49m"
#define V_COLOR_FRESET "\033[39;49m"

typedef unsigned long long	Long;

using namespace ft;

struct Visualizer {

private:
	Long	spaces;
	Long	block;
	String	line;

public:
	template <typename T, typename C, typename A>
	explicit Visualizer( Tree<T, C, A> & tree ) { call(tree); }

	Visualizer( void ) { /* no-op */ }
	~Visualizer( void ) { /* no-op */ }

	template <typename T, typename C, typename A>
	void call( Tree<T, C, A> & tree ) {
		std::size_t		h = tree.height();

		spaces = (1 << h) * V_DATA_SIZE + (1 << (h + 1)) * V_BLOCK_SIZE;
		COUT(V_COLOR_RESET);
		for (std::size_t lvl = 0; lvl <= h; ++lvl) {
			block = (spaces - (1 << lvl) * V_DATA_SIZE) / (1 << (lvl + 1));

			visualize(tree.root().base(), lvl);

			LOG(std::endl << line);
			line.clear();
		}
		COUT(V_COLOR_FRESET);
	}

private:
	template <typename T>
	void	visualize( Node<T> *node, int lvl, bool left_child = false ) {
		if (lvl == 0) {
			if (is_leaf_node(node)) {
				String	data = (V_DATA_SIZE < 4 ? "N" : "NULL");

				data = center(data, left_child);
				COUT(String(block, V_SPACE));
				COUT(V_COLOR_BLACK);
				COUT(std::setw(V_DATA_SIZE) << data << V_COLOR_RESET);
				COUT(String(block, V_SPACE));

				line.append(block, V_SPACE);
				line.append(V_DATA_SIZE, V_SPACE);
				line.append(block, V_SPACE);
			} else {
				const int		space_count = block / 2;
				const int		lines_count = block - space_count;
				std::stringstream	ss;

				ss << node->data;
				String			data = ss.str();

				if (data.length() > V_DATA_SIZE) {
					data.erase(V_DATA_SIZE - 1);
					data.append(1, V_CONTINUE);
				}
				data = center(data, left_child);
				COUT(String(space_count, V_SPACE));
				COUT(String(lines_count, V_HLINE));
				COUT((node->color == BLACK ? V_COLOR_BLACK : V_COLOR_RED));
				COUT(std::setw(V_DATA_SIZE) << data << V_COLOR_RESET);
				COUT(String(lines_count, V_HLINE));
				COUT(String(space_count, V_SPACE));

				line.append(space_count, V_SPACE);
				line.append(1, V_VLINE);
				line.append(lines_count - 1, V_SPACE);
				line.append(V_DATA_SIZE, V_SPACE);
				line.append(lines_count - 1, V_SPACE);
				line.append(1, V_VLINE);
				line.append(space_count, V_SPACE);
			}
		} else if (lvl > 0) {
			if (is_leaf_node(node)) {
				for (size_t i = 0; i < (1 << lvl); i++) {
					COUT(String(block, V_SPACE));
					COUT(String(V_DATA_SIZE, V_SPACE));
					COUT(String(block, V_SPACE));

					line.append(block, V_SPACE);
					line.append(V_DATA_SIZE, V_SPACE);
					line.append(block, V_SPACE);
				}
			} else {
				visualize(node->left, lvl - 1, true);
				visualize(node->right, lvl - 1, false);
			}
		}
	}

	String	center( String title, bool left_child = false ) {
		int	offset = V_DATA_SIZE - title.length();

		offset = offset < 0 ? 0 : offset;

		String	right(offset / 2 + (left_child * (offset % 2)), V_SPACE);
		String	left(offset / 2 + (!left_child * (offset % 2)), V_SPACE);

		return (left + title + right);
	}

};