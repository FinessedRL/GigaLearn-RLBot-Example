//#include "RLBotClient.h"
//////
//#include <rlbot/platform.h>
//#include <rlbot/botmanager.h>
#include <RLGymCPP/ActionParsers/DefaultAction.h>
#include <RLGymCPP/ActionParsers/coyoteaction.h>
#include <RLGymCPP/OBSBuilders/DefaultObsPadded.h>
//#include <rlbot/color.h>
//#include <rlbot/scopedrenderer.h>
////
//using namespace RLGC;
//using namespace GGL;
//float seconds_elapsed_since_actor_load = 0.0f;
//float seconds_elapsed_since_kickoff = 0.0f;
//bool should_score_orange = false;
////
std::filesystem::path GetLatestPolicyFolder3(const std::filesystem::path& checkpointsDir) {
    std::filesystem::path latestFolder;
    std::filesystem::file_time_type latestTime;

    for (const auto& entry : std::filesystem::directory_iterator(checkpointsDir)) {
        if (entry.is_directory()) {
            // Skip the "policy_versions" folder
            if (entry.path().filename() == "policy_versions") {
                continue;
            }

            auto lastWriteTime = std::filesystem::last_write_time(entry);
            if (latestFolder.empty() || lastWriteTime > latestTime) {
                latestFolder = entry.path();
                latestTime = lastWriteTime;
            }
        }
    }

    return latestFolder; // Return the folder itself, not the POLICY.lt file
}
//
//
//RLBotParams g_RLBotParams = {};
//
//rlbot::Bot* BotFactory(int index, int team, std::string name) {
//	return new RLBotBot(index, team, name, g_RLBotParams);
//}
//
//void RLBotBot::InitializePredictionArena() {
//    RocketSim::ArenaConfig arenaConfig;
//    predictionArena = RocketSim::Arena::Create(RocketSim::GameMode::SOCCAR, arenaConfig, 120.0f);
//    //std::cout << "[Bot " << index << "] Created prediction arena at: " << predictionArena << std::endl;
//    predictionArena->ordered_cars.push_back(predictionArena->AddCar(Team::BLUE));
//    predictionArena->ordered_cars.push_back(predictionArena->AddCar(Team::ORANGE));
//
//}
//
//RLBotBot::RLBotBot(int _index, int _team, std::string _name, const RLBotParams& params) 
//	: rlbot::Bot(_index, _team, _name), params(params), predictionArena(nullptr) {
//
//    RocketSim::Init("./collision_meshes", true);
//
//	RG_LOG("Created RLBot bot: index " << _index << ", name: " << name << "...");
//
//    InitializePredictionArena();
//
//    std::cout << " > Done!\n";
//}
//
//RLBotBot::~RLBotBot() {
//	delete g_RLBotParams.inferUnit;
//    delete predictionArena;
//}
//
//
//Vec ToVec(const rlbot::flat::Vector3* rlbotVec) {
//	return Vec(rlbotVec->x(), rlbotVec->y(), rlbotVec->z());
//}
//
//PhysState ToPhysObj(const rlbot::flat::Physics* phys) {
//	PhysState obj = {};
//	obj.pos = ToVec(phys->location());
//
//	Angle ang = Angle(phys->rotation()->yaw(), phys->rotation()->pitch(), phys->rotation()->roll());
//	obj.rotMat = ang.ToRotMat();
//
//	obj.vel = ToVec(phys->velocity());
//	obj.angVel = ToVec(phys->angularVelocity());
//
//	return obj;
//}
//
//// Modify InitializeCarState to return hasFlipX as a std::pair
//std::pair<CarState, bool> InitializeCarState(RocketSim::Car* rocketSimPlayer, const rlbot::flat::PlayerInfo* playerInfo, const RLGC::Action& controls) {
//    CarState carState = {};
//    bool hasFlipX = false;  // Initialize hasFlipX
//
//    if (rocketSimPlayer != nullptr) {
//        const auto& rocketSimState = rocketSimPlayer->GetState();
//        carState.updateCounter = rocketSimState.updateCounter;
//        carState.isOnGround = rocketSimState.isOnGround;
//        memcpy(carState.wheelsWithContact, rocketSimState.wheelsWithContact, sizeof(carState.wheelsWithContact));
//        carState.hasJumped = rocketSimState.hasJumped;
//        carState.hasDoubleJumped = rocketSimState.hasDoubleJumped;
//        carState.hasFlipped = rocketSimState.hasFlipped;
//        carState.flipRelTorque = rocketSimState.flipRelTorque;
//        carState.flipTime = rocketSimState.flipTime;
//        carState.isFlipping = rocketSimState.isFlipping;
//        carState.isJumping = rocketSimState.isJumping;
//        carState.jumpTime = carState.isOnGround ? 0 : rocketSimState.jumpTime;
//        carState.airTime = rocketSimState.airTime;
//        carState.airTimeSinceJump = rocketSimState.airTimeSinceJump;
//        carState.boost = playerInfo->boost();
//        carState.timeSpentBoosting = rocketSimState.timeSpentBoosting;
//        carState.isSupersonic = rocketSimState.isSupersonic;
//        carState.supersonicTime = rocketSimState.supersonicTime;
//        carState.handbrakeVal = rocketSimState.handbrakeVal;
//        carState.isAutoFlipping = rocketSimState.isAutoFlipping;
//        carState.autoFlipTimer = rocketSimState.autoFlipTimer;
//        carState.autoFlipTorqueScale = rocketSimState.autoFlipTorqueScale;
//        carState.worldContact = rocketSimState.worldContact;
//        carState.carContact = rocketSimState.carContact;
//        carState.isDemoed = playerInfo->isDemolished();
//        carState.demoRespawnTimer = rocketSimState.demoRespawnTimer;
//        carState.ballHitInfo = rocketSimState.ballHitInfo;
//        carState.lastControls = rocketSimState.lastControls;
//
//        hasFlipX =
//            !carState.hasDoubleJumped && !carState.hasFlipped
//            && carState.airTimeSinceJump < RLConst::DOUBLEJUMP_MAX_DELAY;
//    }
//    else {
//        //std::cout << "[WARNING] RocketSim car is null for index: " << playerInfo->spawnId() << std::endl;
//        // Fallback to using playerInfo for some fields
//        carState.hasJumped = playerInfo->jumped();
//        carState.hasDoubleJumped = playerInfo->doubleJumped();
//        carState.isDemoed = playerInfo->isDemolished();
//        carState.boost = playerInfo->boost();
//    }
//
//    return { carState, hasFlipX };  // Return both carState and hasFlipX
//}
//
//Player ToPlayer(const rlbot::flat::PlayerInfo* playerInfo, RocketSim::Car* rocketSimPlayer, uint64_t ticks, int tickSkip, const rlbot::GameTickPacket& gameTickPacket, const RLGC::Action& controls, int playerIndex) {
//	Player pd = {};
//	static_cast<PhysState&>(pd) = ToPhysObj(playerInfo->physics());
//    
//	pd.carId = playerInfo->spawnId();
//	pd.team = (Team)playerInfo->team();
//    //std::cout << playerInfo->team() << std::endl;
//    auto [carState, hasFlipX] = InitializeCarState(rocketSimPlayer, playerInfo, controls);
//    //std::cout << "isOnGround: " << carState.isOnGround << ", jumpTime: " << carState.jumpTime << std::endl;
//    pd.index = playerIndex;
//    
//    
//    pd.ballTouchedStep = false;
//    pd.ballTouchedTick = false;
//    
//    pd.boost = carState.boost;
//    pd.isOnGround = carState.isOnGround;
//    pd.hasJumped = carState.hasJumped;
//    pd.hasDoubleJumped = carState.hasDoubleJumped;
//    pd.isDemoed = carState.isDemoed;
//    
//	return pd;
//
//    //Player pd = {};
//    //
//	//static_cast<PhysState&>(pd) = ToPhysObj(playerInfo->physics());
//    //
//	//pd.carId = playerInfo->spawnId();
//    //
//	//pd.team = (Team)playerInfo->team();
//    //
//	//pd.boost = playerInfo->boost();
//	//pd.isOnGround = playerInfo->hasWheelContact();
//	//pd.hasJumped = playerInfo->jumped();
//	//pd.hasDoubleJumped = playerInfo->doubleJumped();
//	//pd.isDemoed = playerInfo->isDemolished();
//
//	//return pd;
//}
//
//GameState ToGameState(rlbot::GameTickPacket& gameTickPacket, int ticksElapsed, int tickSkip, const std::vector<RocketSim::Car*>& rocketSimCars, uint64_t tickCount, const RLGC::Action& controls) {
//    GameState gs = {};
//    const rlbot::flat::Touch* latestTouch = gameTickPacket->ball()->latestTouch();
//    float currentTime = gameTickPacket->gameInfo()->secondsElapsed();
//
//    auto players = gameTickPacket->players();
//    for (int i = 0; i < players->size(); i++) {
//        RocketSim::Car* rocketSimCar = (i < rocketSimCars.size()) ? rocketSimCars[i] : nullptr;
//        Player player = ToPlayer(players->Get(i), rocketSimCar, tickCount, tickSkip, gameTickPacket, controls, i);
//
//        if (latestTouch != nullptr &&
//            latestTouch->gameSeconds() > 0 &&
//            i == latestTouch->playerIndex() &&
//            currentTime - latestTouch->gameSeconds() < tickSkip / 120.0f) {
//            player.ballTouchedStep = true;
//        }
//        else {
//            player.ballTouchedStep = false;
//        }
//
//        gs.players.push_back(player);
//    }
//
//    static_cast<PhysState&>(gs.ball) = ToPhysObj(gameTickPacket->ball()->physics());
//
//    auto boostPadStates = gameTickPacket->boostPadStates();
//    if (boostPadStates->size() != CommonValues::BOOST_LOCATIONS_AMOUNT) {
//        if (rand() % 20 == 0) {
//            RG_LOG(
//                "RLBotClient ToGameState(): Bad boost pad amount, expected " << CommonValues::BOOST_LOCATIONS_AMOUNT << " but got " << boostPadStates->size()
//            );
//        }
//        std::fill(gs.boostPads.begin(), gs.boostPads.end(), 1);
//    }
//    else {
//        for (int i = 0; i < CommonValues::BOOST_LOCATIONS_AMOUNT; i++) {
//            gs.boostPads[i] = boostPadStates->Get(i)->isActive();
//            gs.boostPadsInv[CommonValues::BOOST_LOCATIONS_AMOUNT - i - 1] = gs.boostPads[i];
//            gs.boostPadTimers[i] = boostPadStates->Get(i)->timer();
//            gs.boostPadTimersInv[CommonValues::BOOST_LOCATIONS_AMOUNT - i - 1] = gs.boostPadTimers[i];
//        }
//    }
//
//    return gs;
//}
//
//RLGC::Action ConvertToAction(const rlbot::Controller& controller) {
//    RLGC::Action action;
//    action.throttle = controller.throttle;
//    action.steer = controller.steer;
//    action.pitch = controller.pitch;
//    action.yaw = controller.yaw;
//    action.roll = controller.roll;
//    action.jump = controller.jump;
//    action.boost = controller.boost;
//    action.handbrake = controller.handbrake;
//    return action;
//}
//
//void RLBotBot::UpdatePredictionArena(const RLGC::GameState& gs) {
//    if (!updatePredictionArenaEnabled) return;
//    if (predictionArena == nullptr) {
//        std::cout << "Prediction arena is null" << std::endl;
//        return;
//    }
//
//    // Update ball state
//    RocketSim::BallState ballState = predictionArena->ball->GetState();
//    ballState.pos = RocketSim::Vec(gs.ball.pos.x, gs.ball.pos.y, gs.ball.pos.z);
//    ballState.vel = RocketSim::Vec(gs.ball.vel.x, gs.ball.vel.y, gs.ball.vel.z);
//    ballState.angVel = RocketSim::Vec(gs.ball.angVel.x, gs.ball.angVel.y, gs.ball.angVel.z);
//    predictionArena->ball->SetState(ballState);
//   
//    auto cars = predictionArena->GetCars();
//    if (cars.empty()) {
//        std::cout << "No cars in prediction arena" << std::endl;
//        return;
//    }
//
//    RocketSim::Car* localCar = nullptr;
//    for (auto car : cars) {
//        if (car->team == (Team)team) {
//            localCar = car;
//            break;
//        }
//    }
//
//    if (!localCar) {
//        std::cerr << "[Bot " << index << "] WARNING: localCar was not found for team " << team << std::endl;
//        return; // Prevent undefined behavior (and makes Visual Studio shut up)
//    }
//
//    // Update local car state
//    const auto& localPlayer = gs.players[index];
//
//    RocketSim::CarState localCarState = localCar->GetState();
//    localCarState.pos = RocketSim::Vec(localPlayer.pos.x, localPlayer.pos.y, localPlayer.pos.z);
//    localCarState.vel = RocketSim::Vec(localPlayer.vel.x, localPlayer.vel.y, localPlayer.vel.z);
//    localCarState.angVel = RocketSim::Vec(localPlayer.angVel.x, localPlayer.angVel.y, localPlayer.angVel.z);
//    localCarState.rotMat = localPlayer.rotMat;
//    localCarState.isDemoed = localPlayer.isDemoed;
//    localCar->SetState(localCarState);
//    localCar->controls = (CarControls)controls;
//
//    // Update opponent car if present
//    if (cars.size() > 1) {
//        RocketSim::Car* opponentCar = nullptr;
//        for (auto car : cars) {
//            if (car->team != (Team)team) {
//                opponentCar = car;
//                break;
//            }
//        }
//        const Player* opponent = nullptr;
//        for (const auto& player : gs.players) {
//            if (player.team != localPlayer.team) {
//                opponent = &player;
//                break;
//            }
//        }
//
//        if (opponent) {
//            RocketSim::CarState opponentCarState = opponentCar->GetState();
//            opponentCarState.pos = RocketSim::Vec(opponent->pos.x, opponent->pos.y, opponent->pos.z);
//            opponentCarState.vel = RocketSim::Vec(opponent->vel.x, opponent->vel.y, opponent->vel.z);
//            opponentCarState.angVel = RocketSim::Vec(opponent->angVel.x, opponent->angVel.y, opponent->angVel.z);
//            opponentCarState.rotMat = opponent->rotMat;
//            opponentCarState.hasJumped = opponent->hasJumped;
//            opponentCarState.hasDoubleJumped = opponent->hasDoubleJumped;
//            opponentCarState.isDemoed = opponent->isDemoed;
//            opponentCar->SetState(opponentCarState);
//            //opponentCar->controls = (CarControls)controls;
//        }
//        else {
//            //std::cout << "Opponent not found in game state" << std::endl;
//        }
//    }
//
//    predictionArena->Step(1);
//}
//
//bool hasSetTickSkip = false;
//
//void RLBotBot::UpdateControls(RLGC::Action act) {
//    controls.throttle = act.throttle;
//    controls.steer = act.steer;
//    controls.pitch = act.pitch;
//    controls.yaw = act.yaw;
//    controls.roll = act.roll;
//    controls.jump = act.jump;
//    controls.boost = act.boost;
//    controls.handbrake = act.handbrake;
//}
//
//std::string RLBotBot::formatVec(const Vec& v) const {
//    std::ostringstream oss;
//    oss << std::fixed << std::setprecision(2) << "(" << v.x << ", " << v.y << ", " << v.z << ")";
//    return oss.str();
//}
//
//std::string RLBotBot::formatFloat(float value) const {
//    std::ostringstream oss;
//    oss << std::fixed << std::setprecision(2) << value;
//    return oss.str();
//}
//
//void RLBotBot::RenderCarStateTable(const GameState& gs) {
//    rlbot::ScopedRenderer renderer("carstate_renderer");
//
//    // Define color variables for conditional transparency
//    rlbot::Color visibleColor{ 255, 255, 255, 255 };
//    rlbot::Color transparentColor{ 0, 0, 0, 0 };
//    rlbot::Color bgColor{ 64, 64, 64, 192 };
//    rlbot::Color bgTransparentColor{ 0, 0, 0, 0 };
//
//    if (!renderCarStateTableEnabled) {
//        visibleColor = transparentColor;
//        bgColor = bgTransparentColor;
//    }
//
//    const Player& player = gs.players[index];
//
//    float x = 20.0f;
//    float y = 50.0f;
//    float marginLeft = 30.0f;
//    float marginTop = 20.0f;
//    float nameSpacing = 150.0f;
//    float vecSpacing = 130.0f;
//    float lineSpacing = 25.0f;
//    float padding = 20.0f;
//    float panelSpacing = 150.0f;
//    float extraBottomPadding = 40.0f; // Extra padding at the bottom of each panel
//
//    std::vector<std::tuple<std::string, std::string, std::string, std::string>> mainLines;
//    std::vector<std::tuple<std::string, std::string>> secondaryLines;
//
//    auto addMainLine = [&](const std::string& label, const std::string& value, const std::string& value2 = "", const std::string& value3 = "") {
//        mainLines.emplace_back(label, value, value2, value3);
//    };
//
//    auto addSecondaryLine = [&](const std::string& label, const std::string& value) {
//        secondaryLines.emplace_back(label, value);
//    };
//
//    // Add main panel lines
//    addMainLine("On Ground", std::to_string(player.isOnGround));
//    addMainLine("Has Jumped", std::to_string(player.hasJumped));
//    addMainLine("Has Double Jumped", std::to_string(player.hasDoubleJumped));
//    addMainLine("Has Flipped", std::to_string(player.hasFlipped));
//    addMainLine("Is Flipping", std::to_string(player.isFlipping));
//    addMainLine("Is Jumping", std::to_string(player.isJumping));
//    addMainLine("Jump Time", formatFloat(player.jumpTime));
//    addMainLine("Flip Time", formatFloat(player.flipTime));
//    addMainLine("Air Time", formatFloat(player.airTime));
//    // Add secondary panel lines
//    addSecondaryLine("Boost", formatFloat(player.boost));
//    addSecondaryLine("Is Supersonic", std::to_string(player.isSupersonic));
//    addSecondaryLine("Supersonic Time", formatFloat(player.supersonicTime));
//    addSecondaryLine("Time Boosting", formatFloat(player.timeSpentBoosting));
//    addSecondaryLine("Ball Touched", std::to_string(player.ballTouchedStep));
//    addSecondaryLine("Demolished", std::to_string(player.isDemoed));
//    addSecondaryLine("Has Flip", std::to_string(player.HasFlip()));
//    addSecondaryLine("Has Jump", std::to_string(player.HasJump()));
//
//    // Calculate main panel size
//    float mainWidth = marginLeft + nameSpacing + 3 * vecSpacing + padding;
//    float mainHeight = marginTop + mainLines.size() * lineSpacing + padding + extraBottomPadding;
//
//    // Calculate secondary panel size
//    float secondaryWidth = mainWidth; // Make it the same width as the main panel
//    float secondaryHeight = marginTop + secondaryLines.size() * lineSpacing + padding + extraBottomPadding;
//
//    // Draw main background panel
//    renderer.DrawRect2D(bgColor, rlbot::flat::Vector3{ x, y, 0 }, mainWidth, mainHeight, true);
//
//    // Draw secondary background panel
//    float secondaryY = y + mainHeight + panelSpacing;
//    renderer.DrawRect2D(bgColor, rlbot::flat::Vector3{ x, secondaryY, 0 }, secondaryWidth, secondaryHeight, true);
//
//    // Draw main panel title and lines
//    float currentLine = y + marginTop;
//    renderer.DrawString2D("Car State", visibleColor, rlbot::flat::Vector3{ x + marginLeft, currentLine, 0 }, 1, 1);
//    currentLine += lineSpacing * 1.5f;
//
//    for (const auto& line : mainLines) {
//        const auto& [label, value, value2, value3] = line;
//        renderer.DrawString2D(label, visibleColor, rlbot::flat::Vector3{ x + marginLeft, currentLine, 0 }, 1, 1);
//        renderer.DrawString2D(value, visibleColor, rlbot::flat::Vector3{ x + marginLeft + nameSpacing, currentLine, 0 }, 1, 1);
//        if (!value2.empty()) {
//            renderer.DrawString2D(value2, visibleColor, rlbot::flat::Vector3{ x + marginLeft + nameSpacing + vecSpacing, currentLine, 0 }, 1, 1);
//        }
//        if (!value3.empty()) {
//            renderer.DrawString2D(value3, visibleColor, rlbot::flat::Vector3{ x + marginLeft + nameSpacing + vecSpacing * 2, currentLine, 0 }, 1, 1);
//        }
//        currentLine += lineSpacing;
//    }
//
//    // Draw secondary panel title and lines
//    currentLine = secondaryY + marginTop;
//    renderer.DrawString2D("Additional Info", visibleColor, rlbot::flat::Vector3{ x + marginLeft, currentLine, 0 }, 1, 1);
//    currentLine += lineSpacing * 1.5f;
//
//    for (const auto& line : secondaryLines) {
//        const auto& [label, value] = line;
//        renderer.DrawString2D(label, visibleColor, rlbot::flat::Vector3{ x + marginLeft, currentLine, 0 }, 1, 1);
//        renderer.DrawString2D(value, visibleColor, rlbot::flat::Vector3{ x + marginLeft + nameSpacing, currentLine, 0 }, 1, 1);
//        currentLine += lineSpacing;
//    }
//
//    // Render 3D text above the player
//    rlbot::flat::Vector3 localPlayerLocation = {
//        player.pos.x,
//        player.pos.y,
//        player.pos.z + 200.0f
//    };
//    renderer.DrawString3D("", visibleColor, localPlayerLocation, 2, 2);
//}
//
//rlbot::Controller RLBotBot::GetOutput(rlbot::GameTickPacket gameTickPacket) {
//    // Get current time and frame information
//    if (!hasSetTickSkip) {
//        hasSetTickSkip = true;
//        ticks = 8;
//        updateAction = true;
//    }
//
//    float cur_time = gameTickPacket->gameInfo()->secondsElapsed();
//    float dt = cur_time - prevTime;
//    seconds_elapsed_since_actor_load += dt;
//    seconds_elapsed_since_kickoff += dt;
//    prevTime = cur_time;
//
//    int ticksElapsed = std::round(dt * 120);
//    ticks += ticksElapsed;
//
//    std::vector<RocketSim::Car*> rocketSimCars;
//    if (predictionArena != nullptr) {
//        auto& cars = predictionArena->GetCars();
//        rocketSimCars.assign(cars.begin(), cars.end());
//    }
//    //std::cout << "RocketSim cars seen: " << rocketSimCars.size() << std::endl;
//
//    // Convert the game tick packet to a GameState
//    GameState gs = ToGameState(gameTickPacket, ticksElapsed, 8, rocketSimCars, ticks, controls);
//    auto& localPlayer = gs.players[index];
//    UpdatePredictionArena(gs);
//    //RenderCarStateTable(gs);
//    if (updateAction) {
//        action = params.inferUnit->InferAction(localPlayer, gs, /*deterministic=*/false);
//        updateAction = false;
//    }
//
//    // Handle kickoff logic
//    if (gameTickPacket->gameInfo()->isKickoffPause()) {
//        seconds_elapsed_since_actor_load = 0.0f;
//        seconds_elapsed_since_kickoff = 0.0f;
//    }
//
//    // Periodically reload the policy
//    if (seconds_elapsed_since_actor_load > 30) {
//    
//        std::filesystem::path checkpointsDir = "E:\\GigaLearnCPP-main (2)\\GigaLearnCPP-main\\Build\\Release\\checkpoints";
//        std::filesystem::path latestPolicyFolder = GetLatestPolicyFolder2(checkpointsDir);
//    
//        // Retry up to 3 times to allow the folder to be fully available
//        for (int i = 0; i < 3; i++) {
//            if (std::filesystem::exists(latestPolicyFolder)) break;
//            std::this_thread::sleep_for(std::chrono::milliseconds(500));
//        }
//    
//        if (!latestPolicyFolder.empty() && std::filesystem::exists(latestPolicyFolder)) {
//            RLGC::ObsBuilder* obsBuilder = new DefaultObs();
//            RLGC::ActionParser* actionParser = new DefaultAction();
//            PartialModelConfig sharedHeadConfig;
//            sharedHeadConfig.addOutputLayer = false;
//            PartialModelConfig policyConfig;
//            policyConfig.layerSizes = { 256, 256, 256 };
//            policyConfig.addLayerNorm = false;
//            policyConfig.activationType = ModelActivationType::RELU;
//            policyConfig.optimType = ModelOptimType::ADAM;
//    
//    
//            try {
//                GGL::InferUnit* inferUnit = new GGL::InferUnit(
//                    obsBuilder,
//                    163,
//                    actionParser,
//                    sharedHeadConfig,
//                    policyConfig,
//                    latestPolicyFolder,
//                    false
//                );
//                params.inferUnit = inferUnit;
//                std::cout << "Policy successfully loaded from: " << latestPolicyFolder << std::endl;
//            }
//            catch (const std::exception& e) {
//                std::cerr << "InferUnit initialization failed: " << e.what() << std::endl;
//            }
//        }
//        else {
//            std::cerr << "Failed to load latest policy! Folder not found: " << latestPolicyFolder << std::endl;
//        }
//    
//        seconds_elapsed_since_actor_load = 0.0f;
//    }
//
//    // Periodically manipulate ball state for goal testing
//    if (seconds_elapsed_since_kickoff > 230) {
//        Vec goalPos = should_score_orange ? CommonValues::ORANGE_GOAL_CENTER : CommonValues::BLUE_GOAL_CENTER;
//        Vec ballPos = {
//            gameTickPacket->ball()->physics()->location()->x(),
//            gameTickPacket->ball()->physics()->location()->y(),
//            gameTickPacket->ball()->physics()->location()->z()
//        };
//    
//        Vec velVec = {
//            goalPos.x - ballPos.x,
//            goalPos.y - ballPos.y,
//            goalPos.z - ballPos.z
//        };
//    
//        rlbot::BallState ballState = {};
//        ballState.physicsState.velocity = { CommonValues::SIDE_WALL_X, 3, velVec.z };
//    
//        auto gamestate = rlbot::GameState();
//        gamestate.ballState = ballState;
//    
//        rlbot::Interface::SetGameState(gamestate);
//        seconds_elapsed_since_kickoff = 0.0f;
//        should_score_orange = !should_score_orange;
//    }
//
//    if (ticks >= params.actionDelay) {
//        UpdateControls(action);
//    }
//
//    // Reset ticks and trigger action update
//    if (ticks >= params.tickSkip) {
//        updateAction = true;
//        ticks = 0;
//    }
//
//    // Assign controls to the output controller
//    auto rc = rlbot::Controller();
//    {
//        rc.throttle = controls.throttle;
//        rc.steer = controls.steer;
//
//        rc.pitch = controls.pitch;
//        rc.yaw = controls.yaw;
//        rc.roll = controls.roll;
//
//        rc.boost = controls.boost > 0;
//        rc.jump = controls.jump > 0;
//        rc.handbrake = controls.handbrake > 0;
//    }
//
//    localPlayer.prevAction = controls;
//    return rc;
//}
//
//void RLBotClient::Run(const RLBotParams& params) {
//	g_RLBotParams = params;
//
//	rlbot::platform::SetWorkingDirectory(
//		rlbot::platform::GetExecutableDirectory()
//	);
//
//	rlbot::BotManager botManager(BotFactory);
//	botManager.StartBotServer(params.port);
//}
//


























