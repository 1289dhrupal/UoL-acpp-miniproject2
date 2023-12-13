# Game Project - Read Me

## Overview
This text-based game is structured with a focus on simplicity and specific game mechanics. Please note the following key points while playing the game:

1. **First Objective Considered**: The game considers only the first objective listed in the game data. Subsequent objectives, if any, are not taken into account.

2. **First 'KilledBy' Object Considered**: In scenarios involving combat or enemy interactions, only the first 'killedby' object listed for an enemy will be considered effective.

3. **Input Format**: Commands should be provided in separate lines. Each part of a command is entered separately for clear and sequential processing.

## Command Format
When entering commands, split them into separate lines as follows:

- For a command like `attack enemyID objectID`, enter it as:
    ```
    Command1: attack
    Command2: enemyID
    Command3: objectID
    ```

- For a command like `look room`, enter it as:
    ```
    Command1: look
    Command2: room
    Command3: 
    ```
  Leave the third line blank if the command doesn't require a third parameter.

## Playing the Game
- Start the game and follow the on-screen instructions.
- Enter commands as per the format specified above to interact with the game world.
- Navigate through rooms, interact with objects and enemies, and achieve the objective to progress in the game.

## Notes
- This game is designed to follow the command structure strictly. Please ensure to follow the input guidelines for a smooth gaming experience.

Thank you for playing, and enjoy the game!

# Game Project - Read Me

## Overview
This text-based game features strategic combat and room navigation. Players must carefully choose their actions to progress. The game has specific rules for combat interactions and room exits.

## Attack Logic
1. **Effective Attacks**:
   - If the enemy can be killed by the specified object, the object's durability only reduces by 1, and the enemy is killed.
   - For example:
     ```
     Command1: attack
     Command2: enemyID
     Command3: objectID
     ```

2. **Ineffective Attacks**:
   - If the enemy is not to be killed by the object but the player uses it anyway, the object's durability is reduced by the same amount as the enemy's aggressiveness.
   - For example:
     ```
     Command1: attack
     Command2: enemyID
     Command3: otherObjectID
     ```

3. **Exiting Rooms with Enemies**:
   - If a player chooses to exit a room without defeating the enemy, their health is reduced by the amount of the enemy's aggressiveness.

## Input Format
Commands should be provided in separate lines. Each part of a command is entered separately for clear and sequential processing.

- For a command like `look room`, enter it as:
    ```
    Command1: look
    Command2: room
    Command3: 
    ```

## Playing the Game
- Start the game and follow the on-screen instructions.
- Use the combat mechanics wisely to defeat enemies or strategically decide when to retreat.
- Remember, your decisions will impact your character's health and the durability of your items.

Thank you for playing, and enjoy the game!
