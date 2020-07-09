#ifndef Huffman_H
#define Huffman_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>


struct statistics {
    int32_t srcsz, compsz, decompsz;
    static const int EXTRADATA = (UCHAR_MAX + 2) * sizeof(int32_t);

    statistics() : srcsz(0), compsz(0), decompsz(0) {}
};

namespace huffman {
    class HuffmanAchiever {
    private:
        class HuffmanTree {
        public:
            class TreeTraversal {
            public:
                TreeTraversal(HuffmanTree &tree) : tree_(tree), pos(tree.root) {}

                TreeTraversal &operator+=(bool bit);

                char operator*() const;

                bool isLeaf() const;

            private:
                HuffmanTree &tree_;
                int pos;
            };

            TreeTraversal begin() { return TreeTraversal(*this); }

            HuffmanTree(std::vector<int32_t> freq);

            void buildCode(int index, std::vector<bool> code);
            std::unordered_map<int, std::vector<bool>> codeTable;

        private:
            class Node {
            public:
                int left, right;

                Node() {};

                Node(int left, int right) : left(left), right(right) {}
            };

            std::vector<Node> tree;
            int root;
        };

    public:
        void compress(std::istream &is, std::ostream &os, statistics &stcs);

        void decompress(std::istream &is, std::ostream &os, statistics &stcs);

    };
}

namespace streams {
    class Istream {
    public:
        Istream(std::istream &is) : is_(is), buf(0), cnt(8) {};

        Istream &operator>>(bool &input);

    private:
        std::istream &is_;
        std::int8_t buf;
        int cnt;
    };

    class Ostream {
    public:
        Ostream(std::ostream &os) : os_(os), buf(0), cnt(0) {};

        ~Ostream();

        Ostream &operator<<(std::vector<bool> output);

    private:
        std::ostream &os_;
        std::int8_t buf;
        int cnt;
    };
}

#endif