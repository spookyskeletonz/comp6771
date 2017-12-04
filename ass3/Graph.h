#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>


namespace gdwg {

    template <typename N, typename E>  
    class Graph {
    public:
        class Node;
        class Edge;
        Graph() {};
        Graph(const Graph& g){
            Graph c = Graph(g);
            *this =  c;
        }
        Graph(Graph&& g){
            Graph m = Graph(g);
            *this = m;
        }

        Graph& operator=(const Graph& g) {
            this->clear();
            std::vector<std::shared_ptr<Edge>> edgesToAdd;
            for(std::shared_ptr<Node> n : g.nodes){
                this->addNode(n->getVal());
                if(n->getOutDegree() > 0) {
                    for(std::shared_ptr<Edge> e : n->getOutEdges()){
                        edgesToAdd.push_back(e);
                    }
                }
            }

            for(std::shared_ptr<Edge> e : edgesToAdd){
                this->addEdge(e->getSource(), e->getDest(), e->getWeight());
            }
            return *this;  
        }

        Graph& operator=(Graph&& g){
            this->clear();
            nodes = std::move(g.nodes);
            return *this;
        }

        void begin() const{ iterator = 0; }
        bool end() const{ return iterator >= nodes.size(); }
        void next() const{ iterator++; }
        const N& value() const{ return nodes[iterator]->getVal(); }

        bool addNode(const N& val);
        bool addEdge(const N& src, const N& dst, const E& w);
        bool isNode (const N& val) const;
        bool replace(const N& oldData, const N& newData);
        void mergeReplace(const N& oldData, const N& newData);
        void deleteNode(const N& del) noexcept;
        void deleteEdge(const N& src, const N& dst, const E& w) noexcept;
        void clear() noexcept;
        bool isConnected(const N& src, const N& dst) const;
        void printNodes() const;
        void printEdges(const N& val) const; 
        //TODO: iterator stuffffff

        //private inner class for holding the node values of type N
        class Node {
        
            public:
            //constructor for creating a new Node
            Node(const N& val) : valPtr{std::make_shared<N>(val)} {}

            const N& getVal() const { return *valPtr; }
            void addEdge(std::shared_ptr<Node> self, std::shared_ptr<Node> dst, const E& w);
            std::weak_ptr<N> getValPtr() const { return valPtr; }
            bool hasEdge (const E& w, const N& dst) const;
            const int getOutDegree() const { return outEdges.size(); } 
            const bool isConnected(const N& dst) const;
            void replace(const N& newData) {*valPtr = newData;}
            void printEdges();
            void mergeEdges(std::shared_ptr<Node> selfNode, std::shared_ptr<Node> newNode);
            void deleteNode();
            void resetValPtr() { valPtr.reset(); }
            void removeOutEdge(std::shared_ptr<Edge>);
            void removeInEdge(std::shared_ptr<Edge>);
            void deleteEdge(const N& dst, const E& w);
            std::vector<std::shared_ptr<Edge>> getOutEdges() { return outEdges; }
            std::vector<std::shared_ptr<Edge>> getInEdges() { return inEdges; }

        private:
            //private data member for Node
            std::shared_ptr<N> valPtr;
            std::vector<std::shared_ptr<Edge>> outEdges;
            std::vector<std::shared_ptr<Edge>> inEdges; 
        };

        class Edge {
                
        public:
            //constructor for new Edge
            Edge(std::shared_ptr<Node> src, std::shared_ptr<Node> dst, const E& w): weight{w}, source{src}, dest{dst} {}
            const E& getWeight() const{ return weight; }
            const N& getSource() const{ return source.lock()->getVal(); }
            const N& getDest() const{ return dest.lock()->getVal(); }
            void setSourceNode(std::shared_ptr<Node> src) { source = src; }
            void setDestNode(std::shared_ptr<Node> dst) { dest = dst;}
            std::shared_ptr<Node> getSourceNode() { return source.lock(); }
            std::shared_ptr<Node> getDestNode() { return dest.lock(); }

        private:
            //private data members of Edge
            E weight;
            std::weak_ptr<Node> source;
            std::weak_ptr<Node> dest;

        };

    private:
        //private data members for Graph
        std::vector<std::shared_ptr<Node>> nodes;
        mutable unsigned int iterator = 0;
    };
  
#include "Graph.tem"
} 

#endif
