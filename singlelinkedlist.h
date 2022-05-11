#pragma once

#include <iterator>
#include <algorithm>
#include <stdexcept>

namespace List {

template <typename Type>
class SingleLinkedList {

    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val), next_node(next) {}
        Type value;
        Node* next_node = nullptr;
    };

public:
    template <typename ValueType>
    class BasicIterator {
        friend class SingleLinkedList;
        explicit BasicIterator(Node* node) noexcept : node_(node) {}

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        BasicIterator() = default;
        BasicIterator(const BasicIterator<Type>& other) noexcept : node_(other.node_) {}
        BasicIterator& operator=(const BasicIterator& rhs) noexcept;

        bool operator== (const BasicIterator<const Type>& rhs) const noexcept;
        bool operator!= (const BasicIterator<const Type>& rhs) const noexcept;
        bool operator== (const BasicIterator<Type>& rhs) const noexcept;
        bool operator!= (const BasicIterator<Type>& rhs) const noexcept;

        BasicIterator& operator++();
        BasicIterator operator++(int);
        reference operator* () const;
        pointer operator-> () const;

    private:
        Node* node_ = nullptr;
    };

    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using Iterator = BasicIterator<Type>;
    using ConstIterator = BasicIterator<const Type>;

    Iterator before_begin() noexcept;
    ConstIterator cbefore_begin() const noexcept;
    ConstIterator before_begin() const noexcept;

    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;

    SingleLinkedList();
    SingleLinkedList(std::initializer_list<Type> values);
    SingleLinkedList(const SingleLinkedList& other);
    ~SingleLinkedList();

    bool operator==(const SingleLinkedList& rhs);

    SingleLinkedList& operator=(const SingleLinkedList& rhs);
    void swap(SingleLinkedList& other) noexcept;
    size_t GetSize() const noexcept;
    bool IsEmpty() const noexcept;
    SingleLinkedList& PushFront(const Type& value);
    Iterator InsertAfter(ConstIterator pos, const Type& value);
    void PopFront();
    Iterator EraseAfter(ConstIterator pos);
    void Clear() noexcept;

private:
    Node head_; // Фиктивный узел, используется для вставки "перед первым элементом"
    size_t size_; // кол-во элементов списка

    template <typename Iter>
    void Init(Iter begin, Iter end);
};

/*  Ниже реализация методов класса SingleLinkedList */

template <typename Type>
bool SingleLinkedList<Type>::operator==(const SingleLinkedList<Type>& rhs) {
    return std::equal(begin(), end(), rhs.begin(), rhs.end());
}

template <typename Type>
SingleLinkedList<Type>& SingleLinkedList<Type>::operator=(const SingleLinkedList<Type>& rhs) {
    if (this != &rhs) {
        SingleLinkedList<Type> temp(rhs);
        swap(temp);
    }
    return *this;
}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList() : head_(Node()), size_(0) {
}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(std::initializer_list<Type> values) : SingleLinkedList() {
    SingleLinkedList<Type> temp;
    temp.Init(values.begin(), values.end());
    swap(temp);
}

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(const SingleLinkedList<Type>& other) : SingleLinkedList() {
    SingleLinkedList<Type> temp;
    temp.Init(other.begin(), other.end());
    swap(temp);
}

template <typename Type>
SingleLinkedList<Type>::~SingleLinkedList() {
    Clear();
}

template <typename Type>
void SingleLinkedList<Type>::swap(SingleLinkedList<Type>& other) noexcept {
    std::swap(head_.next_node, other.head_.next_node);
    std::swap(size_, other.size_);
}

template <typename Type>
[[nodiscard]] size_t SingleLinkedList<Type>::GetSize() const noexcept {
    return size_;
}

template <typename Type>
[[nodiscard]] bool SingleLinkedList<Type>::IsEmpty() const noexcept {
    return size_ == 0;
}