#include "RLBotClient.h"
#include <rlbot/platform.h>
#include <rlbot/botmanager.h>
#include <cmath>

using namespace RLGC;
using namespace GGL;

RLBotParams g_RLBotParams = {};
float seconds_elapsed_since_actor_load = 0.0f;

rlbot::Bot* BotFactory(int index, int team, std::string name) {
    return new RLBotBot(index, team, name, g_RLBotParams);
}

Vec ToVec(const rlbot::flat::Vector3* rlbotVec) {
    if (!rlbotVec) return Vec();
    return Vec(rlbotVec->x(), rlbotVec->y(), rlbotVec->z());
}

PhysState ToPhysState(const rlbot::flat::Physics* phys) {
    PhysState obj = {};
    if (phys) {
        obj.pos = ToVec(phys->location());
        if (phys->rotation()) {
            Angle ang = Angle(phys->rotation()->yaw(), phys->rotation()->pitch(), phys->rotation()->roll());
            obj.rotMat = ang.ToRotMat();
        }
        obj.vel = ToVec(phys->velocity());
        obj.angVel = ToVec(phys->angularVelocity());
    }
    return obj;
}

RLBotBot::RLBotBot(int _index, int _team, std::string _name, const RLBotParams& params)
    : rlbot::Bot(_index, _team, _name), params(params) {
    RG_LOG("Created RLBot bot: index " << _index << ", name: " << name << "...");
}

