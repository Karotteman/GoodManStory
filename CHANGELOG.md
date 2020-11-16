# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [0.2.0] (BETA) - 2020-11-13
### Added
- Add blood decal on ground with flower shape
- Add levelup particle
- Rework main map (coline and catle died for caverne and tower)
- Ocean kill now entities
- Difficulty function that compute the boss level
- Integrate sounds and musics
- Add boss life bar
- Add trail on hammer for the lavel 2
- Add juicyness for ground attack
- Add juicyness for fireball attack
- Add juicyness for rage bar
- Add juicyness for each fireball
- Add lots of gamepad vibration and gamepad shake
- Player unlock gold armor at level 4
- Add start animation for the boss with AI delay
- Create UX :
    - Create main menu
    - Create settings with abilty to change the sensibility, music sound, fx sound and invert axis
    - Create in game sub menu
    - Create win and loose HUD


### Change
- Use the mesh physical asset of the boss insteat of it's capusle callider (more presicion)
- Rework boss AI (Can now try only one attack at time)
- clean and optimize animBP

### Fixed
- Tourbilol inflict only 1 hit
- Wave not reset on end of the wave
- Crash error on battle fixe
- Player canno't do tourbilol or other skills if he try during it
- Animation of tourbilol tutter
- Fixe waveManager warning
- Player canno't unlock evile spell capacity
- Fixe enemies can spawn on the floor
- Boss is now alway is front of play on punsh and throw fire ball
- Fixe speed and damage of ground attack don't work properly
- Remove collision between camera and the boss
- Fixe epileptique leg for the boss


## [0.1.4] - 2020-11-05
### Added
- Create fire ball attack for the boss
- Create explosive fire ball
- Create repulsive fire ball
- Create teleportation zone
- Create blood splat on enemies with particul and decale
- Add stun animation and stun feature for warrior
- Basic camera shake on boss choc wave
- GamePad shake for on boss choc wave, fire ball player hit and tank hit by player
- Create player jump animation and improve it with new animation
- Add fire ball particle for repulsive fire ball
- Add evil capacity
- Add max life range for the fireball
- Add weak zone for the Boss
- Add check point when the player died
- Add lot of call back for the enemies
- Integrate all new feature in trash arena
- Link trashArena with new map : Boss arena (don't work properly yet)
- Add behaviours for each level unlock by the player

### Change
- Create crash message if user try to start scene without dataTable in enmie manager
- Blend walk animation with attack

### Fixed 
- Camera zone don't work propely
- Trash can now be struck by the boss grounsd attack
- Eneity can now be hit only once time by the fire ball and the player
- OnCharacterDestroy don't work fixed
- Player canno't now charge during basic attack. Bug fixe with hit boox always activate after basic atttack
- Fixe trashTank and agressivTrash walk animation
- Adjust mesh position for all entites
- Adjust side walk speed
- Wave call now the end wave callback at the last wave

## [0.1.3] - 2020-10-29
### Added
- CReate toubilol atttack for the player
- Create boss behaviours :
    - Create ground attack with choc wave feature
    - Create punch hit attack
    - Create lots of callback to integrate ore easly particule, sound and behaviours
- Create callback for each level unlock by the player to controle more easly the behaviours of the player
- Integrate feature to LD in new map : Trash Arena
- Create callback for each wave to controle action on start and end of wave

### Change
- Create basic death for the player (restart the world)
- Rework enemies architectur

### Fixed
- Player freezed at the first trash hit
- Player could move the boss on ratotation

## [0.1.3] (ALPHA) - 2020-10-22
### Added
- Add limite of entity and limite of weapon on the map
- Add charge skill. Player can now roll on its enemies and push it
- Player can now push its enemy and can walk more easly
- Add lots of call back to controle event, debug and integrate effect
- Add WarriorCharacter betwen BaseChacter and PlayerCharacter/EnemyCharacter
- Create boss (stay idle for now, WIP)
- create score system. When player hit enemy he win its life and additionnal rage reward of its enemy
- Create differente possibility to unlock skills and new stats with level. Implementation with callback in blueprint for more controle of action

### Changed
- Change propulsion of trashmob from unreal physic to our physic to controle each launch
- Player can now chose it's direction when he figth with combo

### Fixed 
- Rework spawner and add possibility to choose many randome spawner
- Spawner can now spawn entity on heigth

## [0.1.0] - 2020-10-15
### Added
- Create spawner with differente zone to activate it. Enemy manager manage all the spawner and enemies waves
- Game designer can now create wave with dataTable
- Enemies can now attack the player

### Fixed 
- The player move now always forward him

### Removed
- Remove access to prototype menu with escape on the main scene
- Removeprototype menu as main scene and replace by the protottype scene
- Remove velocity when player hit its enemies (WIP)

## [0.0.1] (3C) - 2020-10-08
### Added
- Create 3C prototype
- Create player
- Create trashmob
- Add computer and gamepad input (display text on input activated)
- Add 4 combo to player with left clic and X
- Add epic trash mob death with ragdoll
- Add capacity to move with ZQSD and left joystick
- Add capacity to move camera with mouse and rigth joystick
- Add capacity to change the camera sholder side with tab and Rigth joystick click
- Add capacity to jump with space and A
- Add capacity to restart scene with R
- Add menu to genertate trash mob spawn (backspace = return to menu/ enter = go to scene)
- Add profiling function with touch J, K and L
- Add quit game with escape