#include <iostream>
#include <vector>
#include <algorithm>

class lca_tree
{
    struct segment_tree_node
    {
        size_t min_index;

        size_t left_index;
        size_t right_index;

        segment_tree_node* left_subtree = nullptr;
        segment_tree_node* right_subtree = nullptr;
    };

    size_t num_nodes;

    std::vector<std::vector<int>> children;

    std::vector<int> visit_order;
    std::vector<int> time_in;
    std::vector<int> height;

    segment_tree_node* segment_tree;

public:
    lca_tree(size_t num_nodes) : num_nodes(num_nodes), children(num_nodes), time_in(num_nodes), height(num_nodes) { }

    void pidor()
    {
        for(int u = 0; u < num_nodes; u++) {
            std::cout << u << ": ";

            for(int v : children[u]) {
                std::cout << v << " ";
            }

            std::cout << std::endl;
        }

        std::cout << "Visit order: ";

        for(int v : visit_order) {
            std::cout << v << " ";
        }

        std::cout << std::endl;

        std::cout << "Height: ";

        for(int h : height) {
            std::cout << h << " ";
        }

        std::cout << std::endl;
    }

    void add_edge(int u, int v)
    {
        children[u].push_back(v);
        children[v].push_back(u);
    }

    /**
     * "Hang" the tree by vertex `u` (so that all vectices become unidirectional and all nodes are reachable from `u`),
     * and also preprocessed the tree for least-common-ancestor requests
     * @param u The new root of the tree
     */
    void hang_by_and_preprocess_lca(int u)
    {
        hang_by(u);

        preprocess_lca(u);

        segment_tree = build_segment_subtree(0, visit_order.size() - 1);
    }

private:
    segment_tree_node* build_segment_subtree(size_t l, size_t r)
    {
        segment_tree_node* new_node = new segment_tree_node;

        new_node->left_index = l;
        new_node->right_index = r;

        if(l == r) {
            new_node->min_index = l;
        }
        else {
            size_t mid = (l + r) / 2;

            new_node->left_subtree = build_segment_subtree(l, mid);
            new_node->right_subtree = build_segment_subtree(mid + 1, r);

            if(height[visit_order[new_node->left_subtree->min_index]]
               < height[visit_order[new_node->right_subtree->min_index]]) {
                new_node->min_index = new_node->left_subtree->min_index;
            }
            else {
                new_node->min_index = new_node->right_subtree->min_index;
            }
        }

        return new_node;
    }

    int get_index_with_min_height(size_t left, size_t right, segment_tree_node* node)
    {
        if(left == node->left_index && right == node->right_index) {
            return (int)node->min_index;
        }

        size_t mid = (node->left_index + node->right_index) / 2;

        if(right <= mid) {
            return get_index_with_min_height(left, right, node->left_subtree);
        }
        else if(left > mid) {
            return get_index_with_min_height(left, right, node->right_subtree);
        }
        else {
            int left_min = get_index_with_min_height(left, mid, node->left_subtree);
            int right_min = get_index_with_min_height(mid + 1, right, node->right_subtree);

            if(height[visit_order[left_min]] < height[visit_order[right_min]]) {
                return left_min;
            }
            else {
                return right_min;
            }
        }
    }

    void hang_by(int u)
    {
        for(int v : children[u]) {
            children[v].erase(std::remove(children[v].begin(), children[v].end(), u), children[v].end());

            hang_by(v);
        }
    }

    void preprocess_lca(int root)
    {
        visit_order.reserve(2 * num_nodes);

        record_visit_order(root);

        for(int i = (int)(visit_order.size()) - 1; i >= 0; i--) {
            time_in[visit_order[i]] = i;
        }

        record_height(root, 0);
    }

    void record_visit_order(int u)
    {
        visit_order.push_back(u);

        for(int v : children[u]) {
            record_visit_order(v);

            visit_order.push_back(u);
        }
    }

    void record_height(int u, int current_height)
    {
        height[u] = current_height;

        for(int v : children[u]) {
            record_height(v, current_height + 1);
        }
    }

public:
    int get_lca(int u, int v)
    {
        size_t u_index = (size_t)time_in[u];
        size_t v_index = (size_t)time_in[v];

        int lca_index = get_index_with_min_height(std::min(u_index, v_index), std::max(u_index, v_index), segment_tree);

        return visit_order[lca_index];
    }
};

int main()
{
    size_t num_nodes, num_requests;

    std::cin >> num_nodes >> num_requests;

    lca_tree t(num_nodes);

    for(int u = 1; u < num_nodes; u++) {
        int v;

        std::cin >> v;

        t.add_edge(u, v - 1);
    }

    t.hang_by_and_preprocess_lca(0);

    for(int i = 0; i < num_requests; i++) {
        int u, v, w;

        std::cin >> u >> v >> w;

        std::cout << t.common_edges(u - 1, v - 1, w - 1) << std::endl;
    }
}
