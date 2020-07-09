#include "HuffmnaAchiever.h"

using namespace huffman;
using namespace streams;

HuffmanAchiever::HuffmanTree::HuffmanTree(std::vector<int32_t> freq) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    tree.resize(freq.size());
    for (size_t i = 0; i < freq.size(); i++) {
        if (freq[i]) {
            tree[i] = Node(-1, -1);
            pq.push(std::make_pair(freq[i], i));
        }
    }
    while (pq.size() > 1) {
        std::pair<int, int> m1, m2;
        m1 = pq.top();
        pq.pop();
        m2 = pq.top();
        pq.pop();
        tree.emplace_back(m1.second, m2.second);
        freq.push_back(m1.first + m2.first);
        pq.push(std::make_pair(freq.back(), tree.size() - 1));
    }
    root = pq.top().second;
    buildCode(root, std::vector<bool>());
}

void HuffmanAchiever::HuffmanTree::buildCode(int i, std::vector<bool> code) {
    if (tree[i].left != -1) {
        code.push_back(0);
        buildCode(tree[i].left, code);
        code.pop_back();
        code.push_back(1);
        buildCode(tree[i].right, code);
        code.pop_back();
    } else
        codeTable[i] = code;
}

HuffmanAchiever::HuffmanTree::TreeTraversal &HuffmanAchiever::HuffmanTree::TreeTraversal::operator+=(bool bit) {
    pos = bit ? tree_.tree[pos].right : tree_.tree[pos].left;
    return *this;
}

char HuffmanAchiever::HuffmanTree::TreeTraversal::operator*() const {
    if (isLeaf())
        return pos;
    throw std::runtime_error("It does not point to a leaf.");
}

bool HuffmanAchiever::HuffmanTree::TreeTraversal::isLeaf() const {
    return tree_.tree[pos].left == -1;
}

void HuffmanAchiever::compress(std::istream &is, std::ostream &os, statistics &stcs) {
    std::vector<int32_t > freq(UCHAR_MAX + 1, 0);
    char c;
    int32_t fsz = 0;
    while (is.get(c)) {
        freq[static_cast<unsigned char>(c)]++;
        fsz++;
    }
    if (!fsz) {
        stcs.srcsz = 0;
        stcs.compsz = 0;
        return;
    }
    for (auto f : freq)
        os.write(reinterpret_cast<char *>(&f), sizeof(int32_t));
    os.write(reinterpret_cast<char *>(&fsz), sizeof(int32_t));
    HuffmanTree tree(std::move(freq));
    is.clear();
    is.seekg(0, std::ios::beg);
    Ostream bos(os);
    while (is.get(c)) {
        auto it = tree.codeTable.find(c);
        if (it == tree.codeTable.end())
            throw std::runtime_error("Symbol does not exist.");
        bos << it->second;
    }
    stcs.srcsz = fsz;
    stcs.compsz = static_cast<int32_t>(os.tellp()) + 1 - stcs.EXTRADATA;
}

void HuffmanAchiever::decompress(std::istream &is, std::ostream &os, statistics &stcs) {
    if (is.peek() == std::istream::traits_type::eof()) {
        stcs.compsz = 0;
        stcs.decompsz = 0;
        return;
    }
    std::vector<int32_t> freq(UCHAR_MAX + 1);
    for (auto &f : freq)
        is.read(reinterpret_cast<char *>(&f), sizeof(int32_t));
    int32_t count;
    is.read(reinterpret_cast<char *>(&count), sizeof(int32_t));
    HuffmanTree tree(std::move(freq));
    Istream bis(is);
    for (size_t i = 0; i < (size_t) count; i++) {
        HuffmanTree::TreeTraversal it = tree.begin();
        while (!it.isLeaf()) {
            bool bit;
            bis >> bit;
            it += bit;
        }
        char c = *it;
        os.write(reinterpret_cast<char *>(&c), 1);
    }
    stcs.decompsz = static_cast<int32_t>(is.tellg()) - stcs.EXTRADATA;
    stcs.compsz = os.tellp();
}

Istream &Istream::operator>>(bool &input) {
    if (cnt == CHAR_BIT) {
        is_.read(reinterpret_cast<char *>(&buf), 1);
        cnt = 0;
    }
    input = (buf >> cnt++) & 1;
    return *this;
}

Ostream::~Ostream() {
    if (cnt)
        os_.write(reinterpret_cast<char *>(&buf), 1);
}

Ostream &Ostream::operator<<(std::vector<bool> output) {
    for (bool bit : output) {
        if (cnt == CHAR_BIT) {
            os_.write(reinterpret_cast<char *>(&buf), 1);
            cnt = 0;
            buf = 0;
        }
        buf |= (bit << cnt++);
    }
    return *this;
}