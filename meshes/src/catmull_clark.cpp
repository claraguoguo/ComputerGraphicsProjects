#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>

#include "vertex_triangle_adjacency.h"
#include <iostream>

struct Edge {
  int v1_index;
  int v2_index;
  std::string get_v1_v2_name() {
    return std::to_string(v1_index) + "|" + std::to_string(v2_index);
  };
  std::string get_v2_v1_name() {
    return std::to_string(v2_index) + "|" + std::to_string(v1_index);
  };
};

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (num_iters == 0) return; 
  // Face point of every face
  std::unordered_map<int, Eigen::RowVector3d> face_point;

  // Edge and its 2 neighbouring faces
  std::unordered_map<std::string, std::vector<int>> edge_to_faces;

  // Vertex and its adjacent vertices
  std::unordered_map<int, std::vector<int>> vertex_to_adj_vertices;

  // Lists of incident faces of each vertex
  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);

  for (int i = 0; i < F.rows(); ++i){
    Eigen::RowVector3d vertices_sum(0,0,0);
    for (int j = 0; j < F.cols(); ++j){
      int curr_vertex = F(i, j);
      vertices_sum += V.row(curr_vertex);

      // Construct the edge
      Edge edge = {curr_vertex, F(i, (j + 1)%F.cols())};
      std::string k1 = edge.get_v1_v2_name();
      std::string k2 = edge.get_v2_v1_name();
      if (std::find(edge_to_faces[k1].begin(), edge_to_faces[k1].end(), i)
        == edge_to_faces[k1].end()) { // Not found
          // Push the face index to this edge's neighbouring faces vector
          edge_to_faces[k1].push_back(i); 
      }

      // Repeat the same for the 'flipped' k2
      if (std::find(edge_to_faces[k2].begin(), edge_to_faces[k2].end(), i)
        == edge_to_faces[k2].end()) { // Not found
          // Push the face index to this edge's neighbouring faces vector
          edge_to_faces[k2].push_back(i); 
      }

      // Find the vertext adjacent to curr_vertex
      int adj_vertex = edge.v2_index;
      if (std::find(vertex_to_adj_vertices[curr_vertex].begin(),
        vertex_to_adj_vertices[curr_vertex].end(), adj_vertex)
        == vertex_to_adj_vertices[curr_vertex].end()) { // Not found
          // Push the adj_vertex to this edge's neighbouring vertices vector
          vertex_to_adj_vertices[curr_vertex].push_back(adj_vertex); 
      }

      adj_vertex = F(i, (F.cols() + (j - 1))%F.cols());
      if (std::find(vertex_to_adj_vertices[curr_vertex].begin(),
        vertex_to_adj_vertices[curr_vertex].end(), adj_vertex)
        == vertex_to_adj_vertices[curr_vertex].end()) { // Not found
          // Push the adj_vertex to this edge's neighbouring vertices vector
          vertex_to_adj_vertices[curr_vertex].push_back(adj_vertex); 
      }

    }
    // Find the average of all 4 vertices
    face_point[i] = vertices_sum/4.0;
  }

  SV = Eigen::MatrixXd::Zero(0,3);
  SF = Eigen::MatrixXi::Zero(0,4);

  // helper functions
  auto recalculate_vertex = [](int curr_vertex, Eigen::MatrixXd V,
    std::vector<std::vector<int>> VF, 
    std::unordered_map<int, Eigen::RowVector3d> face_point,
    std::unordered_map<int, std::vector<int>> vertex_to_adj_vertices) {
    
    Eigen::RowVector3d F, R, P;
    double n = (double)VF[curr_vertex].size();

    P = V.row(curr_vertex);
    Eigen::RowVector3d face_point_sum(0, 0, 0);
    for (auto & face : VF[curr_vertex]) {
      face_point_sum += face_point[face];
    }
    F = face_point_sum/n;

    Eigen::RowVector3d edge_midpoint_sum(0, 0, 0);
    for (auto & adj_vertex : vertex_to_adj_vertices[curr_vertex]) {
        edge_midpoint_sum += (P + V.row(adj_vertex))/2.0;
    }
    R = edge_midpoint_sum/(double)vertex_to_adj_vertices[curr_vertex].size();
    Eigen::RowVector3d output = (F + 2.0*R + (n-3)*P)/n;
    return output;
  };

  auto compute_edge_pt = [](int v1, int v2,
    Eigen::MatrixXd V,
    std::unordered_map<int, Eigen::RowVector3d> face_point,
    std::unordered_map<std::string, std::vector<int>> edge_to_faces) {
    
    Edge edge = {v1, v2};
    // avg_edge_pt: Average of neighbouring face points && edge end points
    Eigen::RowVector3d avg_edge_pt(0, 0, 0);
   
    // First, get the sum of neighbouring face points
    for (auto & face : edge_to_faces[edge.get_v1_v2_name()]){
      avg_edge_pt += face_point[face];
    }
    
    // Then, add the edge end points
    avg_edge_pt += V.row(edge.v1_index);
    avg_edge_pt += V.row(edge.v2_index);

    // Take the average
    Eigen::RowVector3d output = avg_edge_pt /= 4.0;

    return output;
  };

  for (int i = 0; i < F.rows(); ++i){
    for (int j = 0; j < F.cols(); ++j){
        int curr_vertex = F(i, j);

        // 2 adjacent vertices of curr_vertex on face i
        int adj_v1 = F(i, (j + 1)%F.cols());
        int adj_v2 = F(i, (F.cols() + (j - 1))%F.cols());
          
        Eigen::RowVector3d new_P = recalculate_vertex(curr_vertex, V, VF, face_point, vertex_to_adj_vertices);
        Eigen::RowVector3d edge_pt_1 = compute_edge_pt(curr_vertex, adj_v1, V, face_point, edge_to_faces);
        Eigen::RowVector3d face_pt = face_point[i];
        Eigen::RowVector3d edge_pt_2 = compute_edge_pt(curr_vertex, adj_v2, V, face_point, edge_to_faces);
        
        // Compute SV, SF using new_P
        int counter = 0;
        Eigen::RowVector4i new_face_vertices(-1, -1, -1, -1);
        std::vector<Eigen::RowVector3d> new_vertices = {new_P, edge_pt_1, face_pt, edge_pt_2};
        for (auto & pt : new_vertices) {
          // Iterate through all vertices in SV and check if there is a match
          for (int i = 0; i < SV.rows(); ++i) {
            bool isMatch = pt.isApprox(SV.row(i));
            if (isMatch) {
              // Add the vertex index (from SV) to new_face_vertices
              new_face_vertices(counter) = i;
            }
          }

          // If there is no match, add the new vertex (pt) to SV in a new row
          if (new_face_vertices(counter) == -1){
            // Add a new row to SV
            SV.conservativeResize(SV.rows() + 1, SV.cols());
            // Insert pt to the new row
            SV.row(SV.rows() - 1) = pt;
            // Record the vertex index to new_face_vertices
            new_face_vertices(counter) = SV.rows() - 1;
          }
          counter ++;
        }
        // Add a new row to SF
			  SF.conservativeResize(SF.rows() + 1, SF.cols());
        // Insert the new_face_vertices to the new row
        SF.row(SF.rows() - 1) = new_face_vertices;
    }
  }
  // Run it recursively 
  catmull_clark(SV, SF, num_iters - 1, SV, SF);
  ////////////////////////////////////////////////////////////////////////////
}
