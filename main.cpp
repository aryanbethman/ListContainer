#include <iostream>
#include <string>
#include "containers.h"

// --- Demonstration for basic types ---
template <typename T>
void demonstrate(AbstractList<T>& container, T a, T b, T c) {
    std::cout << "--- Demonstrating: " << container.name() << " ---" << std::endl;
    std::cout << "Pushing: " << a << ", " << b << ", " << c << std::endl;
    container.push(a);
    container.push(b);
    container.push(c);

    std::cout << "Size is: " << container.size() << std::endl;
    
    // Pop an item - behavior depends on the container
    std::cout << "Popped: " << container.pop() << std::endl;
    std::cout << "Size is now: " << container.size() << std::endl;

    container.clear();
    std::cout << "Cleared container. Size is now: " << container.size() << std::endl;
    std::cout << std::endl;
}

// --- Demonstration for custom PriorityQueue types ---
struct Person {
    std::string name;
    int age;

    // Required for the min-heap
    bool operator<(const Person& other) const { return age < other.age; }
    bool operator>(const Person& other) const { return age > other.age; }

    // For printing
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        os << "{" << p.name << ", " << p.age << "}";
        return os;
    }
};


int main() {
    std::cout << "========== Demonstrating Containers with INTEGERS ==========" << std::endl;
    VectorList<int> vec;
    demonstrate(vec, 10, 20, 30);

    Stack<int> stack;
    demonstrate(stack, 10, 20, 30);

    std::cout << "========== Demonstrating Containers with STRINGS ==========" << std::endl;
    LinkedList<std::string> ll;
    demonstrate(ll, std::string("alpha"), std::string("beta"), std::string("gamma"));

    Queue<std::string> queue;
    demonstrate(queue, std::string("first"), std::string("second"), std::string("third"));

    std::cout << "========== Demonstrating PriorityQueue with a CUSTOM STRUCT ==========" << std::endl;
    PriorityQueue<Person> pq;
    std::cout << "Pushing {Carol, 30}, {Alice, 25}, {Bob, 40}" << std::endl;
    pq.push({"Carol", 30});
    pq.push({"Alice", 25});
    pq.push({"Bob", 40});

    std::cout << "Top of PQ (youngest person): " << pq.top().name << std::endl;
    std::cout << "Popping from PQ: " << pq.pop().name << std::endl;
    std::cout << "Popping from PQ: " << pq.pop().name << std::endl;
    std::cout << "Popping from PQ: " << pq.pop().name << std::endl;
    std::cout << "Final size: " << pq.size() << std::endl;

    return 0;
}
