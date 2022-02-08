To: Professor Benjamin Scott Lerner

From: Luke Quirion and James Peterson 

Subject: Plan for Train.com Map Visualization Program

The visualization program should consume a Map object. It would use the getter methods from the Map to retrieve City and Connection information to use in visualizing the cities and connections between them.

The exact positions of the cities on the map don't matter for our map program. The map just has all of the Cities which have Connections as well as Destinations with bonus points. It does not care about the positioning of the cities. The visualization program will need to determine the layout of the cities. However it must ensure that Connections do not cross over each other.

The map visualization should be constructed like an undirected graph. The cities would be the vertices with their name either visible above or inside the visual representation of the city (what the cities themselves look like on the map is up to those behind the visualization program). The edges would be the Connections. They would be highlighted if the road is occupied. The coloring of the occupied Connection (aka rail track) is dependent on the colored card used by players and is as a result not a concern for our Map, it's a concern for our Player interface which is yet to be constructed.