RLBotBot::~RLBotBot() {
}

void RLBotBot::UpdateBallHitInfo(Player& player, PlayerInternalState& internalState,
    float curTime, const rlbot::flat::Touch* latestTouch) {
    // Update ball hit info if this player touched the ball
    if (latestTouch && latestTouch->playerIndex() == player.index) {
        float timeSinceTouch = curTime - latestTouch->gameSeconds();

        // Only update if this is a recent touch
        if (timeSinceTouch < 0.1f && gs.lastTickCount > internalState.ballHitInfo.tickCountWhenHit) {
            internalState.ballHitInfo.isValid = true;
            internalState.ballHitInfo.tickCountWhenHit = gs.lastTickCount;

            // Calculate relative position on ball
            Vec ballPos = gs.ball.pos;
            Vec touchLocation = ToVec(latestTouch->location());
            internalState.ballHitInfo.ballPos = ballPos;
            internalState.ballHitInfo.relativePosOnBall = touchLocation - ballPos;

            // Extra hit velocity (approximated - RLBot doesn't provide this directly)
            internalState.ballHitInfo.extraHitVel = Vec(0, 0, 0);
        }
    }
    else {
        // Invalidate old hit info after some time
        if (gs.lastTickCount > internalState.ballHitInfo.tickCountWhenHit + 120) {
            internalState.ballHitInfo.isValid = false;
        }
    }

    // Note: We don't assign to player.ballHitInfo since Player doesn't have this field
    // The internal state tracking is sufficient for observation builders that need it
}

