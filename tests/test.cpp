#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../GraphData.h"

#include "../cs225/PNG.h"
using cs225::PNG;

#include "../cs225/HSLAPixel.h"
using cs225::HSLAPixel;

#include <vector>

// default constructor
TEST_CASE("HSLAPixel's default constructor creates a white pixel", "[weight=1]") {
  REQUIRE(true);
}

TEST_CASE("Testing Shortest Path Functionality on Small Dataset") {
  SECTION("Testing Distance Vector Functionality Starting at Node 0") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(gd_small.getAdjacencyList(), 0);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == 0);
    REQUIRE(distances_vector.at(1) == 3);
    REQUIRE(distances_vector.at(2) == 7);
    REQUIRE(distances_vector.at(3) == 1);
    REQUIRE(distances_vector.at(4) == 2);
  }
  SECTION("Testing Distance Vector Functionality Starting at Node 1") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(gd_small.getAdjacencyList(), 1);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == 3);
    REQUIRE(distances_vector.at(1) == 0);
    REQUIRE(distances_vector.at(2) == 5);
    REQUIRE(distances_vector.at(3) == 2);
    REQUIRE(distances_vector.at(4) == 2);
  }
  SECTION("Testing Distance Vector Functionality Starting at Node 3") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(gd_small.getAdjacencyList(), 3);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == 1);
    REQUIRE(distances_vector.at(1) == 2);
    REQUIRE(distances_vector.at(2) == 6);
    REQUIRE(distances_vector.at(3) == 0);
    REQUIRE(distances_vector.at(4) == 1);
  }
  SECTION("Testing Distance Vector Functionality Starting at Node 4") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(gd_small.getAdjacencyList(), 4);
    vector<int> distances_vector = output.first;
    REQUIRE(distances_vector.at(0) == 2);
    REQUIRE(distances_vector.at(1) == 2);
    REQUIRE(distances_vector.at(2) == 5);
    REQUIRE(distances_vector.at(3) == 1);
    REQUIRE(distances_vector.at(4) == 0);
  }
  SECTION("Testing Previous Vector Functionality Starting at Node 0") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(gd_small.getAdjacencyList(), 0);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(0) == 0);
    REQUIRE(previous_vector.at(1) == 3);
    REQUIRE(previous_vector.at(2) == 4);
    REQUIRE(previous_vector.at(3) == 0);
    REQUIRE(previous_vector.at(4) == 3);
  }
  SECTION("Testing Previous Vector Functionality Starting at Node 2") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(gd_small.getAdjacencyList(), 2);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(0) == 3);
    REQUIRE(previous_vector.at(1) == 2);
    REQUIRE(previous_vector.at(2) == 0);
    REQUIRE(previous_vector.at(3) == 1);
    REQUIRE(previous_vector.at(4) == 2);
  }
  SECTION("Testing Previous Vector Functionality Starting at Node 3") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(gd_small.getAdjacencyList(), 3);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(0) == 3);
    REQUIRE(previous_vector.at(1) == 3);
    REQUIRE(previous_vector.at(2) == 4);
    REQUIRE(previous_vector.at(3) == 0);
    REQUIRE(previous_vector.at(4) == 3);
  }
  SECTION("Testing Previous Vector Functionality Starting at Node 4") {
    GraphData gd_small("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    pair<vector<int>, vector<int>> output = gd_small.shortestPath(gd_small.getAdjacencyList(), 4);
    vector<int> previous_vector = output.second;
    REQUIRE(previous_vector.at(0) == 3);
    REQUIRE(previous_vector.at(1) == 4);
    REQUIRE(previous_vector.at(2) == 4);
    REQUIRE(previous_vector.at(3) == 4);
    REQUIRE(previous_vector.at(4) == 0);
  }
}


