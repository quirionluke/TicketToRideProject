**To: Professor Lerner**\
**From: Luke Quirion and James Peterson**\
**Subject: Player Interface Design Document**\
   \
   \
Summary:

The player interface will be represented by a struct that handles the communication in between the AI and the referee.

Since we don't quite know yet how the AI will be interacting with our system, 
we will be missing the method where we translate player inputs into data for the Referee and Player gamestates to comprehend.
However, we plan on having that method so that if the way the AI are interacting with our system changes, we only change that one method.



Pseudocode:

// including both RefereeGS and PlayerGS

// the CommunicationProtocol will handle the translation of AI input into gamestate data as well as letting the referee check legal moves
struct CommunicationProtocol {

    // a reference to the RefereeGS to check legality
        // we don't need a reference to the PlayerGS because the RefereeGS has that already
    
    // a reference to all AI's PlayerGS's
        // this means we need to know which player they are
        // this will be represented by a Vector of PlayerGS
        // ** a Vector is essentialy a List in C++, it's an ordered list items,
        // ** in this case, PlayerGS objects
        
    // Some kind of Map (ie: unordered_map in C++) that links up an AI player to their respective game state
        // this depends on how the AI player's themselves are represented. As it is now, the Players are separate from the game state

    // some method to turn AI json input into usable data for our system
        input --> json represented by or in Trains/Other/json-c/
        output --> a PlayerGS representing the AI's desired game state after their move

    // some method to query the RefereeGS on the legality of the given move
        input --> a PlayerGS representing the outcome of the desired
        output --> Boolean value that represents whether the move is valid or not (true = valid)

    // some method to ping the AI to let them know its their turn
        input --> an Integer representing the position in the turn order the AI has
        output --> some response value / code (depends on how the network is structured, we don't know this right now)

    // some method to pass the updated gamestate back to the AI as a json
        input --> an Inter representing the position in the turn order the AI has
        output --> some response value / code (depends on how the network is structured, we don't know this right now)

}