void RLBotBot::UpdatePlayerState(Player& player, Player* prevPlayer,
    PlayerInternalState& internalState,
    float deltaTime, bool isLocalPlayer) {

    if (player.isSupersonic) {
        internalState.supersonicTime += deltaTime;
        if (internalState.supersonicTime > RLBotConst::SUPERSONIC_MAINTAIN_MAX_TIME) {
            internalState.supersonicTime = RLBotConst::SUPERSONIC_MAINTAIN_MAX_TIME;
        }
    }
    else {
        internalState.supersonicTime = 0;
    }
    player.supersonicTime = internalState.supersonicTime;

    bool currentlyBoosting = (isLocalPlayer && controls.boost) ||
        (prevPlayer && prevPlayer->prevAction.boost != 0);

    if (internalState.timeSpentBoosting > 0) {
        if (!currentlyBoosting && internalState.timeSpentBoosting >= RLBotConst::BOOST_MIN_TIME) {
            internalState.timeSpentBoosting = 0;
        }
        else {
            internalState.timeSpentBoosting += deltaTime;
        }
    }
    else {
        if (currentlyBoosting) {
            internalState.timeSpentBoosting = deltaTime;
        }
    }
    player.timeSpentBoosting = internalState.timeSpentBoosting;
    bool currentlyHandbraking = (isLocalPlayer && controls.handbrake) ||
        (prevPlayer && prevPlayer->prevAction.handbrake != 0);

    if (currentlyHandbraking) {
        internalState.handbrakeVal += RLBotConst::POWERSLIDE_RISE_RATE * deltaTime;
    }
    else {
        internalState.handbrakeVal -= RLBotConst::POWERSLIDE_FALL_RATE * deltaTime;
    }
    internalState.handbrakeVal = RS_CLAMP(internalState.handbrakeVal, 0.f, 1.f);
    player.handbrakeVal = internalState.handbrakeVal;

    // We estimate by setting all 4 wheels to the same state (API limitation)
    int numWheelsInContact = player.isOnGround ? 4 : 0;

    for (int i = 0; i < 4; i++) {
        internalState.wheelsWithContact[i] = (numWheelsInContact > 0);
        player.wheelsWithContact[i] = internalState.wheelsWithContact[i];
    }
    internalState.numWheelsInContact = numWheelsInContact;

    if (player.isDemoed) {
        if (!internalState.wasDemoedLastFrame) {
            // Just got demoed this frame
            internalState.demoRespawnTimer = RLBotConst::DEMO_RESPAWN_TIME;
            internalState.demoTick = gs.lastTickCount;
        }
        else {
            // Continue counting down
            internalState.demoRespawnTimer -= deltaTime;
            if (internalState.demoRespawnTimer < 0) {
                internalState.demoRespawnTimer = 0;
            }
        }
    }
    else {
        if (internalState.wasDemoedLastFrame) {
            // Just respawned
            internalState.demoRespawnTimer = 0;
        }
    }
    player.demoRespawnTimer = internalState.demoRespawnTimer;
    internalState.wasDemoedLastFrame = player.isDemoed;

    if (internalState.carContact.cooldownTimer > 0) {
        internalState.carContact.cooldownTimer -= deltaTime;
        if (internalState.carContact.cooldownTimer < 0) {
            internalState.carContact.cooldownTimer = 0;
            internalState.carContact.otherCarID = 0;
        }
    }

    player.carContact.otherCarID = internalState.carContact.otherCarID;
    player.carContact.cooldownTimer = internalState.carContact.cooldownTimer;

    if (player.isOnGround) {
        internalState.isJumping = false;
        internalState.isFlipping = false;
        internalState.flipTime = 0;
        internalState.hasFlipped = false;
        internalState.flipRelTorque = Vec(0, 0, 0);
        internalState.airTime = 0;
        internalState.airTimeSinceJump = 0;
        internalState.autoFlipTimer = 0;
        internalState.isAutoFlipping = false;
        internalState.autoFlipTorqueScale = 0;

        // Reset hasJumped when landing (with time padding for minimum jumps)
        if (prevPlayer && prevPlayer->hasJumped) {
            if (internalState.jumpTime < RLBotConst::JUMP_MIN_TIME + RLBotConst::JUMP_RESET_TIME_PAD) {
                // Don't reset jump yet - might still be leaving ground after min-time jump
            }
            else {
                internalState.jumpTime = 0;
            }
        }
    }
    else {

        internalState.airTime += deltaTime;
        player.airTime = internalState.airTime;

        if (internalState.isJumping) {
            internalState.jumpTime += deltaTime;
            // Jump ends after JUMP_MAX_TIME
            if (internalState.jumpTime >= RLBotConst::JUMP_MAX_TIME) {
                internalState.isJumping = false;
            }
        }
        player.jumpTime = internalState.jumpTime;

        if (internalState.isFlipping) {
            internalState.flipTime += deltaTime;
            // Flip torque ends after FLIP_TORQUE_TIME
            if (internalState.flipTime >= RLBotConst::FLIP_TORQUE_TIME) {
                internalState.isFlipping = false;
            }
        }
        player.flipTime = internalState.flipTime;

        if (player.hasJumped && !internalState.isJumping) {
            internalState.airTimeSinceJump += deltaTime;
        }
        else {
            internalState.airTimeSinceJump = 0;
        }
        player.airTimeSinceJump = internalState.airTimeSinceJump;

        // Car auto-flips when upside down in the air for too long
        bool shouldAutoFlip = (player.rotMat.up.z < RLBotConst::CAR_AUTOFLIP_NORMZ_THRESH) &&
            (std::abs(player.rotMat.forward.z) < 0.9f);

        if (shouldAutoFlip) {
            internalState.autoFlipTimer += deltaTime;
            if (internalState.autoFlipTimer >= RLBotConst::CAR_AUTOFLIP_TIME && !internalState.isAutoFlipping) {
                internalState.isAutoFlipping = true;
                // Calculate auto-flip direction based on roll angle
                Angle angles = Angle::FromRotMat(player.rotMat);
                float absRoll = std::abs(angles.roll);
                if (absRoll > RLBotConst::CAR_AUTOFLIP_ROLL_THRESH) {
                    internalState.autoFlipTorqueScale = (angles.roll > 0) ? 1.f : -1.f;
                }
            }
        }
        else {
            internalState.autoFlipTimer = 0;
            internalState.isAutoFlipping = false;
            internalState.autoFlipTorqueScale = 0;
        }

        // Flip reset occurs when all wheels touch a surface while in the air
        internalState.gotFlipResetThisFrame = false;

        // Detect flip reset: hasJumped or hasDoubleJumped goes false while in air
        if (prevPlayer) {
            bool hadJumpedBefore = internalState.hadJumpedLastFrame;
            bool hadDoubleJumpedBefore = internalState.hadDoubleJumpedLastFrame;

            // If hasJumped was true and is now false while in air to flip reset
            if (hadJumpedBefore && !player.hasJumped && !player.isOnGround) {
                internalState.gotFlipResetThisFrame = true;
                internalState.lastFlipResetTick = gs.lastTickCount;

                // Reset flip related states
                internalState.hasFlipped = false;
                internalState.isFlipping = false;
                internalState.flipTime = 0;
                internalState.flipRelTorque = Vec(0, 0, 0);
                internalState.airTimeSinceJump = 0;
            }

            // Alternative detection: doubleJumped goes false while in air
            if (hadDoubleJumpedBefore && !player.hasDoubleJumped && !player.isOnGround && player.hasJumped) {
                internalState.gotFlipResetThisFrame = true;
                internalState.lastFlipResetTick = gs.lastTickCount;
            }
        }
    }

    if (prevPlayer) {
        // Detect first jump
        if (player.hasJumped && !prevPlayer->hasJumped) {
            internalState.isJumping = true;
            internalState.jumpTime = 0;
            internalState.jumpReleased = false;
            // Starting a new jump cancels any flip state
            internalState.isFlipping = false;
            internalState.flipTime = 0;
        }

        // Detect second jump/flip (double jump changes from false to true)
        if (player.hasDoubleJumped && !prevPlayer->hasDoubleJumped && !player.isOnGround) {
            internalState.isFlipping = true;
            internalState.flipTime = 0;
            internalState.hasFlipped = true;
            internalState.isJumping = false; // Flip consumes second jump, ends jumping state

            // Calculate flip direction from controls
            // Get the current action being applied
            Action currentAction = isLocalPlayer ? controls : prevPlayer->prevAction;

            float pitch = currentAction.pitch;
            float yaw = currentAction.yaw;

            // Normalize the dodge direction
            Vec dodgeDir = Vec(pitch, yaw, 0);
            float dodgeMag = dodgeDir.Length();

            if (dodgeMag > 0.1f) {
                dodgeDir = dodgeDir.Normalized();

                // Apply deadzones (< 0.1 becomes 0)
                if (std::abs(dodgeDir.x) < 0.1f) dodgeDir.x = 0;
                if (std::abs(dodgeDir.y) < 0.1f) dodgeDir.y = 0;

                // Calculate relative flip torque: flipRelTorque = (-yaw, pitch, 0)
                // This matches RocketSim's calculation
                internalState.flipRelTorque = Vec(-dodgeDir.y, dodgeDir.x, 0);
            }
            else {
                // Neutral flip (straight up double jump) - no flip torque
                internalState.flipRelTorque = Vec(0, 0, 0);
            }
        }
    }

    player.isJumping = internalState.isJumping;
    player.isFlipping = internalState.isFlipping;
    player.hasFlipped = internalState.hasFlipped;
    player.flipRelTorque = internalState.flipRelTorque;
    player.isAutoFlipping = internalState.isAutoFlipping;
    player.autoFlipTimer = internalState.autoFlipTimer;
    player.autoFlipTorqueScale = internalState.autoFlipTorqueScale;

    // World contact (estimated based on wheel contact)
    player.worldContact.hasContact = internalState.worldContact.hasContact;
    player.worldContact.contactNormal = internalState.worldContact.contactNormal;

    // Store previous frame states for next update
    internalState.wasOnGroundLastFrame = player.isOnGround;
    internalState.wasInAirLastFrame = !player.isOnGround;
    internalState.hadJumpedLastFrame = player.hasJumped;
    internalState.hadDoubleJumpedLastFrame = player.hasDoubleJumped;
    // Note: Don't track hadWheelContactLastFrame since Player doesn't have hasWheelContact field
}

