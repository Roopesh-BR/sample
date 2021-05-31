#pragma once

#include<limits>
#include<cmath>
#include<unordered_map>
#include"model.h"
#include<iostream>

class RouteModel : public Model{

    public:
    class Node: public Model::Node{
        public:
        //Add public node variables and methods here
        Node* parent = nullptr;
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        std::vector<Node*> neighbors;
        void FindNeighbor();

        Node(){}
        Node(int idx, RouteModel* search_model, Model::Node node): Model::Node(node), parent_model(search_model), index(idx){}

        float distance(RouteModel::Node node) const{
            return std::sqrt(std::pow((x - node.x), 2) + std::pow((this->y - node.y), 2));
        }

        private:
        //Add private node variables and methods here
        int index;
        RouteModel* parent_model = nullptr;
        Node* FindNeighbor(std::vector<int> node_indices);
    };

    RouteModel(const std::vector<std::byte> &xml);
    auto &Snodes(){ return m_Nodes; }
    auto &GetNodeToRoadMap(){return node_to_road;};
    Node &FindClosestNode (float x, float y);
    std::vector<Node> path;

    private:
    std::vector<std::byte> m_Nodes;
    std::unordered_map <int, std::vector<const Model::Road*>> node_to_road;

    void CreateNodeToRoadHashmap();
};