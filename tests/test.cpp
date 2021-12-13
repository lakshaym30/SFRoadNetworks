#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../GraphData.h"

#include "../cs225/PNG.h"
using cs225::PNG;

#include "../cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <vector>


// default constructor
TEST_CASE("Testing graphing with Small Dataset") {
  GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
  cs225::PNG img = gd_small.graphVisualizer();

  SECTION("Checking for center of node"){
    cs225::HSLAPixel pixel = img.getPixel(0, 11998);
    REQUIRE(pixel.h==120);
    REQUIRE(pixel.s==1);
    REQUIRE(pixel.l==0.5);
    REQUIRE(pixel.a==1);
  }

  SECTION("Checking for empty pixel"){
    cs225::HSLAPixel pixel = img.getPixel(0, 0);
    REQUIRE(pixel.h==0);
    REQUIRE(pixel.s==0);
    REQUIRE(pixel.l==1);
    REQUIRE(pixel.a==1);
  }

  SECTION("Checking for border of node"){
    cs225::HSLAPixel pixel = img.getPixel(0, 11997);
    REQUIRE(pixel.h==120);
    REQUIRE(pixel.s==1);
    REQUIRE(pixel.l==0.5);
    REQUIRE(pixel.a==1);
  }

  SECTION("Checking for line of graph"){
    cs225::HSLAPixel pixel = img.getPixel(19, 11998);
    REQUIRE(pixel.h==0);
    REQUIRE(pixel.s==0);
    REQUIRE(pixel.l==1);
    REQUIRE(pixel.a==1);
  }
  
}

TEST_CASE("Testing Shortest Path Functionality on Small Dataset") {
  SECTION("Testing Distance Vector Functionality Starting at Node 0") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(0);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == 0);
    REQUIRE(distances_vector.at(1) == 3);
    REQUIRE(distances_vector.at(2) == 7);
    REQUIRE(distances_vector.at(3) == 1);
    REQUIRE(distances_vector.at(4) == 2);
  }

  SECTION("Testing Distance Vector Functionality Starting at Node 1") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(1);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == 3);
    REQUIRE(distances_vector.at(1) == 0);
    REQUIRE(distances_vector.at(2) == 5);
    REQUIRE(distances_vector.at(3) == 2);
    REQUIRE(distances_vector.at(4) == 2);
  }

  SECTION("Testing Distance Vector Functionality Starting at Node 3") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(3);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == 1);
    REQUIRE(distances_vector.at(1) == 2);
    REQUIRE(distances_vector.at(2) == 6);
    REQUIRE(distances_vector.at(3) == 0);
    REQUIRE(distances_vector.at(4) == 1);
  }

  SECTION("Testing Distance Vector Functionality Starting at Node 4") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(4);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == 2);
    REQUIRE(distances_vector.at(1) == 2);
    REQUIRE(distances_vector.at(2) == 5);
    REQUIRE(distances_vector.at(3) == 1);
    REQUIRE(distances_vector.at(4) == 0);
  }

  SECTION("Testing Previous Vector Functionality Starting at Node 0") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(0);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(0) == 0);
    REQUIRE(previous_vector.at(1) == 3);
    REQUIRE(previous_vector.at(2) == 4);
    REQUIRE(previous_vector.at(3) == 0);
    REQUIRE(previous_vector.at(4) == 3);
  }

  SECTION("Testing Previous Vector Functionality Starting at Node 2") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(2);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(0) == 3);
    REQUIRE(previous_vector.at(1) == 2);
    REQUIRE(previous_vector.at(2) == 0);
    REQUIRE(previous_vector.at(3) == 1);
    REQUIRE(previous_vector.at(4) == 2);
  }

  SECTION("Testing Previous Vector Functionality Starting at Node 3") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(3);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(0) == 3);
    REQUIRE(previous_vector.at(1) == 3);
    REQUIRE(previous_vector.at(2) == 4);
    REQUIRE(previous_vector.at(3) == 0);
    REQUIRE(previous_vector.at(4) == 3);
  }

  SECTION("Testing Previous Vector Functionality Starting at Node 4") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(4);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(0) == 3);
    REQUIRE(previous_vector.at(1) == 4);
    REQUIRE(previous_vector.at(2) == 4);
    REQUIRE(previous_vector.at(3) == 4);
    REQUIRE(previous_vector.at(4) == 0);
  }
}

TEST_CASE("Testing Shortest Path Functionality on Big Dataset") {
  SECTION("Testing Distance Vector Functionality Starting at Node 7") {
    GraphData gd_big("datasets/SFnodes.txt", "datasets/SFedges.txt");
    pair<vector<int>, vector<int>> output = gd_big.shortestPath(7);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == 48);
    REQUIRE(distances_vector.at(1) == 53);
    REQUIRE(distances_vector.at(2) == 58);
  }

  SECTION("Testing Distance Vector Functionality (When Nodes Do Not Get Visited) Starting at Node 21") {
    GraphData gd_big("datasets/SFnodes.txt", "datasets/SFedges.txt");
    pair<vector<int>, vector<int>> output = gd_big.shortestPath(21);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == INT_MAX);
    REQUIRE(distances_vector.at(1) == INT_MAX);
    REQUIRE(distances_vector.at(2) == INT_MAX);
  }

  SECTION("Testing Previous Vector Functionality Starting at Node 44") {
    GraphData gd_big("datasets/SFnodes.txt", "datasets/SFedges.txt");
    pair<vector<int>, vector<int>> output = gd_big.shortestPath(44);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(23) == 15);
    REQUIRE(previous_vector.at(24) == 17);
    REQUIRE(previous_vector.at(25) == 0);
  }
  
  SECTION("Testing Previous Vector Functionality Starting at Node 67") {
    GraphData gd_big("datasets/SFnodes.txt", "datasets/SFedges.txt");
    pair<vector<int>, vector<int>> output = gd_big.shortestPath(67);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(33) == 40);
    REQUIRE(previous_vector.at(34) == 33);
    REQUIRE(previous_vector.at(35) == 34);
  }
}

TEST_CASE("Testing BFS") {
  SECTION("Testing BFS on Small Dataset") {
    GraphData gd_bfs_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    vector<bool> output = gd_bfs_small.BFS(0);
    bool flag = true;
    for (bool b : output) {
      if (b != true) {
        flag = false;
      }
    }
    REQUIRE(flag == true);
  }

  SECTION("Testing BFS on Big Dataset") {
    GraphData gd_bfs_big("datasets/SFnodes.txt", "datasets/SFedges.txt");
    vector<bool> output = gd_bfs_big.BFS(0);
    bool flag = true;
    for (bool b : output) {
      if (b != true) {
        flag = false;
      }
    }
    REQUIRE(flag == true);
  }
  
}