void RLBotBot::UpdateGameState(rlbot::GameTickPacket& packet, float deltaTime, float curTime) {

    prevGs = gs;
    gs = {};
    gs.lastTickCount = packet->gameInfo()->frameNum();
    gs.deltaTime = deltaTime;

    PhysState ballPhys = ToPhysState(packet->ball()->physics());
    static_cast<PhysState&>(gs.ball) = ballPhys;
    auto latestTouch = packet->ball()->latestTouch();

    auto boostPadStates = packet->boostPadStates();
    gs.boostPads.resize(CommonValues::BOOST_LOCATIONS_AMOUNT, true);
    gs.boostPadsInv.resize(CommonValues::BOOST_LOCATIONS_AMOUNT, true);
    gs.boostPadTimers.resize(CommonValues::BOOST_LOCATIONS_AMOUNT, 0);
    gs.boostPadTimersInv.resize(CommonValues::BOOST_LOCATIONS_AMOUNT, 0);

    if (boostPadStates && boostPadStates->size() == CommonValues::BOOST_LOCATIONS_AMOUNT) {
        for (int i = 0; i < CommonValues::BOOST_LOCATIONS_AMOUNT; i++) {
            gs.boostPads[i] = boostPadStates->Get(i)->isActive();
            gs.boostPadsInv[CommonValues::BOOST_LOCATIONS_AMOUNT - i - 1] = gs.boostPads[i];
            gs.boostPadTimers[i] = boostPadStates->Get(i)->timer();
            gs.boostPadTimersInv[CommonValues::BOOST_LOCATIONS_AMOUNT - i - 1] = gs.boostPadTimers[i];
        }
    }

    auto players = packet->players();
    gs.players.resize(players->size());

    for (int i = 0; i < players->size(); i++) {
        auto playerInfo = players->Get(i);
        Player& player = gs.players[i];
        Player* prevPlayer = (prevGs.players.size() > i && prevGs.players[i].carId == playerInfo->spawnId())
            ? &prevGs.players[i] : nullptr;
        PlayerInternalState& internalState = internalPlayerStates[i];

        // Basic physics state
        static_cast<PhysState&>(player) = ToPhysState(playerInfo->physics());

        // Basic player info from RLBot
        player.carId = playerInfo->spawnId();
        player.team = (Team)playerInfo->team();
        player.boost = playerInfo->boost();
        player.isDemoed = playerInfo->isDemolished();
        player.isOnGround = playerInfo->hasWheelContact();
        player.hasJumped = playerInfo->jumped();
        player.hasDoubleJumped = playerInfo->doubleJumped();
        player.isSupersonic = playerInfo->isSupersonic();
        player.index = i;
        player.prev = prevPlayer;

        // Update comprehensive state tracking (1:1 with RocketSim)
        bool isLocalPlayer = (i == index);
        UpdatePlayerState(player, prevPlayer, internalState, deltaTime, isLocalPlayer);

        // Update ball hit info
        UpdateBallHitInfo(player, internalState, curTime, latestTouch);

        player.ballTouchedStep = false;
        player.ballTouchedTick = false;

        if (latestTouch && latestTouch->playerIndex() == i) {
            float timeSinceTouch = curTime - latestTouch->gameSeconds();

            // Step touch: within the current step's time window
            if (timeSinceTouch < (params.tickSkip * CommonValues::TICK_TIME) + 0.01f) {
                player.ballTouchedStep = true;
                gs.lastTouchCarID = player.carId;
            }

            // Tick touch: within this specific tick
            if (timeSinceTouch < deltaTime + 0.01f) {
                player.ballTouchedTick = true;
            }

            internalState.lastTouchTick = gs.lastTickCount;
        }
    }

    gs.goalScored = false;
    for (int i = 0; i < 2; i++) {
        int currentScore = packet->teams()->Get(i)->score();
        if (currentScore > lastTeamScores[i]) {
            gs.goalScored = true;
        }
        lastTeamScores[i] = currentScore;
    }
}

