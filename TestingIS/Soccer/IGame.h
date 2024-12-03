#pragma once

#include <vector>
#include <memory>

enum class EPlayer;
class IGameListener;

class IGame {
public:
    virtual ~IGame() = default;

    virtual std::vector<EPlayer> GetPlayerObjects() const = 0;
    virtual EPlayer GetCurrentPlayer() const = 0;

    static std::shared_ptr<IGame> Produce();

    virtual void AddListener(IGameListener* gameListener) = 0;
    virtual void RemoveListener(IGameListener* gameListener) = 0;

    virtual void SwitchPlayers() = 0;

    virtual void NotifyListenersOnWin() = 0;
    virtual void ResetGame() = 0;
    virtual void UpdateScore(EPlayer scoredOn) = 0;
};

struct Post {
    float x, y1, y2;
};
