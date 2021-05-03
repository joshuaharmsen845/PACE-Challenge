void Graph::clique_it(std::unordered_set<int> cluster) {
  for (auto i: cluster) {
    std::unordered_set<int> neighbors = graph[i];
    std::unordered_set<int> not_nei = cluster;
    for (auto j: neighbor) {
      for (auto k: cluster) {
        if (k == j)
          not_nei.erase(k);
      }
    }
    for (auto l: not_nei)
      addEdge(i, l);
  }
}

void Graph::break_it(std::unordered_set<int> cluster) {
  for (auto i: cluster) {
    std::unordered_set<int> neighbors = graph[i];
    for (auto j: neighbor) {
      for (auto k: cluster)        //Does this cut E/2 edges or all of them? We can get away with E/2.
        if (k == j) //Cannot iterate
          cutEdge(i, j);
    }
  }
}

void Graph::large_file() {
  std:: unordered_set<int> used = []
  for (auto i: graph) { 
    float con = 0;                            
    bool iter = false;
    std::unordered_set<int> cluster = findCluster(i);
    int max_con = cluster.size() * (cluster.size() - 1);
    for (auto j: cluster)
      con += connectedness(j);
    float con_per = con / max_con;
    for (auto j: cluster) {
      for (auto k: used) {
        if (j == k)
          iter = true;
      }
    }
    if !iter
      if (con_per < .5)
        clique_it(cluster);
      else
        break_it(cluster);
  }
}

