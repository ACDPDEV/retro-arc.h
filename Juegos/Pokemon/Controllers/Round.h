#pragma once
#include <memory>
#include "../Models/Player.h"
#include "TurnController.h"
#include "../Commands/Command.h"
#include "../Views/BattleViews.h"
#include "../Sound/PokemonSound.h"
#include "../Database/State.h"
#include "../../../Common/Output.h"
#include "PlayerController.h"

namespace PokemonGame
{    
    class Round
    {
        private:
            PokemonGame::TurnController& turnOne;
            PokemonGame::TurnController& turnTwo;

            std::unique_ptr<PokemonGame::Command> playerOneCommand;
            std::unique_ptr<PokemonGame::Command> playerTwoCommand;

            void ExecuteIfIsDefensiveCommand(PokemonGame::Command* command, PokemonGame::TurnController& affectedTurn)
            {
                if( ! dynamic_cast<AttackCommand*>(command))
                {
                    command->Execute(affectedTurn.GetPlayer());
                }
            }

            void ExecuteIfIsAttackCommand(PokemonGame::Command* command, PokemonGame::TurnController& defenderTurn)
            {
                if(PokemonGame::AttackCommand* attackCommand = dynamic_cast<AttackCommand*>(command))
                {
                    attackCommand->Execute(defenderTurn.GetPlayer());
                }
            }
    
        public:
            Round(
                PokemonGame::TurnController& turnOne, 
                PokemonGame::TurnController& turnTwo)
                :
                turnOne(turnOne),
                turnTwo(turnTwo)
            {
            }
            
            ~Round() = default;

