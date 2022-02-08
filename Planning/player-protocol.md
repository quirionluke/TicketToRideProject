To: Professor Lerner

From: James Peterson and Luke Quirion

Subject: Player Protocol Design Document

Summary:

The protocol must be able to spell out all phases of a tournament of trains.

It needs to have a method that can initialize an individual Player or many Players.

It should not need to be able to create a Map as this would be handled by the tournament manager.

It needs to have a method that can pass a Player turn request to a Referee. This would likely
come in as some JSON that Requests cards and/or a Connection.

It also needs to have a method that communicates to a Player that it is their turn.

It needs to be able to check the status of of the game and if it is over. 
It should also have a way to communicate with the tournament manager (however that system is designed in the future)
to allow a Player to see where they are in the tournament.