rlbot::Controller RLBotBot::GetOutput(rlbot::GameTickPacket gameTickPacket) {

    float curTime = gameTickPacket->gameInfo()->secondsElapsed();
    if (prevTime == 0) prevTime = curTime;
    float deltaTime = curTime - prevTime;
    seconds_elapsed_since_actor_load += deltaTime;
    prevTime = curTime;

    int ticksElapsed = (ticks == -1) ? params.tickSkip : roundf(deltaTime * 120);

    // If no time has passed, return previous controls
    if (ticksElapsed == 0 && ticks != -1) {
        rlbot::Controller output_controller = {};
        output_controller.throttle = controls.throttle;
        output_controller.steer = controls.steer;
        output_controller.pitch = controls.pitch;
        output_controller.yaw = controls.yaw;
        output_controller.roll = controls.roll;
        output_controller.jump = controls.jump != 0;
        output_controller.boost = controls.boost != 0;
        output_controller.handbrake = controls.handbrake != 0;
        return output_controller;
    }

    last_ticks = ticks;
    ticks += ticksElapsed;

    // Update game state with comprehensive 1:1 RocketSim tracking
    UpdateGameState(gameTickPacket, deltaTime, curTime);
    auto& localPlayer = gs.players[index];
    localPlayer.prevAction = controls;

    // Determine if we need new action from policy
    if (ticks >= params.tickSkip || ticks == -1) {
        ticks %= params.tickSkip;
        updateAction = true;
    }

    if (gameTickPacket->gameInfo()->isKickoffPause()) {
                seconds_elapsed_since_actor_load = 0.0f;
        //        seconds_elapsed_since_kickoff = 0.0f;
           }

    // Get new action from policy if needed
    if (updateAction) {
        updateAction = false;
        action = params.inferUnit->InferAction(localPlayer, gs, params.deterministic);
    }

    // Apply action delay
    if (last_ticks < params.actionDelay && ticks >= params.actionDelay) {
        controls = action;
    }

    if (seconds_elapsed_since_actor_load > 120) {
            
                std::filesystem::path checkpointsDir = "E:\\GigaLearnCPP-main (2)\\GigaLearnCPP-main\\Build\\Release\\checkpoints";
                std::filesystem::path latestPolicyFolder = GetLatestPolicyFolder3(checkpointsDir);
            
                // Retry up to 3 times to allow the folder to be fully available
                for (int i = 0; i < 3; i++) {
                    if (std::filesystem::exists(latestPolicyFolder)) break;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                }
            
                if (!latestPolicyFolder.empty() && std::filesystem::exists(latestPolicyFolder)) {
                    RLGC::ObsBuilder* obsBuilder = new DefaultObsPadded(3);
                    RLGC::ActionParser* actionParser = new CoyoteAction();
                    PartialModelConfig sharedHeadConfig;
                    sharedHeadConfig.addOutputLayer = false;
                    PartialModelConfig policyConfig;
                    policyConfig.layerSizes = { 256, 256, 256 };
                    policyConfig.addLayerNorm = false;
                    policyConfig.activationType = ModelActivationType::RELU;
                    policyConfig.optimType = ModelOptimType::ADAM;
            
            
                    try {
                        GGL::InferUnit* inferUnit = new GGL::InferUnit(
                            obsBuilder,
                            143,
                            actionParser,
                            sharedHeadConfig,
                            policyConfig,
                            latestPolicyFolder,
                            false
                        );
                        params.inferUnit = inferUnit;
                        std::cout << "Policy successfully loaded from: " << latestPolicyFolder << std::endl;
                    }
                    catch (const std::exception& e) {
                        std::cerr << "InferUnit initialization failed: " << e.what() << std::endl;
                    }
                }
                else {
                    std::cerr << "Failed to load latest policy! Folder not found: " << latestPolicyFolder << std::endl;
                }
            
                seconds_elapsed_since_actor_load = 0.0f;
            }

    // Convert to RLBot controller format
    rlbot::Controller output_controller = {};
    output_controller.throttle = controls.throttle;
    output_controller.steer = controls.steer;
    output_controller.pitch = controls.pitch;
    output_controller.yaw = controls.yaw;
    output_controller.roll = controls.roll;
    output_controller.jump = controls.jump != 0;
    output_controller.boost = controls.boost != 0;
    output_controller.handbrake = controls.handbrake != 0;
    output_controller.useItem = false;

    return output_controller;
}

void RLBotClient::Run(const RLBotParams& params) {
    g_RLBotParams = params;
    rlbot::platform::SetWorkingDirectory(rlbot::platform::GetExecutableDirectory());
    rlbot::BotManager botManager(BotFactory);
    botManager.StartBotServer(params.port);
}
