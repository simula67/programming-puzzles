package com.wordpress.simula67.javapackages.grapOrderingProblem;

import junit.framework.TestCase;

public class GraphTest extends TestCase {

    public void testAddEdgeMaintainOrder() throws Exception {

        /* This is the graph we are testing for

        A         ------>      B          ------>         C      ----------> D

        When we use addEdgeMaintainOrder to add an edge from D to A it fails because it detects that that will form a cycle and refuses to insert it.
        Afterwards we validate the graph by querying it.

         */




        // Create the graph
        Graph graph = new Graph();
        graph.addVertex("A");
        graph.addVertex("B");
        graph.addVertex("C");
        graph.addVertex("D");

        // Add edge using maintain order. These should succeed
        graph.addEdgeMaintainOrder("A", "B");
        graph.addEdgeMaintainOrder("B", "C");
        graph.addEdgeMaintainOrder("C", "D");

        // The following should fail since this will create a cycle
        graph.addEdgeMaintainOrder("D", "A");

        /*
        BEGIN VERIFICATION OF GRAPH STRUCTURE
        ======================================
         */

        // NO vertices are connected to A
        assertTrue(graph.getGraphNodeForVertex("A").verticesConnectedToThisNode.isEmpty());

        // One vertices are connected to each of B,C,D
        assertEquals(graph.getGraphNodeForVertex("B").verticesConnectedToThisNode.size(), 1);
        assertEquals(graph.getGraphNodeForVertex("C").verticesConnectedToThisNode.size(), 1);
        assertEquals(graph.getGraphNodeForVertex("D").verticesConnectedToThisNode.size(), 1);

        // Further integrity checks
        // Make sure that B reports that A is connected to B, C reports that B is connected to C, and D reports that C is connected to D
        assertTrue(graph.getGraphNodeForVertex("B").verticesConnectedToThisNode.get(0).equalsIgnoreCase("A"));
        assertTrue(graph.getGraphNodeForVertex("C").verticesConnectedToThisNode.get(0).equalsIgnoreCase("B"));
        assertTrue(graph.getGraphNodeForVertex("D").verticesConnectedToThisNode.get(0).equalsIgnoreCase("C"));

        // Further integrity checks
        // Make sure that there are still only 4 vertices in the graph
        assertEquals(graph.graphNodes.size(), 4);

    }
}