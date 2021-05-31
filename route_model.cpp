#include"route_model.h"
#include<iostream>

RouteModel::RouteModel(const std::vector<std::byte> &xml): Model(xml){

    //create route_model nodes
    int counter = 0;
    for(Model::Node node : this->Nodes()){
        
        m_Nodes.emplace_back(Node(counter, this, node));
        counter++;
    }
    CreateNodeToRoadHashmap();

}

void RouteModel::CreateNodeToRoadHashmap(){
    for(const Model::Road &road: Roads()){
        if(road.type != Model::Road::Type::Footway){
            for(int node_idx: Ways()[road.way].nodes){
                if(node_to_road.find(node_idx) == node_to_road.end()){
                    node_to_road[node_idx] = std::vector<const Model::Road*>{};                    
                }
                node_to_road[node_idx].push_back(&road);

            }
        }

    }
}

RouteModel::Node* RouteModel::Node::FindNeighbor(std::vector<int> node_indices){

    RouteModel::Node* closet_node = nullptr;
    RouteModel::Node node;
    for(int node_index  : node_indices){

        node = parent_model->Snodes()[node_index ];
        if(this->distance(node) != 0 && !node.visited){
            if(closet_node == nullptr || (this->distance(node) < (this->distance(*closet_node)))){
                closet_node = &parent_model->Snodes()[node_index ];
            }

        }

    }
    return closet_node;
}

void RouteModel::Node::FindNeighbor(){

    for(auto &road: parent_model->node_to_road[this->index]){
        RouteModel::Node* new_neighbor = this->FindNeighbor(parent_model->Ways()[road->way].nodes);
        if(new_neighbor){
            this->neighbors.push_back(new_neighbor);
        }

    }

}

RouteModel::Node &RouteModel::FindClosestNode (float x, float y){
    RouteModel::Node input;
    input.x = x;
    input.y = y;

    float min_dist = std::numeric_limits<float>::max();
    float dist;
    int closest_idx;

    for(const Model::Road &road: Roads()){
        if(road.type != Model::Road::Type::Footway){
            for(int node_idx: Ways()[road.way].nodes){
                dist = input.distance(Snodes()[node_idx]);
                if(dist<min_dist){
                    closest_idx = node_idx;
                    min_dist = dist;
                }
                
            }
        }
    }
    return Snodes()[closest_idx];
}
