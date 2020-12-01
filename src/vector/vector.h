//
// Created by 张锐 on 2020/11/24.
//

#ifndef DATASTRUCT_VECTOR_H
#define DATASTRUCT_VECTOR_H

// 向量头文件
// 定义向量的基本实现
template<typename T>
class vector {
public:
    // 类型定义
    typedef size_t rank;    // 向量的逻辑结构和物理结构保持一致。寻秩访问
    typedef T* pointer;
    typedef T& reference;
    typedef const T* const_pointer;

    vector():_capacity(0),_size(0),_elements(new T[_capacity]) {};
    vector(rank c);
    vector(rank, rank, const T&);   //容量初始化为c，并初始化前n个元素为T
    // 拷贝控制成员
    vector(const vector<T> &);  // 拷贝构造函数
    vector(const vector<T> &&);  // 移动构造函数
    vector &operator=(const vector<T> &);  // 拷贝构造运算符
    vector &operator=(const vector<T> &&);  // 移动构造运算符
    ~vector();

    // 元素访问
    reference operator[](rank i);
    reference at(rank i);


    // 修改器
    rank insert(rank r, const T& e); //插入元素
    rank insert (const T& e);//默认作为末元素插入
    T remove (rank r); //删除秩为r的元素
    int remove (rank lo, rank hi); //删除秩在区间[lo, hi)之内的元素

    // 容量
    rank size() const { return _size; };
    bool empty() const { return !_size; };
    rank capacity() const { return _capacity; };

    // 算法
    bool disordered() const;            //判断向量是否已排序
    void sort();    //整体排序
    void sort (rank lo, rank hi);     //对[lo, hi)排序
    void unsort();  //整体置乱
    void unsort (rank lo, rank hi);   //对[lo, hi)置乱
    int uniquify();     //有序去重
    int deduplicate();  //无序去重
    int find(const T&) const;
    int find(const T&, rank, rank) const; // 无序向量给定区间内查找
    int search(const T&) const;
    int search(const T&, rank, rank) const; // 有序向量给定区间内查找
    void traverse(void(*p)(reference)) const ;

protected:
    void bubbleSort (rank lo, rank hi);       //起泡排序算法
    void selectionSort (rank lo, rank hi);    //选择排序算法
    void mergeSort (rank lo, rank hi);        //归并排序算法
    void quickSort (rank lo, rank hi);        //快速排序算法
    void heapSort (rank lo, rank hi);         //堆排序（稍后结合完全堆讲解）

private:
    rank _size;
    rank _capacity;
    T * _elements;
    void expand(); //空间不足时扩容
    void shrink(); //装填因子过小时压缩
    void clear();  // 清除元素但不改变内存

    void copy(pointer lhs, pointer rhs, rank n);   // 从 rhs 开始复制 n 个元素到当前向量中

    rank max (rank lo, rank hi);              //选取最大元素
    bool bubble (rank lo, rank hi);           //扫描交换
    void merge (rank lo, rank mi, rank hi);   //归并算法
    rank partition (rank lo, rank hi);        //轴点构造算法
};

#endif //DATASTRUCT_VECTOR_H
