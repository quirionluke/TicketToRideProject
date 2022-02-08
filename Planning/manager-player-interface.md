To: Professor Lerner

From: Luke Quirion and Jamie Peterson

Subject: Tournament Manger Design Document

The Tournament Manager will need to perform the following tasks
- Create a game with a Referee and assigned Players and Return the Game created.
- Assign Players to a given Referee from a pool of potential Players
- Assign Players to tournaments aka squences of games run by different Referees and return the created Tournament Object (however that is implemented)
- Create a Referee with an associated Map and return it
- The above could also be split into a method that creates a randomized map or reads it in from a json. These details are TBD.
- Produce some kind of metric that can be consumed by the Observer component
- Connect an Observer to an ongoing game

A Game object simply contains the RefereeGS which contains all game information as well as the previous and next scheduled Game.
The future scheduled game may not have any players assigned to it yet.

As a result of these needed functionalities, the Tournament Manager will need to keep track of all connected Players and Observers, 
Referees and their associated games (which are represented in the RefereeGS).

The Player will change by adding the following functionalities:
- Keep track of wins and / or overall points (depending on tournament specifications)
- Clear PlayerGS and replace it with an empty game state or a new game

The Referee will not change as it is designed to only handle a single game and is self contained.
