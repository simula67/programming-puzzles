package com.wordpress.simula67.javapackages.grapOrderingProblem;

import java.util.LinkedList;
import java.util.List;


public class Graph
{
    List<GraphNode> graphNodes;

    Graph()
    {
        this.graphNodes = new LinkedList<GraphNode>();
    }
    void addVertex(String vertex)
    {
        GraphNode graphNode = new GraphNode();
        graphNode.vertex = vertex;
        graphNode.verticesConnectedToThisNode = new LinkedList<String>();
        this.graphNodes.add(graphNode);
    }

    void addEdge(String fromVertex, String toVertex)
    {
        for ( GraphNode graphNode : this.graphNodes) {
            if (graphNode.vertex.equalsIgnoreCase(toVertex))
            {
                graphNode.verticesConnectedToThisNode.add(fromVertex);
            }
        }
    }

    void addEdgeMaintainOrder(String fromVertex, String toVertex) throws Exception {
        if(!doesToVertexComeBeforeFromVertex(fromVertex, toVertex))
        {
            addEdge(fromVertex,toVertex);
        }
    }

    GraphNode getGraphNodeForVertex(String vertex) throws Exception
    {
        for (GraphNode graphNode : this.graphNodes)
        {
            if(graphNode.vertex.equalsIgnoreCase(vertex))
            {
                return graphNode;
            }
        }
        throw new Exception("Cannot find the graph node for vertex : \"" + vertex + "\"");

    }

    private boolean doesToVertexComeBeforeFromVertex(String fromVertex, String toVertex) throws Exception
    {
        GraphNode fromVertexGraphNode = getGraphNodeForVertex(fromVertex);
        for( String vertexConnectedToFromVertex : fromVertexGraphNode.verticesConnectedToThisNode)
        {
            return vertexConnectedToFromVertex.equalsIgnoreCase(toVertex) || doesToVertexComeBeforeFromVertex(vertexConnectedToFromVertex, toVertex);
        }
        // Searched throughout the graph
        return false;
    }
}
