#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

void printGraph(vector<vector<int>> &instance, int edges, vector<int> new_to_original){
    cout << instance.size() << endl << edges << endl;
    for (int i = 0; i < instance.size(); ++i) {
       for (int j = i; j < instance.size(); j++) {
          if(!new_to_original.empty()){
              if(!instance[new_to_original[i]][new_to_original[j]])
                  cout << i << " " << j << endl;
          } else{
              if(!instance[i][j])
                  cout << i << " " << j << endl;
          }
       }
    }
}

int main(int argc, char ** argv){
    random_device dev;
    mt19937 generator(dev());
    int vertices, requested_edges, excluded_edge, possible_edges;
    int v1, v2;

    cin >> vertices >> requested_edges;

    vector<vector<int>> excluded_edges(vertices);
    vector<int> mapping(vertices);

    for (auto &i : excluded_edges)
        i.resize(vertices);

    for (int i = 0; i < vertices; ++i)
        mapping[i] = i;

    uniform_int_distribution<int> distribution(0, (vertices * vertices) - 1);

    for (int i = 0; i < (vertices * (vertices + 1))/2 - requested_edges; ++i) {
        do{
           excluded_edge = distribution(generator);
        }while(excluded_edges[excluded_edge / vertices][excluded_edge % vertices] == 1);
        v1 = excluded_edge / vertices;
        v2 = excluded_edge % vertices;
        excluded_edges[v1][v2] = excluded_edges[v2][v1] = 1;
    }

    printGraph(excluded_edges, requested_edges, mapping);
    shuffle(mapping.begin(), mapping.end(), generator);
    printGraph(excluded_edges, requested_edges, mapping);

    return 0;
}