            /// @brief Plays one round of the battle.
            /// @param roundNumber Current round counter (0-based, as tracked by Battle::countRounds).
            ///        REQ-4.3: there is no speed/priority stat in the current Pokemon/PokemonSpecie
            ///        model, and adding one would be a schema change disproportionate to this phase.
            ///        Instead, turn order alternates by round parity: player 1 attacks first on
            ///        even rounds, player 2 attacks first on odd rounds. This is documented here as
            ///        the chosen minimal rule for REQ-4.3.
            void Play(int roundNumber)
            {
                // Update battle state
                ::Pokemon::battleHp1 = turnOne.GetPlayer().GetActivePokemon() 
                    ? turnOne.GetPlayer().GetActivePokemon()->GetCurrentHp() : 0;
                ::Pokemon::battleMaxHp1 = turnOne.GetPlayer().GetActivePokemon() 
                    ? turnOne.GetPlayer().GetActivePokemon()->GetMaxHp() : 0;
                ::Pokemon::battleHp2 = turnTwo.GetPlayer().GetActivePokemon() 
                    ? turnTwo.GetPlayer().GetActivePokemon()->GetCurrentHp() : 0;
                ::Pokemon::battleMaxHp2 = turnTwo.GetPlayer().GetActivePokemon() 
                    ? turnTwo.GetPlayer().GetActivePokemon()->GetMaxHp() : 0;
                ::Pokemon::battleActivePokemonId1 = turnOne.GetPlayer().GetActivePokemon() 
                    ? turnOne.GetPlayer().GetActivePokemon()->GetId() : 0;
                ::Pokemon::battleActivePokemonId2 = turnTwo.GetPlayer().GetActivePokemon() 
                    ? turnTwo.GetPlayer().GetActivePokemon()->GetId() : 0;

                //----------------------------------
                // Turno del jugador 1
                //----------------------------------

                /// Player 1 selects action via interactive battle views
                int entityId1 = -1;
                PokemonGame::ChooseCommandOption p1Option;

                while (true) {
                    p1Option = ::Pokemon::BattleMenuView(turnOne.GetPlayer(), turnTwo.GetPlayer());

                    if (p1Option == PokemonGame::ChooseCommandOption::FIGHT) {
                        entityId1 = ::Pokemon::FightMenuView(turnOne.GetPlayer(), turnTwo.GetPlayer());
                        if (entityId1 != -1) break;
                    } else if (p1Option == PokemonGame::ChooseCommandOption::BAG) {
                        entityId1 = ::Pokemon::BagMenuView(turnOne.GetPlayer(), turnTwo.GetPlayer());
                        if (entityId1 != -1) {
                            // Play heal sound if a healing item was selected
                            if (entityId1 == PlayerController::ITEM_ID_POTION || entityId1 == PlayerController::ITEM_ID_SUPER_POTION) {
                                ::Pokemon::PlayHealSound();
                            }
                            break;
                        }
                    } else if (p1Option == PokemonGame::ChooseCommandOption::POKEMON) {
                        entityId1 = ::Pokemon::PokemonMenuView(turnOne.GetPlayer());
                        if (entityId1 != -1) break;
                    } else if (p1Option == PokemonGame::ChooseCommandOption::SONIDO) {
                        // Toggle background music on/off via the PokemonSound facade
                        // (single source of truth — no direct Common::Music calls here)
                        if (::Pokemon::g_isBattleMusicPaused) {
                            // Currently paused → resume (toggle OFF)
                            ::Pokemon::ResumeBattleMusic();
                        } else {
                            // Currently playing (or no-op if nothing is playing, SCN-018) → pause (toggle ON)
                            ::Pokemon::PauseBattleMusic();
                        }
                        // Loop back to battle menu (entityId stays -1)
                    } else if (p1Option == PokemonGame::ChooseCommandOption::RUN) {
                        bool confirmed = ::Pokemon::RunConfirmationView();
                        if (confirmed) {
                            ::Pokemon::PlayEscapeSound();
                            // Execute run immediately
                            turnOne.GetPlayer().GetActivePokemon()->Run();
                            // Show flee result screen
                            std::string runnerName = turnOne.GetPlayer().GetName();
                            std::string winnerName = turnTwo.GetPlayer().GetName();
                            ::Pokemon::RunResultView(runnerName, winnerName);
                            // Battle ends — skip command validation
                            return;
                        }
                    }
                }

                playerOneCommand = turnOne.ChooseCommand(p1Option, entityId1);
                
                //----------------------------------
                // Turno del jugador 2
                //----------------------------------

                /// Player 2 selects action via interactive battle views
                int entityId2 = -1;
                PokemonGame::ChooseCommandOption p2Option;

                while (true) {
                    p2Option = ::Pokemon::BattleMenuView(turnTwo.GetPlayer(), turnOne.GetPlayer(), true);

                    if (p2Option == PokemonGame::ChooseCommandOption::FIGHT) {
                        entityId2 = ::Pokemon::FightMenuView(turnTwo.GetPlayer(), turnOne.GetPlayer(), true);
                        if (entityId2 != -1) break;
                    } else if (p2Option == PokemonGame::ChooseCommandOption::BAG) {
                        entityId2 = ::Pokemon::BagMenuView(turnTwo.GetPlayer(), turnOne.GetPlayer(), true);
                        if (entityId2 != -1) {
                            // Play heal sound if a healing item was selected
                            if (entityId2 == PlayerController::ITEM_ID_POTION || entityId2 == PlayerController::ITEM_ID_SUPER_POTION) {
                                ::Pokemon::PlayHealSound();
                            }
                            break;
                        }
                    } else if (p2Option == PokemonGame::ChooseCommandOption::POKEMON) {
                        entityId2 = ::Pokemon::PokemonMenuView(turnTwo.GetPlayer());
                        if (entityId2 != -1) break;
                    } else if (p2Option == PokemonGame::ChooseCommandOption::SONIDO) {
                        // Toggle background music on/off via the PokemonSound facade
                        // (single source of truth — no direct Common::Music calls here)
                        if (::Pokemon::g_isBattleMusicPaused) {
                            // Currently paused → resume (toggle OFF)
                            ::Pokemon::ResumeBattleMusic();
                        } else {
                            // Currently playing (or no-op if nothing is playing, SCN-018) → pause (toggle ON)
                            ::Pokemon::PauseBattleMusic();
                        }
                        // Loop back to battle menu (entityId stays -1)
                    } else if (p2Option == PokemonGame::ChooseCommandOption::RUN) {
                        bool confirmed = ::Pokemon::RunConfirmationView();
                        if (confirmed) {
                            ::Pokemon::PlayEscapeSound();
                            // Execute run immediately
                            turnTwo.GetPlayer().GetActivePokemon()->Run();
                            // Show flee result screen
                            std::string runnerName = turnTwo.GetPlayer().GetName();
                            std::string winnerName = turnOne.GetPlayer().GetName();
                            ::Pokemon::RunResultView(runnerName, winnerName);
                            // Battle ends — skip command validation
                            return;
                        }
                    }
                }

                playerTwoCommand = turnTwo.ChooseCommand(p2Option, entityId2);

                //----------------------------------
                // Validar comandos
                //----------------------------------
                bool bothCanExecute = true;
                if( ! playerOneCommand || ! playerOneCommand->CanExecute(turnOne.GetPlayer()))
                    bothCanExecute = false;

                if( ! playerTwoCommand || ! playerTwoCommand->CanExecute(turnTwo.GetPlayer()))
                    bothCanExecute = false;

                if( ! bothCanExecute)
                {
                    Common::feedbackMessage = "No se pudo ejecutar la accion seleccionada.";
                    Common::PrintFeedBackMessage();
                    Common::Sleep(1000);
                    return;
                }

                //----------------------------------
                // Ejecutar acciones defensivas
                //----------------------------------
                ExecuteIfIsDefensiveCommand(playerOneCommand.get(), turnOne);
                ExecuteIfIsDefensiveCommand(playerTwoCommand.get(), turnTwo);
                if (! turnOne.GetPlayer().CanPlay())
                    return;
                
                if (! turnTwo.GetPlayer().CanPlay())
                    return;
                
                turnOne.GetPlayer().UpdateEndOfTheTurnTeamEffects();
                turnTwo.GetPlayer().UpdateEndOfTheTurnTeamEffects();

                //----------------------------------
                // Ejecutar acciones ofensivas
                //----------------------------------
                // Capture HP before attacks for damage calculation
                double defHpBefore1 = turnTwo.GetPlayer().GetActivePokemon() ? turnTwo.GetPlayer().GetActivePokemon()->GetCurrentHp() : 0;
                double defHpBefore2 = turnOne.GetPlayer().GetActivePokemon() ? turnOne.GetPlayer().GetActivePokemon()->GetCurrentHp() : 0;

                auto executePlayerOneAttack = [&]() {
                    ExecuteIfIsAttackCommand(playerOneCommand.get(), turnTwo);
                    // BattleViews integration: show attack result after player 1 attacks
                    if (AttackCommand* atkCmd1 = dynamic_cast<AttackCommand*>(playerOneCommand.get())) {
                        std::string atkName1 = turnOne.GetPlayer().GetActivePokemon()
                            ? turnOne.GetPlayer().GetActivePokemon()->GetName() : "???";
                        std::string defName1 = turnTwo.GetPlayer().GetActivePokemon()
                            ? turnTwo.GetPlayer().GetActivePokemon()->GetName() : "???";
                        std::string moveName1 = atkCmd1->GetMove() ? atkCmd1->GetMove()->GetName() : "???";
                        // Calculate damage from HP difference
                        double defHpAfter1 = turnTwo.GetPlayer().GetActivePokemon() ? turnTwo.GetPlayer().GetActivePokemon()->GetCurrentHp() : 0;
                        int damage1 = static_cast<int>(defHpBefore1 - defHpAfter1);
                        // Get effectiveness string from move type vs defender type
                        std::string eff1 = "";
                        if (atkCmd1->GetMove() && turnTwo.GetPlayer().GetActivePokemon()) {
                            double effVal = EFFECTIVENESS[static_cast<int>(atkCmd1->GetMove()->GetType())][static_cast<int>(turnTwo.GetPlayer().GetActivePokemon()->GetType())];
                            if (effVal > 1.0) eff1 = "Es muy efectivo!";
                            else if (effVal < 1.0) eff1 = "No es muy efectivo...";
                        }
                        // Play Pokemon-specific attack sound before result display
                        int attackerId1 = turnOne.GetPlayer().GetActivePokemon()
                            ? turnOne.GetPlayer().GetActivePokemon()->GetId() : -1;
                        ::Pokemon::PlayAttackForPokemon(attackerId1);
                        ::Pokemon::AttackResultView(atkName1, moveName1, defName1, damage1, eff1);
                        // Low health sound if defender fainted
                        if (turnTwo.GetPlayer().GetActivePokemon() && turnTwo.GetPlayer().GetActivePokemon()->IsFainted()) {
                            ::Pokemon::PlayLowHealthSound();
                        }
                    }
                };

                auto executePlayerTwoAttack = [&]() {
                    ExecuteIfIsAttackCommand(playerTwoCommand.get(), turnOne);
                    // BattleViews integration: show attack result after player 2 attacks
                    if (AttackCommand* atkCmd2 = dynamic_cast<AttackCommand*>(playerTwoCommand.get())) {
                        std::string atkName2 = turnTwo.GetPlayer().GetActivePokemon()
                            ? turnTwo.GetPlayer().GetActivePokemon()->GetName() : "???";
                        std::string defName2 = turnOne.GetPlayer().GetActivePokemon()
                            ? turnOne.GetPlayer().GetActivePokemon()->GetName() : "???";
                        std::string moveName2 = atkCmd2->GetMove() ? atkCmd2->GetMove()->GetName() : "???";
                        // Calculate damage from HP difference
                        double defHpAfter2 = turnOne.GetPlayer().GetActivePokemon() ? turnOne.GetPlayer().GetActivePokemon()->GetCurrentHp() : 0;
                        int damage2 = static_cast<int>(defHpBefore2 - defHpAfter2);
                        // Get effectiveness string from move type vs defender type
                        std::string eff2 = "";
                        if (atkCmd2->GetMove() && turnOne.GetPlayer().GetActivePokemon()) {
                            double effVal = EFFECTIVENESS[static_cast<int>(atkCmd2->GetMove()->GetType())][static_cast<int>(turnOne.GetPlayer().GetActivePokemon()->GetType())];
                            if (effVal > 1.0) eff2 = "Es muy efectivo!";
                            else if (effVal < 1.0) eff2 = "No es muy efectivo...";
                        }
                        // Play Pokemon-specific attack sound before result display
                        int attackerId2 = turnTwo.GetPlayer().GetActivePokemon()
                            ? turnTwo.GetPlayer().GetActivePokemon()->GetId() : -1;
                        ::Pokemon::PlayAttackForPokemon(attackerId2);
                        ::Pokemon::AttackResultView(atkName2, moveName2, defName2, damage2, eff2);
                        // Low health sound if defender fainted
                        if (turnOne.GetPlayer().GetActivePokemon() && turnOne.GetPlayer().GetActivePokemon()->IsFainted()) {
                            ::Pokemon::PlayLowHealthSound();
                        }
                    }
                };

                // REQ-4.3: alternate who attacks first by round parity (see Play()'s doc comment).
                if (roundNumber % 2 == 0) {
                    executePlayerOneAttack();
                    executePlayerTwoAttack();
                } else {
                    executePlayerTwoAttack();
                    executePlayerOneAttack();
                }


            }
    };
}