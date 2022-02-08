To: Professor Benjamin Scott Lerner

From: James Peterson and Luke Quirion

Subject: Data Design for Game State 

We will create a game state struct called State that contains:
- a copy of the starting Map (so it cannot be mutated)
  - this will allow us to view what Connections are available at any time
- a reference to each Player
- a reference to the visualizer which will allow it to update the visual representation of the board

The State can:
- execute the desired move of a Player
- update the visual representation to show a Player's move
- check validity of Player's move (aka "referee method")

We will create a Player struct that contains:
- a List of colored cards that is called the Hand
  - a Card is one of the valid colors RED BLUE GREEN WHITE
- an unsigned integer representation of their total score
- a Set<Destination> which represents the Player's goal(s)
- a Set<Connections> which represents the Player's owned Connections

A Player can:
- send a request to update the game State
- take ownership of an unowned Connection using the Cards in their Hand
- view a visual representation of the board (likely over TCP or some similar protocol)
- draw a Card into their Hand