template <typename Type>
SingleLinkedList<Type>& SingleLinkedList<Type>::PushFront(const Type& value) {
    head_.next_node = new Node(value, head_.next_node);
    ++size_;
    return *this;
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator
SingleLinkedList<Type>::InsertAfter(ConstIterator pos, const Type& value) {
    if (pos.node_ == nullptr) {
        throw std::out_of_range("Invalid iterator");
    }
    pos.node_->next_node = new Node(value, pos.node_->next_node);
    ++size_;
    return Iterator(pos.node_->next_node);
}

template <typename Type>
void SingleLinkedList<Type>::PopFront(){
    if (IsEmpty()) {
        throw std::out_of_range("List is empty");
    }
    Node *temp = head_.next_node;
    head_.next_node = head_.next_node->next_node;
    delete temp;
    --size_;
}

template <typename Type>
typename SingleLinkedList<Type>::Iterator
SingleLinkedList<Type>::EraseAfter(ConstIterator pos){
    if (pos.node_->next_node == nullptr) {
        throw std::out_of_range("Invalid iterator");
    }
    Node *temp = pos.node_->next_node;
    pos.node_->next_node = pos.node_->next_node->next_node;
    delete temp;
    --size_;
    return Iterator(pos.node_->next_node);
}

template <typename Type>
void SingleLinkedList<Type>::Clear() noexcept {
    while (head_.next_node != nullptr) {
        Node *temp = head_.next_node;
        head_.next_node = temp->next_node;
        delete temp;
        --size_;
    }
}

template <typename Type>
template <typename Iter>
void SingleLinkedList<Type>::Init(Iter begin, Iter end) {
    Node *p = &head_;
    for (auto it = begin; it != end; ++it) {
        p->next_node = new Node(*it, nullptr);
        p = p->next_node;
        ++size_;
    }
}

template <typename Type>
[[nodiscard]] typename SingleLinkedList<Type>::Iterator
SingleLinkedList<Type>::before_begin() noexcept {
    return Iterator(&head_);
}

template <typename Type>
[[nodiscard]] typename SingleLinkedList<Type>::ConstIterator
SingleLinkedList<Type>::cbefore_begin() const noexcept {
    return ConstIterator(const_cast<Node*>(&head_));
}

template <typename Type>
[[nodiscard]] typename SingleLinkedList<Type>::ConstIterator
SingleLinkedList<Type>::before_begin() const noexcept {
    return ConstIterator(&head_);
}

template <typename Type>
[[nodiscard]] typename SingleLinkedList<Type>::Iterator
SingleLinkedList<Type>::begin() noexcept {
    return Iterator(head_.next_node);
}

template <typename Type>
[[nodiscard]] typename SingleLinkedList<Type>::Iterator
SingleLinkedList<Type>::end() noexcept {
    return Iterator();
}

template <typename Type>
[[nodiscard]] typename SingleLinkedList<Type>::ConstIterator
SingleLinkedList<Type>::begin() const noexcept {
    return ConstIterator(head_.next_node);
}

template <typename Type>
[[nodiscard]] typename SingleLinkedList<Type>::ConstIterator
SingleLinkedList<Type>::end() const noexcept {
    return ConstIterator();
}

template <typename Type>
[[nodiscard]] typename SingleLinkedList<Type>::ConstIterator
SingleLinkedList<Type>::cbegin() const noexcept {
    return ConstIterator(head_.next_node);
}

template <typename Type>
[[nodiscard]] typename SingleLinkedList<Type>::ConstIterator
SingleLinkedList<Type>::cend() const noexcept {
    return ConstIterator();
}

/*  Ниже реализация методов класса BasicIterator */

template <typename Type>
template <typename ValueType>
typename SingleLinkedList<Type>::template BasicIterator<ValueType>&
SingleLinkedList<Type>::BasicIterator<ValueType>::
operator=(const BasicIterator &rhs) noexcept {
    node_ = rhs.node_;
    return *this;
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] bool SingleLinkedList<Type>::BasicIterator<ValueType>::
operator==(const BasicIterator<const Type>& rhs) const noexcept {
    return node_ == rhs.node_;
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] bool SingleLinkedList<Type>::BasicIterator<ValueType>::
operator!=(const BasicIterator<const Type>& rhs) const noexcept {
    return node_ != rhs.node_;
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] bool SingleLinkedList<Type>::BasicIterator<ValueType>::
operator==(const BasicIterator<Type>& rhs) const noexcept {
    return node_ == rhs.node_;
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] bool SingleLinkedList<Type>::BasicIterator<ValueType>::
operator!=(const BasicIterator<Type>& rhs) const noexcept {
    return node_ != rhs.node_;
}

template <typename Type>
template <typename ValueType>
typename SingleLinkedList<Type>::template BasicIterator<ValueType>&
SingleLinkedList<Type>::BasicIterator<ValueType>::operator++() {
    if (node_ == nullptr) {
        throw std::out_of_range("Invalid iterator");
    }
    node_ = node_->next_node;
    return *this;
}

template <typename Type>
template <typename ValueType>
typename SingleLinkedList<Type>::template BasicIterator<ValueType>
SingleLinkedList<Type>::BasicIterator<ValueType>::operator++(int) {
    if (node_ == nullptr) {
        throw std::out_of_range("Invalid iterator");
    }
    auto old_value(*this);
    ++(*this);
    return old_value;
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] typename SingleLinkedList<Type>::template BasicIterator<ValueType>::reference
SingleLinkedList<Type>::BasicIterator<ValueType>::operator*() const {
    if (node_ == nullptr) {
        throw std::out_of_range("Invalid iterator");
    }
    return node_->value;
}

template <typename Type>
template <typename ValueType>
[[nodiscard]] typename SingleLinkedList<Type>::template BasicIterator<ValueType>::pointer
SingleLinkedList<Type>::BasicIterator<ValueType>::operator->() const {
    if (node_ == nullptr) {
        throw std::out_of_range("Invalid iterator");
    }
    return &(node_->value);
}

/*  Ниже реализация свободных функций */

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return (lhs < rhs || lhs == rhs);
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs <= rhs);
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !(lhs < rhs);
}

} // namespace SingleLinkedList
