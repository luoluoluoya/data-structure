//
// Created by 47302 on 2020/12/6.
//

#ifndef PLUS_HUFFMAN_H
#define PLUS_HUFFMAN_H

/**
字符编码 =》 二叉树（正确编解码方案） =》 完全二叉树（高效率编码方案） =》 huffman编码树（基于某种概率分布的编解码方案）

若字符集C1和C2之间没有公共字符，且PFC编码方案分别对应于二叉树T1和 T2，则通过引入一个根节点合并T1和T2之后所得到的二叉树，就是对应于C1和C2的一种PFC编码方案。
请注意，无论T1和T2的高度与规模是否相等，这一性质总是成立。利用上述性质，可自底而上地构造PFC编码树。首先，由每一字符分别构造一棵单节点二叉树，并将它们视作一个森林。
此后，反复从森林中取出两棵树并将其合二为一。如此，经|C1| - 1步迭代之后，初始森林中的|C1|棵树将合并成为一棵完整的PFC编码树。接下来，再将PFC编码树转译为编码表，
以便能够根据待编码字符快捷确定与之对应的编码串。至此，对于任何待编码文本，通过反复查阅编码表，即可高效地将其转化为二进制编码串。与编码过程相对应地，接收方也可以借助
同一棵编码树来记录双方约定的编码方案。于是，每当接收到经信道传送过来的编码串后，（只要传送过程无误）接收方都可通过在编码树中反复从根节点出发做相应的漫游，依次完成对信息文本中各字符的解码

最优编码树
    同一字符集的所有编码方案中，平均编码长度最小者称作最优方案；对应编码树的ald()值也达到最小，故称之为最优二叉编码树，简称最优编码树（optimal encoding tree）。
    对于任一字符集C，深度不超过|C|的编码树数目有限，故在其中ald()值最小者必然存在。需注意的是，最优编码树不见得唯一（比如，同层节点互换位置后，并不影响全树的平均深度），
    但从工程的角度看，任取其中一棵即可。为导出最优编码树的构造算法，以下需从更为深入地了解最优编码树的性质入手。

    首先，最优二叉编码树必为真二叉树：内部节点的左、右孩子全双（习题[5-2]）。若不然，假设在某棵最优二叉编码树T中，内部节点p拥有唯一的孩子x。于是，此时只需将节点p删除并代之以子树x，
    即可得到原字符集的另一棵编码树T'。不难看出，除了子树x中所有叶节点的编码长度统一缩短1层之外，其余叶节点的编码长度不变，因此相对于T，T'的平均编码长度必然更短这与T的最优性矛盾。

    最优编码树中，叶节点位置的选取有严格限制。其深度之差不得超过1。假设，某棵最优二叉编码树T含有深度之差不小于2的一对叶节点x和y。不失一般性设x更深，并令p为x的父亲。
    于是由双子性，作为内部节点的p必然还有另一孩子q。令叶节点y与子树p互换位置，从而得到一棵新树T'。易见，T'依然是原字符集的一棵二叉编码树。更重要的是，就深度而言，
    除了x、y以及子树q中的叶节点外，其余叶节点均保持不变。其中，x的提升量与y的下降量相互抵消，而子树q中的叶节点都至少提升1层。因此相对于T，T'的平均编码长度必然更短。这与T的最优性矛盾。

    最优编码树的构造：最优编码树中的叶节点只能出现于最低两层，故这类树的一种特例就是真完全树。

Huffman编码树
    字符出现概率
        以上最优编码树算法的实际应用价值并不大，除非C中各字符在文本串中出现的次数相等。遗憾的是，这一条件往往并不满足，甚至不确定。为此，
        需要从待编码的文本中取出若干样本，通过统计各字符在其中出现的次数（亦称作字符的频率），估计各字符实际出现的概率。
    带权平均编码长度与叶节点带权平均深度
        若考虑字符各自的出现频率，则可将带权平均编码长度取作编码树T的叶节点带权平均深度（weighted average leaf depth），亦即：wald(T) = sum(p(x)∙|rps(x)|)(x 为所有叶节点)
    最优带权编码树
        若字符集C中各字符的出现频率分布为p()，则wald()值最小的编码方案称作C（按照p()分布的）的最优带权编码方案，对应的编码树称作最优带权编码树。
        当然，与不考虑字符出现概率时同理，此时的最优带权编码树也必然存在（尽管通常并不唯一）。
    层次性
        具体地，若字符x和y的出现概率在所有字符中最低，则必然存在某棵最优带权编码树，使x 和y在其中同处于最底层，且互为兄弟。为证明这一重要特性任取一棵最优带权编码树T。
        根据双子性，必然可以在最低层找到一对兄弟节点a和b。不妨设它们不是x和y。 图5.36 最优编码树癿局次性现在，交换a和x， 再交换b和y，从而得到该字符集的另一编码树T'，
        x和y成为其中最低层的一对兄弟。因字符x和y权重最小，故如此交换之后，wald(T')不致增加。
    策略与算法
        因此，对于字符出现概率已知的任一字符集C，都可采用如下算法构造其对应的最优带权编码树：首先，对应于C中的每一字符，分别建立一棵单个节点的树，其权重取作该字符的频率，
        这|C|棵树构成一个森林F。接下来，从F中选出权重最小的两棵树，创建一个新节点，并分别以这两棵树作为其左、右子树，如此将它们合并为一棵更高的树，其权重取作二者权重之和。
        实际上，此后可以将合并后的新树等效地视作一个字符，称作超字符。这一选取、合并的过程反复进行，每经过一轮迭代，F中的树就减少一棵。当最终F仅包含一棵树时，它就是一棵最优带权编码树，
        构造过程随即完成。以上构造过程称作Huffman编码算法，由其生成的编码树称作Huffman编码树（Huffmanencodin tree）。需再次强调的是，Huffman编码树只是最优带权编码树中的一棵。
 */

