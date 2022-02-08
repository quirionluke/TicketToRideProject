# Missing:

  - Drawing train lines on top of each other in the Visualizer
  - Calculating longest path and awarding destination points
  - Cheat strategy implementation
  - Ending game phase and ending the game
  - Loading a (Strategy) class from a file path a.k.a dynamic loading
  - Sending the player a map in addition to their gamestate
  - Manager selecting what cards to hand to players
  - Manager selecting what order to select destinations
  - Weighted randomness on dealing cards
  - Actually using a lot of the config file variables (checking validity of certain numbers)
  - Actual unit tests for our methods so we can prove that they function
  - Checking all of our memory management stuff so we don’t have any leaks
  - Double check that everything allocated with “new” is deleted with “delete”
  - Timing out a player and booting them when they don’t respond within a few seconds

# Broken:
  - IsGameOver in Referee doesn’t ever return true unless there is only one player in the game
  - Choosing the destinations for buynow and hold10 (lexigraphic sorting is kinda wonk)
  - Detecting cheating players / moving them to the cheating list
  - Making players take their turns (this might have to do with Strategy)


# Etc:
  - a bunch of nonsense to the main gameplay loop to make the testing task for milestone 8 run (get rid of int i = 10000 please)
  - Remove the getters before final push (they are only used for testing)