#include "../bintree/bintree.h"
#include "../stack/stack.h"
#include "huffchar.h"
#include "../bitmap/bitmap.h"
#include <map>
#include <cstring>

// 定义huffman树
typedef bintree<HuffChar> HuffTree;
typedef vector<HuffTree*> HuffForest;


// 根据编码树对长为n的Bitmap串做Huffman解码
stack<char> decode(HuffTree& tree, BitMap& code, int n) {
    stack<char> output;
    auto x = tree.root();
    for(int i = 0; i < n; ++i) {
        x = code.test(i) ? x->rc : x->lc;
        if(!x->hasChild()) {
            output.push(x->data.ch); x = tree.root();
        }
    }
    if(x != tree.root()) ; // 存在部分编码未解出
    return output;
}
// 依据编码表对字符串进行编码并返回的编码串
BitMap* encode(std::map<char,char*> table, char*str) {
    BitMap codeString = new BitMap(); int n = 0;
    for (int i = 0; i < strlen(str); ++i) {
        char *charCode = table[str[i]];
        //将当前字符的编码接入编码串
        for(size_t m = strlen(charCode), j = 0; j < m; j++)
            '1' == charCode[j] ? codeString->set(n++) : codeString->clear(n++);
    }
    return codeString;
}



//根据频率统计表，为每个字符创建一棵树
HuffForest* initForest(int* freq, int cNum) {
    HuffForest* forest = new HuffForest;
    for(int i = 0; i < cNum; i++) {
        forest->insert(new HuffTree(HuffChar(i, freq[i])));
    }
    return forest;
}

// 编码树森林中最小权重编码树
HuffTree *minWeight(HuffForest *forest) {
    int w = INT_MAX; int r = 0;
    for(int i = 0; i < forest->size(); ++i) {
        if(w > forest->at(i)->root()->data.weight) {
            w = forest->at(i)->root()->data.weight; r = 0;
        }
    }
    return forest->remove(r);
}

// 根据编码树森林生成最有编码数
HuffTree* generate(HuffForest *forest) {
    while(forest->size() > 1) {
        auto t1 = minWeight(forest), t2 = minWeight(forest);
        HuffTree* s = new HuffTree(HuffChar('^', t1->root()->data.weight + t2->root()->data.weight));
        s->attachAsLc(s->root(), t1); s->attachAsRc(s->root(), t2);
        forest->insert(s);
    }
    return forest[0];
}

// 根据编码树生成编码表
std::map<char, char*> generateTable(HuffTree* tree) {
    std::map<char, char*> table; BitMap *code = new BitMap();
    generateCt(code, 0, table, tree->root());
    return table;
}

// 从某节点开始遍历编码子树，并将编码读入table中
void generateCt(BitMap* code, int length, std::map<char, char*>& table, bintreenode<HuffChar> x) {
    if(!x.hasChild()) {
        table[x.data.ch] = code->toString(length); return ;
    }
    if(x.hasLc()) {
        code->reset(length); generateCt(code, length+1, table, v->lc);
    }
    if(x.hasRc()) {
        code->set(length); generateCt(code, length+1, table, v->rc);
    }
}

//统计字符出现频率
std::map<char,int> statistics(char *file) {
    std::map<char, int> nums;
    FILE* fp = fopen(sample_text_file, "r");
    //逐个扫描样本文件中的每个字符, 累计对应的出现次数
    for(char ch; 0 < fscanf(fp, "%c", &ch);)
        nums[ch]++;
    fclose(fp);
    return freq;
}

#endif //PLUS_HUFFMAN_H

